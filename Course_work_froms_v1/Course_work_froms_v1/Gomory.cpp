#include "Gomory.hpp"

namespace coursework
{

	void Gomory(char *file_name, graph *&gr)
	{
		FILE *f;

		// Open file
		if ((f = fopen(file_name, "wt")) == NULL)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не можливо відкрити файл ";
			e.text += file_name;
			throw(e);
		}

		// Recreate graph
		gr->type = 0;
		if (gr->adj_m != NULL)
		{
			delete_array<bool>(gr->adj_m, gr->n_vertexes);
			gr->adj_m = adj(gr);
		}

		// Give memory for result graph
		graph *gr_result = create_graph(gr->n_vertexes, gr->n_vertexes - 1);

		// Set that we have one vertex (gr)
		gr_result->n_vertexes = 1;
		gr_result->n_edges = 0;

		// Create array of graphs. Each graph of array is a vertex of gr_result
		graph **graphs = new graph*[gr->n_vertexes];

		// Give memory for adjacent matrix
		gr_result->adj_m = create_array<bool>(gr->n_vertexes, gr->n_vertexes);

		// First init
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			graphs[i] = NULL;
			gr_result->v_n[i] = gr->v_n[i];
			for (int j = 0; j < gr->n_vertexes; j++)
				gr_result->adj_m[i][j] = 0;
		}

		// First graph and first vertex
		graphs[0] = gr;

		//
		//
		// Start recurs for gr_resultS
		try
		{
			recurs_Gomory(gr_result, graphs, 0, &f);
		}
		catch (int &e)
		{
			Gomory_free(gr_result, graphs);

			T_exception ex;
			if (fclose(f))
			{
				
				ex.code = 1;
				ex.text = "Не можливо закрити файл ";
				ex.text += file_name;
				throw(ex);
			}

			ex.code = e;
			if (e == 5)
			{
				ex.text = "Алгоритм Форда-Фалкерсона перевищив максимальну кількість ітерацій.";
				ex.solution = "Змініть граф, або вкажіть джерело та стік.";
			}
			else if (e == 3)
			{
				ex.text = "Не можливо знайти стік або джерело мережі.";
				ex.solution = "Змініть граф, або вкажіть джерело та стік.";
			}
			else
			{
				ex.text = "Невідома помилка.";
			}

			throw(ex);
		}
		//
		//
		//

		// Rebuild result graph
		T_vertex tmp;
		tmp.union_v = false;
		for (int i = 0; i < gr_result->n_edges; i++)
		{
			// Find id of not union vertex in graph
			tmp.v = find_not_union_ver(graphs[gr_result->edges[i].in]);
			// Set instead of graph - not union vertex
			gr_result->edges[i].in = g_id(tmp, gr_result);

			// Find id of not union vertex in graph
			tmp.v = find_not_union_ver(graphs[gr_result->edges[i].out]);
			// Set instead of graph - not union vertex
			gr_result->edges[i].out = g_id(tmp, gr_result);

			// If error
			if (gr_result->edges[i].in == -1 || gr_result->edges[i].out == -1)
			{
				T_exception e;
				e.code = 1;
				e.text = "Виникла помилка в алгоритмі Гуморі-Ху.";
				e.solution = "Введіть інший граф.";
				throw(e);
			}
		}
		// Recreare adjacent matrix
		delete_array(gr_result->adj_m, gr_result->n_vertexes);
		gr_result->adj_m = adj(gr_result);

		// Init pass_abl by stream
		for (int i = 0; i < gr_result->n_edges; i++)
			gr_result->edges[i].pass_abl = gr_result->edges[i].stream;

		// Output result graph in file
		fprintf(f, "================================================\nResult graph:\n\n");
		output(gr_result, &f);
		// And draw...
		graphviz("Gomory_result.png", gr_result);

		// Free memory from graphs
		Gomory_free(gr_result, graphs);

		//
		// Build streams matrix
		//

		// Create dynamic array
		gr_result->streams = create_array<int>(gr_result->n_vertexes, gr_result->n_vertexes);
		// Init
		for (int i = 0; i < gr_result->n_vertexes; i++)
			for (int j = 0; j < gr_result->n_vertexes; j++)
				if (i == j)
					gr_result->streams[i][j] = 0;
				else
					gr_result->streams[i][j] = INF;

		for (int i = 0; i < gr_result->n_edges; i++)
		{
			gr_result->streams[gr_result->edges[i].in][gr_result->edges[i].out] = gr_result->edges[i].stream;
			gr_result->streams[gr_result->edges[i].out][gr_result->edges[i].in] = gr_result->edges[i].stream;
		}

		// Define matrix of streams by DFS
		for (int i = 0; i < gr_result->n_vertexes; i++)
		{
			DFS_Gomory(gr_result, i, -1, i, INF);
		}

		// Ouput matrix of streams in file
		fprintf(f, "\n\nMatrix of streams:\n");
		output_streams(gr_result, &f);

		// Now input graph is Gomory resulted graph
		gr = gr_result;

		// Close file
		if (fclose(f))
		{
			T_exception e;
			e.code = 1;
			e.text = "Не можливо закрити файл ";
			e.text += file_name;
			throw(e);
		}
	}

	int find_not_union_ver(graph *gr)
	{
		for (int i = 0; i < gr->n_vertexes; i++)
			for (int i = 0; i < gr->n_vertexes; i++)
				if (!gr->v_n[i].union_v)
					return gr->v_n[i].v;

		return -1;
	}

	void recurs_Gomory(graph *&gr_result, graph **&graphs, int ver, FILE **f_output)
	{
		//
		// If end of recurs
		//

		if (if_end_recurs(graphs[ver]))
			return;

		//
		// If not end of recurs
		//

		// Output current graph
		fprintf(*f_output, "================================================\nCurrent graph (№%d):\n", gr_result->n_vertexes);
		output(graphs[ver], f_output);

		char *tmp = new char[40];
		char *buf = new char[40];
		//char *buffer = new char[20]; // Char buffer
		//itoa(gr_result->n_vertexes, buf, 10);
		sprintf(tmp, "Graph#%d.png", gr_result->n_vertexes);
		graphviz(tmp, graphs[ver]);

		//
		//
		//---------------------------------------------------------
		// Ford for two not union vertices

		// Find two not union vertices
		int *vers = find_not_union_vers(graphs[ver]);

		// Ford-Fulkerson algorithm
		int max_stream;
		max_stream = Ford(f_output, graphs[ver], vers[0], vers[1]);
		

		// Recreate adjacent matrix
		for (int i = 0; i < graphs[ver]->n_vertexes; i++)
			for (int j = 0; j < graphs[ver]->n_vertexes; j++)
				if (graphs[ver]->adj_m[i][j])
					graphs[ver]->adj_m[j][i] = 1;

		// Define minimum cut
		int *vect;
		vect = def_min_cut(graphs[ver], vers[0]);
		delete[] vers;

		// Output minimum cut vertices
		int i = 0;
		fprintf(*f_output, "\nVertices in minimum cut of current graph:\n");
		while (vect[i] != -1)
		{
			fprintf(*f_output, "%s ", g_n(graphs[ver]->v_n[vect[i]], buf));
			i++;
		}
		fprintf(*f_output, "\n");
		//---------------------------------------------------------
		//
		//

		//
		//
		//---------------------------------------------------------
		// Condense first half of graph (do not hold vect)
		graphs[gr_result->n_vertexes] = condense(graphs[ver], 0, vect, /*ver*/gr_result->n_vertexes);
		gr_result->n_vertexes++;

		fprintf(*f_output, "\nFirst condensed graph:\n");
		output(graphs[gr_result->n_vertexes - 1], f_output);
		sprintf(tmp, "Graph#%d_first_half.png", gr_result->n_vertexes - 1);
		graphviz(tmp, graphs[gr_result->n_vertexes - 1]);

		// Condense second half of graph (hold vect)
		graphs[gr_result->n_vertexes] = condense(graphs[ver], 1, vect, /*ver*/gr_result->n_vertexes - 1);
		gr_result->n_vertexes++;

		fprintf(*f_output, "\nSecond condensed graph:\n");
		output(graphs[gr_result->n_vertexes - 1], f_output);
		sprintf(tmp, "Graph#%d_second_half.png", gr_result->n_vertexes - 2);
		graphviz(tmp, graphs[gr_result->n_vertexes - 1]);
		//---------------------------------------------------------
		//
		//

		//
		//
		//---------------------------------------------------------
		// Rebuild Gomory graph

		// Free memory from old graph which is was given in function (Do not need it enough)
		delete_graph(graphs[ver]);
		// If "0" vertex is in second half
		if (!find_in_vect(vect, 0))
		{
			// Set on his (gr) place first half
			graphs[ver] = graphs[gr_result->n_vertexes - 2];
			// Set on place this(^) graph, second half graph
			graphs[gr_result->n_vertexes - 2] = graphs[gr_result->n_vertexes - 1];
			graphs[gr_result->n_vertexes - 1] = NULL;
			gr_result->n_vertexes--;
		}
		else
		{
			// Set on his (gr) place second half
			graphs[ver] = graphs[gr_result->n_vertexes - 1];
			graphs[gr_result->n_vertexes - 1] = NULL;
			gr_result->n_vertexes--;
		}

		// Add new edge between graphs[ver] and second hapf graphs[last]
		gr_result->edges[gr_result->n_edges].in = ver;
		gr_result->edges[gr_result->n_edges].out = gr_result->n_vertexes - 1;
		gr_result->edges[gr_result->n_edges].stream = max_stream;
		gr_result->edges[gr_result->n_edges].union_vertex = gr_result->n_vertexes - 1;
		gr_result->n_edges++;
		gr_result->adj_m[ver][gr_result->n_vertexes - 1] = 1;
		gr_result->adj_m[gr_result->n_vertexes - 1][ver] = 1;

		// Change edges of result graph
		cg_adj(gr_result, graphs, ver, vect);

		// Draw Gomory graph
		sprintf(tmp, "Gomory_Graph_%d.png", gr_result->n_vertexes - 1);
		graphviz(tmp, gr_result, true);

		// Free memory
		delete[] tmp;
		delete[] buf;
		delete[] vect;

		fprintf(*f_output, "\n\n");
		//---------------------------------------------------------
		//
		//

		//
		//
		//---------------------------------------------------------
		// Recurs

		// Start recurs_Gomory for second half
		recurs_Gomory(gr_result, graphs, gr_result->n_vertexes - 1, f_output);

		// Start recurs_Gomory for first half
		recurs_Gomory(gr_result, graphs, ver, f_output);

		//---------------------------------------------------------
		//
		//
	}

	bool if_end_recurs(graph *gr)
	{
		// Number of vertexes without UNION_VERTEX
		int num = 0;
		for (int i = 0; i < gr->n_vertexes; i++)
			if (!gr->v_n[i].union_v)
				num++;

		// If there are more then one not UNION_VERTEX in graph
		if (num > 1)
			return false;
		else
			return true;
	}

	int* find_not_union_vers(graph *gr)
	{
		int *res = new int[2];

		// Current number of vertexes in @res
		int k = 0;

		for (int i = 0; i < gr->n_vertexes; i++)
			for (int i = 0; i < gr->n_vertexes; i++)
				if (!gr->v_n[i].union_v)
				{
					res[k] = i;
					k++;
					if (k == 2)
						return res;
				}

		return res;
	}

	bool find_union_ver(graph *gr, int name)
	{
		for (int i = 0; i < gr->n_edges; i++)
			if ((gr->v_n[gr->edges[i].in].union_v && gr->v_n[gr->edges[i].in].v == name) || (gr->v_n[gr->edges[i].out].union_v && gr->v_n[gr->edges[i].out].v == name))
				return true;

		return false;
	}

	void cg_adj(graph *&gr_result, graph **graphs, int ver, int *vect)
	{
		// Current edge
		int cur_e;

		for (int i = 0; i < gr_result->n_vertexes; i++)
		{
			// If vertex is not adjacent
			if (!gr_result->adj_m[i][ver] || i == gr_result->n_vertexes - 1)
				continue;

			cur_e = g_e(i, ver, gr_result);
			if (!find_union_ver(graphs[ver], gr_result->edges[cur_e].union_vertex))
			{
				gr_result->adj_m[i][ver] = 0;
				gr_result->adj_m[ver][i] = 0;
				gr_result->adj_m[gr_result->n_vertexes - 1][i] = 1;
				gr_result->adj_m[i][gr_result->n_vertexes - 1] = 1;

				gr_result->edges[cur_e].in = i;
				gr_result->edges[cur_e].out = gr_result->n_vertexes - 1;
			}
		}
	}

	graph* condense(graph *&gr, bool half, int* vect, int ver)
	{
		// Give memory for condense graph
		graph *result = create_graph(gr->n_vertexes, gr->n_edges);
		result->n_vertexes = 1;
		result->n_edges = 0;

		// Create union vertex
		result->v_n[0].v = ver;
		result->v_n[0].union_v = true;

		// Create adjacent matrix
		if (gr->adj_m == NULL)
			gr->adj_m = adj(gr);

		int c_e; // Current edge

		for (int i = 0; i < gr->n_vertexes; i++)
			for (int j = 0; j < gr->n_vertexes; j++)
			{
				// If first half and vertexes adjacement
				if (!half && gr->adj_m[i][j])
				{
					// If i is in vect
					if (find_in_vect(vect, i))
					{
						if (!find_in_vect(vect, j))
						{
							// If vertex not been found yet
							if (g_id(gr->v_n[j], result) == -1)
							{
								result->v_n[result->n_vertexes] = gr->v_n[j];
								result->n_vertexes++;
							}

							// To avoid adges with same vertices
							if (gr->v_n[j].v == ver && gr->v_n[j].union_v)
								continue;

							if ((c_e = g_e(0, g_id(gr->v_n[j], result), result)) == -1)
							{
								// Create edge
								result->edges[result->n_edges].in = 0;
								result->edges[result->n_edges].out = g_id(gr->v_n[j], result);
								result->edges[result->n_edges].pass_abl = gr->edges[g_e(i, j, gr)].pass_abl;
								result->n_edges++;
							}
							else
							{
								result->edges[c_e].pass_abl += gr->edges[g_e(i, j, gr)].pass_abl;
							}
						}
					}
					else if (!find_in_vect(vect, j))
					{
						// If vertex not been found yet
						if (g_id(gr->v_n[j], result) == -1)
						{
							result->v_n[result->n_vertexes] = gr->v_n[j];
							result->n_vertexes++;
						}
						// If vertex not been found yet
						if (g_id(gr->v_n[i], result) == -1)
						{
							result->v_n[result->n_vertexes] = gr->v_n[i];
							result->n_vertexes++;
						}

						if ((c_e = g_e(g_id(gr->v_n[i], result), g_id(gr->v_n[j], result), result)) == -1)
						{
							// Create edge
							result->edges[result->n_edges].in = g_id(gr->v_n[i], result);
							result->edges[result->n_edges].out = g_id(gr->v_n[j], result);
							result->edges[result->n_edges].pass_abl = gr->edges[g_e(i, j, gr)].pass_abl;
							result->n_edges++;
						}
					}


				}
				else if (half && gr->adj_m[i][j])
				{
					// If i is not in vect
					if (!find_in_vect(vect, i))
					{
						if (find_in_vect(vect, j))
						{
							// If vertex not been found yet
							if (g_id(gr->v_n[j], result) == -1)
							{
								result->v_n[result->n_vertexes] = gr->v_n[j];
								result->n_vertexes++;
							}

							if (gr->v_n[j].v == ver && gr->v_n[j].union_v)
								continue;

							if ((c_e = g_e(0, g_id(gr->v_n[j], result), result)) == -1)
							{
								// Create edge
								result->edges[result->n_edges].in = 0;
								result->edges[result->n_edges].out = g_id(gr->v_n[j], result);
								result->edges[result->n_edges].pass_abl = gr->edges[g_e(i, j, gr)].pass_abl;
								result->n_edges++;
							}
							else
							{
								result->edges[c_e].pass_abl += gr->edges[g_e(i, j, gr)].pass_abl;
							}
						}
					}
					else if (find_in_vect(vect, j))
					{
						// If vertex not been found yet
						if (g_id(gr->v_n[j], result) == -1)
						{
							result->v_n[result->n_vertexes] = gr->v_n[j];
							result->n_vertexes++;
						}

						// If vertex not been found yet
						if (g_id(gr->v_n[i], result) == -1)
						{
							result->v_n[result->n_vertexes] = gr->v_n[i];
							result->n_vertexes++;
						}

						if ((c_e = g_e(g_id(gr->v_n[i], result), g_id(gr->v_n[j], result), result)) == -1)
						{
							// Create edge
							result->edges[result->n_edges].in = g_id(gr->v_n[i], result);
							result->edges[result->n_edges].out = g_id(gr->v_n[j], result);
							result->edges[result->n_edges].pass_abl = gr->edges[g_e(i, j, gr)].pass_abl;
							result->n_edges++;
						}
					}
				}
			}

		// Init streams by zero
		for (int i = 0; i < result->n_edges; i++)
			result->edges[i].stream = 0;

		return result;
	}

	int* def_min_cut(graph* gr, int in)
	{
		// Vertor of vertexes of first half of cut
		int* result = new int[gr->n_vertexes];
		T_queue *wave_head = NULL;
		T_queue *wave_tail = NULL;

		// Array of visited vertices
		bool* visit = new bool[gr->n_vertexes];

		// Init
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			result[i] = -1;
			visit[i] = 0;
		}
		result[0] = in;
		visit[in] = 1;
		add_e(wave_head, wave_tail, in);

		int edge_n,		// Current edge
			c_v = in,	// Current vertex
			j = 1;		// Count of vertexes in result - 1

		// Fill result vector
		while (wave_head != NULL)
		{
			// Get element from previous wave
			c_v = get_e(wave_head, wave_tail);

			// For each adjacent vertex...
			for (int i = 0; i < gr->n_vertexes; i++)
			{
				edge_n = g_e(c_v, i, gr);
				if (
					(!visit[i] && gr->adj_m[c_v][i] && (gr->edges[edge_n].stream < gr->edges[edge_n].pass_abl))
					||
					(!visit[i] && (gr->adj_m[i][c_v] && gr->edges[edge_n].pass_abl != 0 && gr->type))
					)
				{
					visit[i] = 1;
					result[j] = i;
					add_e(wave_head, wave_tail, i);
					j++;
				}
			}
		}

		delete[] visit;

		return result;
	}

	bool find_in_vect(int *vect, int num)
	{
		int i = 0;
		while (vect[i] != -1)
		{
			if (vect[i] == num)
				return true;

			i++;
		}

		return false;
	}

	void DFS_Gomory(graph *&gr, int start, int prev, int in, int min)
	{
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			if (gr->adj_m[in][i] && i != prev)
			{
				if (min < gr->streams[in][i])
				{
					gr->streams[start][i] = min;
					gr->streams[i][start] = min;

					// Recurs
					DFS_Gomory(gr, start, in, i, min);
				}
				else
				{
					gr->streams[start][i] = gr->streams[in][i];
					gr->streams[i][start] = gr->streams[in][i];

					// Recurs
					DFS_Gomory(gr, start, in, i, gr->streams[in][i]);
				}
			}
		}
	}

	void Gomory_free(graph *&gr_result, graph **&graphs)
	{
		for (int i = 0; i < gr_result->n_vertexes; i++)
		{
			delete_graph(graphs[i]);
		}
		delete[] * graphs;
		graphs = NULL;
	}

}
