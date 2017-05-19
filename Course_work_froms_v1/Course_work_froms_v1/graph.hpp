#pragma once

#include "stdafx.hpp"
#include "dynamic_array.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Structure of edge
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
	* Structure of vertex
	* @v name of vertex
	* @union_v if vertex is union
	*/
	struct T_vertex
	{
		int v;
		bool union_v;
	};

	/**
	* Structure of graph
	* @type type of graph(1 - oriented, 0 - unoriented)
	* @n_vertexes number of vertexes
	* @n_edges number of edges
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
		//int *v_n;
		T_vertex *v_n;
		edge *edges;
		bool **adj_m;
		int **streams;
	};

	/**
	* Create dynamic graph
	* @param n_vertexes number of vertex
	* @param n_edges number of edges
	* @param or if graph oriented
	*/
	graph* create_graph(int n_vertexes, int n_edges, bool or = 0);

	/**
	* Delete dynamic graph
	* @param gr pointer on graph
	*/
	void delete_graph(graph *&gr);

	/**
	* Get number of edge
	* @param out end of edge
	* @param in begin of edge
	* @param gr graph
	* @param or oriented graph (default = 0)
	* @return number of edge
	*/
	int g_e(int out, int in, graph *gr, bool or = 0);

	/**
	* Get id of vertex by name
	* @param ver vertex info
	* @param gr pointer on gr
	* @return id if found and -1 if not found
	*/
	int g_id(T_vertex ver, graph *gr);

	/**
	* Get name of vertex
	* @param ver data of vertex
	* @param buf char buffer
	* @return view of vertex for output
	*/
	char* g_n(T_vertex ver, char *buf);

	/**
	* Define adjacencies matrix
	* @param gr graph
	* @return pointer on adjacencies matrix
	*/
	bool** adj(graph *gr);

}
