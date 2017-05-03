#include "input.hpp"

void input(const char *file_name, graph *&gr)
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
		if (feof(f))
		{
			exit(1);
		}
		fscanf(f, "%d", &(gr->edges[i].out));
		gr->edges[i].out--;
		fscanf(f, "%d", &(gr->edges[i].in));
		gr->edges[i].in--;
		fscanf(f, "%d", &(gr->edges[i].pass_abl));
		gr->edges[i].stream = 0;
		if(type)
			gr->edges[i].orient = true;
		else
			gr->edges[i].orient = false;
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

void input_char(const char *text, graph *&gr)
{
	int n_vertexes, n_edges;
	bool type;

	char edges[255];
	char *tmp;

	strcpy(edges, text);

	// Read type of graph
	tmp = strtok(edges, " \n");
	type = atoi(tmp);


	// Read number of edges and vertexes
	tmp = strtok(NULL, " \n");
	n_vertexes = atoi(tmp);
	tmp = strtok(NULL, " \n");
	n_edges = atoi(tmp);

	gr = create_graph(n_vertexes, n_edges, type);

	// Fill information about edges
	for (int i = 0; i < gr->n_edges; i++)
	{
		tmp = strtok(NULL, " \n");
		gr->edges[i].out = atoi(tmp);
		gr->edges[i].out--;

		tmp = strtok(NULL, " \n");
		gr->edges[i].in = atoi(tmp);
		gr->edges[i].in--;

		tmp = strtok(NULL, " \n");
		gr->edges[i].pass_abl = atoi(tmp);
		gr->edges[i].in--;

		gr->edges[i].stream = 0;

		if (type)
			gr->edges[i].orient = true;
		else
			gr->edges[i].orient = false;
	}

	for (int i = 0; i < gr->n_vertexes; i++)
	{
		gr->v_n[i] = i + 1;
	}
}
