#include "input.hpp"

void input(char *file_name, graph *&gr)
{
	FILE *f;

	// Open file
	if ((f = fopen(file_name, "rt")) == NULL)
	{
		printf("Error opening file %s. Error code: %d\n", file_name, errno);
		getch();
		exit(1);
	}

	int n_vertexes, n_edges;
	int type;

	// Read type of graph
	fscanf(f, "%d", &type);

	// Read number of edges and vertexes
	fscanf(f, "%d", &n_vertexes);
	fscanf(f, "%d", &n_edges);

	gr = create_graph(n_vertexes, n_edges, type);

	// Fill information about edges
	for (int i = 0; i < gr->n_edges; i++)
	{
		fscanf(f, "%d", &(gr->edges[i].out));
		gr->edges[i].out--;
		fscanf(f, "%d", &(gr->edges[i].in));
		gr->edges[i].in--;
		fscanf(f, "%d", &(gr->edges[i].pass_abl));
		gr->edges[i].stream = 0;
	}

	for (int i = 0; i < gr->n_vertexes; i++)
	{
		gr->v_n[i] = i + 1;
	}

	if (fclose(f))
	{
		printf("Error with closing the file: %s\n", file_name);
		getch();
		exit(1);
	}
}
