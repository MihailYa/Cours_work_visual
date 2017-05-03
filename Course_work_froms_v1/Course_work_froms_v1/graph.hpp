#pragma once

#include "stdafx.hpp"
#include "dynamic_array.hpp"
#include "globals.hpp"

/**
* Struct of edge
* @out begin of edge
* @in end of edge
* @stream current stream in edge
* @pass_abl pass able of edge
* @orient if orientation has been selected; //orientation of edge( 0 - just like it is, 1 - otherwide )
*/
struct edge
{
	int out;
	int in;
	int stream;
	union
	{
		int pass_abl;
		int union_vertex;
	};
	bool orient;
};

/**
* Struct of graph
* @type type of graph(1 - oriented, 0 - unoriented)
* @n_vertexes number of vertexes
* @n_edges number of edges
* @v_id array of vertexes ids for each name
* @v_n array of vertexes names for each id
* @edges array of adges
* @adj_m adjacencies matrix
* @streams matrix of streams for each pair of vertexes
*/
struct graph
{
	bool type;
	int n_vertexes;
	int n_edges;
	int *v_id;
	int *v_n;
	edge *edges;
	bool **adj_m;
	int **streams;
};

/**
* Create dynamic graph
* @n_vertexes number of vertex
* @n_edges number of edges
* @or if graph oriented
*/
graph* create_graph(int n_vertexes, int n_edges, bool or = 0);

/**
* Delete dynamic graph
* @gr pointer on graph
*/
void delete_graph(graph *&gr);

/**
* Get number of edge
* @out begin of edge
* @in end of edge
* @gr graph
* @or oriented graph (default = 0)
* @return number of edge
*/
int g_e(int out, int in, graph *gr, bool or = 0);

/**
* Get id of vertex by name
* @name name of vertex
* @gr pointer on gr
* @return id if found and -1 if not found
*/
int g_id(int name, graph *gr);

/**
* Define adjacencies matrix
* @gr graph
* @return pointer on adjacencies matrix
*/
bool** adj(graph *gr);
