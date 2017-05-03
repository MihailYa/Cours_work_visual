#include "Humori.hpp"

void Humori(char *file_name, graph *&gr)
{
	FILE *f;

	// Open file
	if ((f = fopen(file_name, "wt")) == NULL)
	{
		printf("Error opening file %s. Error code: %d\n", file_name, errno);
		getch();
		exit(1);
	}

	gr->type = 0;
	if (gr->adj_m != NULL)
	{
		delete_array<bool>(gr->adj_m, gr->n_vertexes);
		gr->adj_m = adj(gr);
	}

	// Give memory for result graph
	graph *gr_result = create_graph(gr->n_vertexes, gr->n_vertexes - 1);

	// Set that we have one vertex(gr)
	gr_result->n_vertexes = 1;
	gr_result->n_edges = 0;

	// Create array of graphs, each graph is a vertex of gr_result
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

	// Start recurs for gr_result
	recurs_humori(gr_result, graphs, 0, &f);

	// Rebuild result graph
	for (int i = 0; i < gr_result->n_edges; i++)
	{
		gr_result->edges[i].in = g_id(find_not_union_ver(graphs[gr_result->edges[i].in]), gr_result);
		gr_result->edges[i].out = g_id(find_not_union_ver(graphs[gr_result->edges[i].out]), gr_result);
		//----Develop
		printf("%3d -> %3d | %d\n", gr_result->v_n[gr_result->edges[i].in], gr_result->v_n[gr_result->edges[i].out], gr_result->edges[i].stream);
		//----Develop
	}

	for (int i = 0; i < gr_result->n_edges; i++)
		gr_result->edges[i].pass_abl = gr_result->edges[i].stream;

	// Output result graph in file
	fprintf(f, "\n\n\n------------------------------------------------\nResult graph:\n\n");
	output(gr_result, &f);
	graphviz("Humori_result.png", gr_result);

	// Free memory from graphs
	for (int i = 0; i < gr_result->n_vertexes; i++)
	{
		delete_graph(graphs[i]);
	}
	delete[] * graphs;

	// Build streams matrix
	gr_result->streams = create_array<int>(gr_result->n_vertexes, gr_result->n_vertexes);
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

	// Define matrix of streams
	for (int i = 0; i < gr_result->n_vertexes; i++)
		DFS_Humori(gr_result, i, -1, i, INF);

	// Ouput matrix of streams in file
	fprintf(f, "\n\nMatrix of streams:\n");
	output_streams(gr_result, &f);

	//----Develop
	for (int i = 0; i < gr_result->n_vertexes; i++)
	{
		for (int j = 0; j < gr_result->n_vertexes; j++)
			printf("%7d", gr_result->streams[i][j]);
		printf("\n");
	}
	//----Develop

	gr = gr_result;

	// Close file
	if (fclose(f))
	{
		printf("Error with closing the file: %s\n", file_name);
		getch();
		exit(1);
	}
}

int find_not_union_ver(graph *gr)
{

	for (int i = 0; i < gr->n_vertexes; i++)
		for (int i = 0; i < gr->n_vertexes; i++)
			if ((gr->v_n[i] / UNION_VERTEX) < 1)
				return gr->v_n[i];

	return -1;
}

void recurs_humori(graph *&gr_result, graph **&graphs, int ver, FILE **f_output)
{
	// If end of recurs
	if (if_end_recurs(graphs[ver]))
		return;

	fprintf(*f_output, "\n\n\n------------------------------------------------\nCurrent graph (¹%d):\n", gr_result->n_vertexes);
	output(graphs[ver], f_output);
	char *tmp = new char[40];
	char *buf = new char[40];
	itoa(gr_result->n_vertexes, buf, 10);
	strcpy(tmp, "Graph#");
	strcat(tmp, buf);
	strcat(tmp, ".png");
	graphviz(tmp, graphs[ver]);

	//
	// If not end of recurs
	//

	//
	//
	//---------------------------------------------------------
	// Ford for two not UNION_VERTEX

	//Find two not UNION_VERTEX'es
	int *vers = find_not_union_vers(graphs[ver]);
	int max_stream;
	max_stream = Ford(f_output, graphs[ver], vers[0], vers[1]);

	// Recreate adjacent matrix
	for (int i = 0; i < graphs[ver]->n_vertexes; i++)
		for (int j = 0; j < graphs[ver]->n_vertexes; j++)
			if (graphs[ver]->adj_m[i][j])
				graphs[ver]->adj_m[j][i] = 1;

	int *vect;
	vect = def_min_cut(graphs[ver], vers[0]);
	delete[] vers;

	//--------Develop--------
	int k = 0;
	printf("Min cut vector :\n");
	while (vect[k] != -1)
	{
		printf("%d ", graphs[ver]->v_n[vect[k]]);
		k++;
	}
	printf("\n");
	//--------Develop--------

	// Output minimum cut vertexes
	int i = 0;
	fprintf(*f_output, "\nVertex in minimum cut of current graph:\n");
	while (vect[i] != -1)
	{
		fprintf(*f_output, "%d ", graphs[ver]->v_n[vect[i]]);
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
	strcpy(tmp, "Graph#");
	strcat(tmp, buf);
	strcat(tmp, "_first_half.png");
	graphviz(tmp, graphs[gr_result->n_vertexes - 1]);

	// Condense second half of graph (hold vect)
	graphs[gr_result->n_vertexes] = condense(graphs[ver], 1, vect, /*ver*/gr_result->n_vertexes - 1);
	gr_result->n_vertexes++;

	fprintf(*f_output, "\nSecond condensed graph:\n");
	output(graphs[gr_result->n_vertexes - 1], f_output);
	strcpy(tmp, "Graph#");
	strcat(tmp, buf);
	strcat(tmp, "_second_half.png");
	graphviz(tmp, graphs[gr_result->n_vertexes - 1]);
	delete[] tmp;
	delete[] buf;

	//---------------------------------------------------------
	//
	//

	//
	// Rubish (my mistake)
	/*
	// dev: i think it must work
	//
	//
	// ------------New change main graph "gr" by graph with "0" vertex---------------
	// Free memory from old graph which is was given in function
	delete_graph(gr);
	// Set on his(^) place graph which 100% has "0" vertex
	graphs[ver] = graphs[gr_result->n_vertexes - 2];
	// Set on place this(^) graph, second half graph
	graphs[gr_result->n_vertexes - 2] = graphs[gr_result->n_vertexes - 1];
	graphs[gr_result->n_vertexes - 1] = NULL;
	gr_result->n_vertexes--;
	// ------------New change-------------
	//
	//
	*/
	//
	//


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

	//
	//
	//---------------------------------------------------------
	// Add new edge between graphs[ver] and second hapf graphs[last]
	gr_result->edges[gr_result->n_edges].in = ver;
	gr_result->edges[gr_result->n_edges].out = gr_result->n_vertexes - 1;
	gr_result->edges[gr_result->n_edges].stream = max_stream;
	gr_result->edges[gr_result->n_edges].union_vertex = UNION_VERTEX + gr_result->n_vertexes - 1;
	gr_result->n_edges++;
	gr_result->adj_m[ver][gr_result->n_vertexes - 1] = 1;
	gr_result->adj_m[gr_result->n_vertexes - 1][ver] = 1;

	// Change edges of result graph
	cg_adj(gr_result, graphs, ver, vect);

	// Delete minimum cut vector
	delete[] vect;
	//---------------------------------------------------------
	//
	//

	//
	//
	//---------------------------------------------------------
	// Start recurs_humori for second half
	recurs_humori(gr_result, graphs, gr_result->n_vertexes - 1, f_output);

	// Start recurs_humori for first half
	recurs_humori(gr_result, graphs, ver, f_output);
	//---------------------------------------------------------
	//
	//
}

bool if_end_recurs(graph *gr)
{
	// Number of vertexes without UNION_VERTEX
	int num = 0;
	for (int i = 0; i < gr->n_vertexes; i++)
		if ((gr->v_n[i] / UNION_VERTEX) < 1)
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
			if ((gr->v_n[i] / UNION_VERTEX) < 1)
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
		if (gr->v_n[gr->edges[i].in] == name || gr->v_n[gr->edges[i].out] == name)
			return true;

	return false;
}

void cg_adj(graph *&gr_result, graph **graphs, int ver, int *vect)
{
	//-----Develop
	/*printf("\n----------------------\n");
	output(gr_result);

	for (int i = 0; i < gr_result->n_vertexes; i++)
	{
		for (int j = 0; j < gr_result->n_vertexes; j++)
		{
			printf("%2d", gr_result->adj_m[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < gr_result->n_vertexes; i++)
	{
		printf("\nGraphs[%d]:\n", i);
		output(graphs[i]);
	}*/
	//-----Develop

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

		// If first half was moved and hold "i" UNION_VERTEX
		/*if (!find_union_ver(graphs[i], UNION_VERTEX+ver))
		{
		gr_result->adj_m[i][ver] = 0;
		gr_result->adj_m[ver][i] = 0;
		gr_result->adj_m[gr_result->n_vertexes - 1][i] = 1;
		gr_result->adj_m[i][gr_result->n_vertexes - 1] = 1;

		gr_result->edges[g_e(i, ver, gr_result)].in = i;
		gr_result->edges[g_e(i, ver, gr_result)].out = gr_result->n_vertexes - 1;
		}*/
		//if(!find_in_vect)
	}
}

graph* condense(graph *&gr, bool half, int* vect, int ver)
{
	// Give memory for condense graph
	graph *result = create_graph(gr->n_vertexes, gr->n_edges);
	result->n_vertexes = 1;
	result->n_edges = 0;
	// Name of UNION_VERTEX
	result->v_n[0] = UNION_VERTEX + ver;

	// Create adjacent matrix
	if (gr->adj_m == NULL)
		gr->adj_m = adj(gr);

	//-----Develop
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		for (int j = 0; j < gr->n_vertexes; j++)
			printf("%3d", gr->adj_m[i][j]);
		printf("\n");
	}
	//-----Develop

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
						if (gr->v_n[j] == UNION_VERTEX + ver)
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

						if (gr->v_n[j] == UNION_VERTEX + ver)
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

	// Init stream by zero
	for (int i = 0; i < result->n_edges; i++)
		result->edges[i].stream = 0;

	//--------Develop--------
	printf("Half: %d\n", half);
	printf("Vertexes: %d; Edges: %d;\n\nEdges:\nin | out | pass_abl | stream\n", result->n_vertexes, result->n_edges);
	for (int i = 0; i < result->n_edges; i++)
	{
		printf("%d -> %d | %d | %d\n", result->v_n[result->edges[i].in], result->v_n[result->edges[i].out], result->edges[i].pass_abl, result->edges[i].stream);
	}
	printf("\nNumber | Name\n");
	for (int i = 0; i < result->n_vertexes; i++)
	{
		printf("%-2d | %-2d\n", i, result->v_n[i]);
	}
	printf("\n\n");
	//--------Develop--------

	return result;
}

int* def_min_cut(graph* gr, int in)
{
	// Vertor of vertexes of first half of cut
	int* result = new int[gr->n_vertexes];
	T_queue *wave_head = NULL;
	T_queue *wave_tail = NULL;
	// Array of visited vertexes
	bool* visit = new bool[gr->n_vertexes];

	// Init arrays
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
					// When cycle must end
	bool cycle_end = 0;

	// Fill result vector
	while (wave_head != NULL)
	{
		c_v = get_e(wave_head, wave_tail);
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

	/*while (!cycle_end)
	{
	cycle_end = 1;
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
	c_v = i;
	j++;
	cycle_end = 0;
	break;
	}
	}
	}*/

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

void DFS_Humori(graph *&gr, int start, int prev, int in, int min)
{
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		if (gr->adj_m[in][i] && i != prev)
		{
			if (min < gr->streams[in][i])
			{
				gr->streams[start][i] = min;
				gr->streams[i][start] = min;
				DFS_Humori(gr, start, in, i, min);
			}
			else
			{
				gr->streams[start][i] = gr->streams[in][i];
				gr->streams[i][start] = gr->streams[in][i];
				DFS_Humori(gr, start, in, i, gr->streams[in][i]);
			}
		}
	}
}