#include "output.hpp"

void output(graph *gr, FILE **f)
{
	fprintf(*f, " %13s | %9s | %s\n", "Edges", "Pass able", "Current stream");
	for (int i = 0; i < gr->n_edges; i++)
		fprintf(*f, "%5d -> %-5d | %9d | %d\n", gr->v_n[gr->edges[i].out], gr->v_n[gr->edges[i].in], gr->edges[i].pass_abl, gr->edges[i].stream);
}

void output_streams(graph *gr, FILE **f)
{
	fprintf(*f, "%3s", "");
	for (int i = 0; i <= gr->n_vertexes; i++)
	{
		if (i != 0)
			fprintf(*f, "%4d", gr->v_n[i - 1]);
		for (int j = 0; j <= gr->n_vertexes; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					fprintf(*f, " ");
				else
					fprintf(*f, "%4d", gr->v_n[j - 1]);
			}
			else if (j != 0)
			{
				fprintf(*f, "%4d", gr->streams[i - 1][j - 1]);
			}
		}
		fprintf(*f, "\n");
	}
}

void output_graphviz(graph *gr, FILE **f, bool type)
{
	if (type)
	{
		fprintf(*f, "graph G {\n");
		for (int i = 0; i < gr->n_edges; i++)
		{
			fprintf(*f, "T%d -- ", gr->v_n[gr->edges[i].in]);
			fprintf(*f, "T%d", gr->v_n[gr->edges[i].out]);
			fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].stream);

		}
	}
	else if (gr->type)
	{
		fprintf(*f, "digraph G {\n");
		for (int i = 0; i < gr->n_edges; i++)
		{
			if (gr->v_n[gr->edges[i].in] > UNION_VERTEX)
				fprintf(*f, "S%d -> ", gr->v_n[gr->edges[i].in] - UNION_VERTEX);
			else
				fprintf(*f, "%d -> ", gr->v_n[gr->edges[i].in]);

			if (gr->v_n[gr->edges[i].out] > UNION_VERTEX)
				fprintf(*f, "S%d", gr->v_n[gr->edges[i].out] - UNION_VERTEX);
			else
				fprintf(*f, "%d", gr->v_n[gr->edges[i].out]);

			fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].pass_abl);
		}
	}
	else
	{
		fprintf(*f, "graph G {\n");
		for (int i = 0; i < gr->n_edges; i++)
		{
			if (gr->v_n[gr->edges[i].in] > UNION_VERTEX)
				fprintf(*f, "S%d -- ", gr->v_n[gr->edges[i].in] - UNION_VERTEX);
			else
				fprintf(*f, "%d -- ", gr->v_n[gr->edges[i].in]);

			if (gr->v_n[gr->edges[i].out] > UNION_VERTEX)
				fprintf(*f, "S%d", gr->v_n[gr->edges[i].out] - UNION_VERTEX);
			else
				fprintf(*f, "%d", gr->v_n[gr->edges[i].out]);
			fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].pass_abl);
				
		}
	}
	/*for (int i = 0; i < gr->n_vertexes; i++)
	fprintf(*f, "%d;\n", gr->v_n[i]);*/
	fprintf(*f, "}");
}

void graphviz(char *file_name, graph *gr, bool type)
{
	FILE *temp;
	temp = fopen("temp.dot", "wt");
	output_graphviz(gr, &temp, type);
	fclose(temp);
	
	char *param = new char[50];
	strcpy(param, "dot -Tpng temp.dot -o ");
	strcat(param, file_name);
	system(param);
	delete[] param;

	remove("temp.dot");
}
