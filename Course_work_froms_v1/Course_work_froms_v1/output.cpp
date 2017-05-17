#include "output.hpp"

using namespace std;

namespace coursework
{

	void output(graph *gr, FILE **f)
	{
		fprintf(*f, " %13s | %9s | %s\n", "Edges", "Pass able", "Current stream");
		char tmp[20];
		for (int i = 0; i < gr->n_edges; i++)
			if (gr->v_n[gr->edges[i].out].union_v || gr->v_n[gr->edges[i].in].union_v)
				if (gr->v_n[gr->edges[i].out].union_v)
				{
					sprintf(tmp, "S%d", gr->v_n[gr->edges[i].out].v);
					fprintf(*f, "%5s -> %-5d | %9d | %d\n", tmp, gr->v_n[gr->edges[i].in].v, gr->edges[i].pass_abl, gr->edges[i].stream);
				}
				else
					fprintf(*f, "%5d -> S%-4d | %9d | %d\n", gr->v_n[gr->edges[i].out].v, gr->v_n[gr->edges[i].in].v, gr->edges[i].pass_abl, gr->edges[i].stream);
			else
				fprintf(*f, "%5d -> %-5d | %9d | %d\n", gr->v_n[gr->edges[i].out].v, gr->v_n[gr->edges[i].in].v, gr->edges[i].pass_abl, gr->edges[i].stream);
	}

	void output_streams(graph *gr, FILE **f)
	{
		fprintf(*f, "%3s", "");
		for (int i = 0; i <= gr->n_vertexes; i++)
		{
			if (i != 0)
				fprintf(*f, "%4d", gr->v_n[i - 1].v);
			for (int j = 0; j <= gr->n_vertexes; j++)
			{
				if (i == 0)
				{
					if (j == 0)
						fprintf(*f, " ");
					else
						fprintf(*f, "%4d", gr->v_n[j - 1].v);
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
				fprintf(*f, "T%d -- ", gr->v_n[gr->edges[i].in].v);
				fprintf(*f, "T%d", gr->v_n[gr->edges[i].out].v);
				fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].stream);

			}
		}
		else if (gr->type)
		{
			fprintf(*f, "digraph G {\n");
			for (int i = 0; i < gr->n_edges; i++)
			{
				if (gr->v_n[gr->edges[i].in].union_v)
					fprintf(*f, "S%d -> ", gr->v_n[gr->edges[i].in].v);
				else
					fprintf(*f, "%d -> ", gr->v_n[gr->edges[i].in].v);

				if (gr->v_n[gr->edges[i].out].union_v)
					fprintf(*f, "S%d", gr->v_n[gr->edges[i].out].v);
				else
					fprintf(*f, "%d", gr->v_n[gr->edges[i].out].v);

				fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].pass_abl);
			}
		}
		else
		{
			fprintf(*f, "graph G {\n");
			for (int i = 0; i < gr->n_edges; i++)
			{
				if (gr->v_n[gr->edges[i].in].union_v)
					fprintf(*f, "S%d -- ", gr->v_n[gr->edges[i].in].v);
				else
					fprintf(*f, "%d -- ", gr->v_n[gr->edges[i].in].v);

				if (gr->v_n[gr->edges[i].out].union_v)
					fprintf(*f, "S%d", gr->v_n[gr->edges[i].out].v);
				else
					fprintf(*f, "%d", gr->v_n[gr->edges[i].out].v);
				fprintf(*f, " [label=\" %d/%d \"];\n", gr->edges[i].stream, gr->edges[i].pass_abl);

			}
		}
		/*for (int i = 0; i < gr->n_vertexes; i++)
		fprintf(*f, "%d;\n", gr->v_n[i]);*/
		fprintf(*f, "}");
	}

	string output_graphviz(graph *gr, bool type)
	{
		std::string res;
		if (type)
		{
			res = "graph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				res += "T";
				res += to_string(gr->v_n[gr->edges[i].in].v);
				res += " -- ";
				res += "T";
				res += to_string(gr->v_n[gr->edges[i].out].v);
				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].stream);
				res += " \"];\n";
			}
		}
		else if (gr->type)
		{
			res = "digraph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				if (gr->v_n[gr->edges[i].in].union_v)
				{
					res += "S";
					res += to_string(gr->v_n[gr->edges[i].in].v);
					res += " -> ";
				}
				else
				{
					res += to_string(gr->v_n[gr->edges[i].in].v);
					res += " -> ";
				}

				if (gr->v_n[gr->edges[i].out].union_v)
				{
					res += "S";
					res += to_string(gr->v_n[gr->edges[i].out].v);
				}
				else
				{
					res += to_string(gr->v_n[gr->edges[i].out].v);
				}
				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].pass_abl);
				res += " \"];\n";
			}
		}
		else
		{
			res = "graph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				if (gr->v_n[gr->edges[i].in].union_v)
				{
					res += "S";
					res += to_string(gr->v_n[gr->edges[i].in].v);
					res += " -- ";
				}
				else
				{
					res += to_string(gr->v_n[gr->edges[i].in].v);
					res += " -- ";
				}

				if (gr->v_n[gr->edges[i].out].union_v)
				{
					res += "S";
					res += to_string(gr->v_n[gr->edges[i].out].v);
				}
				else
				{
					res += to_string(gr->v_n[gr->edges[i].out].v);
				}
				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].pass_abl);
				res += " \"];\n";
			}
		}

		res += "}";

		return res;
	}

	void graphviz(char *file_name, graph *gr, bool type)
	{
		std::string inp;

		inp = output_graphviz(gr, type);

		GVC_t *gvc;
		gvc = gvContext();

		Agraph_t *g;
		g = agmemread(inp.c_str());

		gvLayout(gvc, g, "dot");
		gvRenderFilename(gvc, g, "png", file_name);
		gvFreeLayout(gvc, g);

		agclose(g);

		gvFreeContext(gvc);
	}

}
