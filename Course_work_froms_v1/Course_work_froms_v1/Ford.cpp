#include "Ford.hpp"

int Ford(const char *file_name, graph *&gr, int &iterations, int in, int out)
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

	// Give memory for visited vertexes
	bool *visited = new bool[gr->n_vertexes];
	int cg_value = INF;	// Value by which stream can be changed
	int c_stream;		// Current stream
	int iter = 0;		// Current iteration
	char name_of_file[40];
	char buf[2];

	fprintf(f, "\n--------------Ford_Fulkerson_Begin--------------\n");

	if (gr->adj_m == NULL)
		gr->adj_m = adj(gr);

	// Define Source and Sink
	if (in == -1)
		in = def_ss(0, gr);
	if (out == -1)
		out = def_ss(1, gr);

	if (in == -1 || out == -1)
	{
		T_exception e;
		e.code = 3;
		e.text = "Не можливо знайти стік або джерело мережі.";
		e.solution = "Змініть граф, або вкажіть джерело та стік.";
		throw(e);
	}
	else if (in >= gr->n_vertexes || out >= gr->n_vertexes)
	{
		T_exception e;
		e.code = 3;
		e.text = "Не правильно вказано джерело або стік мережі.";
		throw(e);
	}

	c_stream = def_stream(gr, out);
	fprintf(f, "\n Current stream of web = %d.\nSource vertex: %d.\nSink vertex: %d\n\n", c_stream, gr->v_n[in], gr->v_n[out]);

	// Create stack
	T_stack *head = NULL;

	for (int i = 0; i < gr->n_vertexes; i++)
		visited[i] = false;
	visited[in] = true;

	add_e(head, gr->v_n[in]);

	while (DFS_Ford(gr, in, out, cg_value, visited, head))
	{
		if (iter > MAX_ITER)
		{
			T_exception e;
			e.code = 2;
			e.text = "Алгоритм Форда-Фалкерсона перевищив максимальну кількість ітерацій.";
			e.solution = "Змініть граф, або вкажіть джерело та стік.";
			throw(e);
		}
		// Change streams
		cg_stream(gr, cg_value, head, &f);
		fprintf(f, "\nValued by which streams changed: %d\n", cg_value);
		fprintf(f, "\nCurrent streams:\n");
		output(gr, &f);

		c_stream = def_stream(gr, out);
		fprintf(f, "\n Current stream of web = %d\n\n", c_stream);

		add_e(head, gr->v_n[in]);
		for (int i = 0; i < gr->n_vertexes; i++)
			visited[i] = false;
		visited[in] = true;

		cg_value = INF;

		iter++;
		// Draw current graph
		strcpy(name_of_file, "Ford_Iteration_");
		itoa(iter, buf, 10);
		strcat(name_of_file, buf);
		strcat(name_of_file, ".png");
		graphviz(name_of_file, gr);
	}

	fprintf(f, "\nNew way can't be found.\n Maximum stream = %d.", c_stream);
	delete[] visited;

	fprintf(f, "\n---------------Ford_Fulkerson_End---------------\n");
	if (fclose(f))
	{
		T_exception e;
		e.code = 1;
		e.text = "Не можливо закрити файл ";
		e.text += file_name;
		throw(e);
	}

	iterations = iter;
	return c_stream;
}

int Ford(FILE **f, graph *&gr, int in, int out)
{
	// Give memory for visited vertexes
	bool *visited = new bool[gr->n_vertexes];
	int cg_value = INF;	// Value by which stream can be changed
	int c_stream;		// Current stream
	int iter = 0;		// Current iteration

	fprintf(*f, "\n--------------Ford Fulkerson Begin--------------\n");

	if (gr->adj_m == NULL)
		gr->adj_m = adj(gr);

	// Define Source and Sink
	if (in == -1)
		in = def_ss(0, gr);
	if (out == -1)
		out = def_ss(1, gr);

	if (in == -1 || out == -1)
	{
		T_exception e;
		e.code = 3;
		e.text = "Не можливо знайти стік або джерело мережі.";
		e.solution = "Змініть граф, або вкажіть джерело та стік.";
		throw(e);
	}

	c_stream = def_stream(gr, out);
	fprintf(*f, "\n Current stream of web = %d.\nSource vertex: %d.\nSink vertex: %d.\n\n", c_stream, gr->v_n[in], gr->v_n[out]);

	// Create stack
	T_stack *head = NULL;

	for (int i = 0; i < gr->n_vertexes; i++)
		visited[i] = false;
	visited[in] = true;

	add_e(head, gr->v_n[in]);

	while (DFS_Ford(gr, in, out, cg_value, visited, head))
	{
		if (iter > MAX_ITER)
		{
			int e = 5;
			throw(e);
		}

		// Change streams
		cg_stream(gr, cg_value, head, f);
		fprintf(*f, "\nValued by which streams changed: %d\n", cg_value);
		fprintf(*f, "\nCurrent streams:\n");
		output(gr, f);

		c_stream = def_stream(gr, out);
		fprintf(*f, "\n Current stream of web = %d\n\n", c_stream);

		add_e(head, gr->v_n[in]);
		for (int i = 0; i < gr->n_vertexes; i++)
			visited[i] = false;
		visited[in] = true;
		iter++;
		cg_value = INF;
	}

	fprintf(*f, "\nNew way can't be found.\n Maximum stream = %d.", c_stream);
	delete[] visited;

	fprintf(*f, "\n---------------Ford Fulkerson End---------------\n");

	return c_stream;
}

bool DFS_Ford(graph *gr, int c_v, int out, int &max, bool *visit, T_stack *&head)
{
	if (c_v == out)
		return true;

	int temp = max;
	int edge_n; // Current edge
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		edge_n = g_e(c_v, i, gr);

		if (!visit[i] && gr->adj_m[c_v][i] && (gr->edges[edge_n].stream < gr->edges[edge_n].pass_abl))
		{
			// Fix orientation of undirected graph
			if (!gr->type && !gr->edges[edge_n].orient)
			{
				gr->edges[edge_n].orient = true;
				gr->adj_m[i][c_v] = 0;
			}

			// Add vertex to stack
			add_e(head, gr->v_n[i]);
			visit[i] = true;

			// Change max if needed
			if (gr->edges[edge_n].pass_abl - gr->edges[edge_n].stream < max)
				max = gr->edges[edge_n].pass_abl - gr->edges[edge_n].stream;

			// Recurs
			if (DFS_Ford(gr, i, out, max, visit, head))
				return true;
			else
			{
				max = temp;
				get_e(head);
				visit[i] = false;
			}
		}
		else if (!visit[i] && (gr->adj_m[i][c_v] && gr->edges[edge_n].pass_abl != 0))
		{
			// Add vertex to stack
			add_e(head, -gr->v_n[i]);
			visit[i] = true;

			// Change max if needed
			if (gr->edges[edge_n].stream < max)
				max = gr->edges[edge_n].stream;

			// Recurs
			if (DFS_Ford(gr, i, out, max, visit, head))
				return true;
			else
			{
				max = temp;
				get_e(head);
				visit[i] = false;
			}
		}
	}
	
	return false;
}

int def_ss(bool mode, graph *gr)
{
	bool check;
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		check = 1;
		for (int j = 0; j < gr->n_vertexes; j++)
		{
			if ((!mode && gr->adj_m[j][i]) || (mode && gr->adj_m[i][j]))
				check = 0;
		}
		if (check) return i;
	}

	return -1;
}

int def_stream(graph* gr, int s_v)
{
	int sum = 0;
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		if (gr->adj_m[i][s_v])
			sum += gr->edges[g_e(i, s_v, gr)].stream;
	}
	return sum;
}

void cg_stream(graph *&gr, int value, T_stack *&head, FILE **f)
{
	int out;
	int in = get_e(head);
	fprintf(*f, "\nFound way:\n");
	while (head != NULL)
	{
		out = in;
		in = get_e(head);
		if (out < 0)
		{
			fprintf(*f, "%d -> ", abs(out));
			gr->edges[g_e(g_id(abs(out), gr), g_id(abs(in), gr), gr)].stream -= value;
		}
		else
		{
			fprintf(*f, "%d <- ", out);
			gr->edges[g_e(g_id(out, gr), g_id(abs(in), gr), gr)].stream += value;
		}
	}
	fprintf(*f, "%d\n", in);
}
