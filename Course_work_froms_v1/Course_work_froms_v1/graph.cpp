#include "graph.hpp"

graph* create_graph(int n_vertexes, int n_edges, bool or )
{
	graph *result = new graph;
	result->edges = new edge[n_edges];
	result->v_n = new int[n_vertexes];
	result->n_vertexes = n_vertexes;
	result->n_edges = n_edges;
	result->type = or ;

	result->adj_m = NULL;
	result->streams = NULL;

	for (int i = 0; i < n_vertexes; i++)
	{
		result->v_n[i] = -1;
	}

	for (int i = 0; i < n_edges; i++)
	{
		result->edges[i].orient = false;
	}

	return result;
}

void delete_graph(graph *&gr)
{
	delete[] gr->edges;
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

	return sum_matrix;
}
