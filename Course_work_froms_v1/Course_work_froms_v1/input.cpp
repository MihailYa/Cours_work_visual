#include "input.hpp"

void input(const char *file_name, graph *&gr)
{
	FILE *f;

	// Open file
	if ((f = fopen(file_name, "rt")) == NULL)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не можливо відкрити файл ";
		e.text += file_name;
		throw(e);
	}

	int n_vertexes, n_edges;
	int type;

	// Read type of graph
	if (fscanf(f, "%d", &type) <= 0)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}

	// Read number of edges and vertexes
	if (fscanf(f, "%d", &n_vertexes) <= 0 || n_vertexes <= 0)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}
	if(fscanf(f, "%d", &n_edges)<=0 || n_edges <= 0)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}

	gr = create_graph(n_vertexes, n_edges, type);

	// Fill information about edges
	for (int i = 0; i < gr->n_edges; i++)
	{
		if (feof(f))
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
		if (fscanf(f, "%d", &(gr->edges[i].out)) <= 0 || gr->edges[i].out<=0 || gr->edges[i].out > gr->n_vertexes)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
		gr->edges[i].out--;
		if (fscanf(f, "%d", &(gr->edges[i].in)) <= 0 || gr->edges[i].in <= 0 || gr->edges[i].in > gr->n_vertexes)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
		gr->edges[i].in--;
		if (fscanf(f, "%d", &(gr->edges[i].pass_abl)) <= 0 || gr->edges[i].pass_abl <= 0)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
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
		T_exception e;
		e.code = 1;
		e.text = "Не можливо закрити файл ";
		e.text += file_name;
		throw(e);
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
	if (tmp == NULL)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}
	n_vertexes = atoi(tmp);
	tmp = strtok(NULL, " \n");
	if (tmp == NULL)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}
	n_edges = atoi(tmp);

	if (n_vertexes <= 0 || n_edges <=0)
	{
		T_exception e;
		e.code = 1;
		e.text = "Не правильно вказано граф.";
		throw(e);
	}

	gr = create_graph(n_vertexes, n_edges, type);

	// Fill information about edges
	for (int i = 0; i < gr->n_edges; i++)
	{
		tmp = strtok(NULL, " \n");
		if (tmp == NULL || (gr->edges[i].out = atoi(tmp))<=0 || gr->edges[i].out>n_vertexes)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
		gr->edges[i].out--;

		tmp = strtok(NULL, " \n");
		if (tmp == NULL || (gr->edges[i].in = atoi(tmp)) <= 0 || gr->edges[i].in>n_vertexes)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}
		gr->edges[i].in--;

		tmp = strtok(NULL, " \n");
		if (tmp == NULL || (gr->edges[i].pass_abl = atoi(tmp))<=0)
		{
			T_exception e;
			e.code = 1;
			e.text = "Не правильно вказано граф.";
			throw(e);
		}

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
