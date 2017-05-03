#include "graph.hpp"

graph* create_graph(int n_vertexes, int n_edges, bool or )
{
	graph *result = new graph;
	result->edges = new edge[n_edges];
	//result->v_id = new int[n_vertexes + 1];
	result->v_n = new int[n_vertexes];
	result->n_vertexes = n_vertexes;
	result->n_edges = n_edges;
	result->type = or ;

	result->adj_m = NULL;
	result->streams = NULL;
	//result->adj_m = create_array<int>(n_vertexes, n_vertexes);
	//result->streams = create_array<int>(n_vertexes, n_vertexes);

	for (int i = 0; i < n_vertexes; i++)
	{
		//result->v_id[i] = -1;
		result->v_n[i] = -1;
	}

	for (int i = 0; i < n_edges; i++)
	{
		result->edges[i].orient = false;
	}
	//result->v_id[n_vertexes] = -1;

	return result;
}

void delete_graph(graph *&gr)
{
	delete[] gr->edges;
	//delete gr->v_id;
	delete[] gr->v_n;
	if (gr->adj_m != NULL)
		delete_array(gr->adj_m, gr->n_vertexes);
	if (gr->streams != NULL)
		delete_array(gr->streams, gr->n_vertexes);

	delete[] gr;
	gr = NULL;
}

int g_e(int out, int in, graph *gr, bool or )
{
	for (int i = 0; i < gr->n_edges; i++)
		if ((gr->edges[i].out == out && gr->edges[i].in == in) || (!or && gr->edges[i].out == in && gr->edges[i].in == out))
			return i;

	return -1;
}

int g_id(int name, graph *gr)
{
	for (int i = 0; i < gr->n_vertexes; i++)
	{
		if (gr->v_n[i] == name)
			return i;
	}

	return -1;
}

bool** adj(graph *gr)
{
	bool **sum_matrix = create_array<bool>(gr->n_vertexes, gr->n_vertexes);
	// Init by 0
	for (int i = 0; i < gr->n_vertexes; i++)
		for (int j = 0; j < gr->n_vertexes; j++)
			sum_matrix[i][j] = 0;

	// Define
	for (int i = 0; i < gr->n_edges; i++)
	{
		sum_matrix[gr->edges[i].out][gr->edges[i].in] = 1;
		if (!gr->type)
			sum_matrix[gr->edges[i].in][gr->edges[i].out] = 1;
	}


	//--------------Develop--------------
	// Output matrix
	printf("%2s", "");
	for (int i = 0; i <= gr->n_vertexes; i++)
	{
		if (i != 0)
			printf("%3d", i);
		for (int j = 0; j <= gr->n_vertexes; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					printf(" ");
				else
					printf("%3d", j);
			}
			else if (j != 0)
			{
				printf("%3d", sum_matrix[i - 1][j - 1]);
			}
		}
		printf("\n");
	}
	//--------------Develop--------------

	return sum_matrix;
}
