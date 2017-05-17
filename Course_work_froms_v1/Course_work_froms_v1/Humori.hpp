#pragma once

#include "stdafx.hpp"
#include "Ford.hpp"
#include "queue.hpp"
#include "output.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Humori's and Hu's algorithm
	* @file_name name of file for output
	* @gr pointer on graph
	*/
	void Humori(char *file_name, graph *&gr);

	/**
	* Recurse function for Humori & Hu algorithm
	* @gr_result pointer on rebuilded @gr (each vertex of this graph is a graph from @graps array)
	* @graphs array of graphs
	* @ver current graph
	* @f_output file for output
	*/
	void recurs_humori(graph *&gr_result, graph **&graphs, int ver, FILE **f_output);

	/**
	* Check if end of recurse
	* @gr pointer on graph
	* @return true in end, else false
	*/
	bool if_end_recurs(graph *gr);

	/**
	* Find two not union vertexes
	* @gr pointer on graph
	* @return dynamic array with two variables( [0] - first vertex, [1] - second vertex )
	*/
	int* find_not_union_vers(graph *gr);

	/**
	* Find first not union vertexes
	* @gr pointer on graph
	* @return name of not union vertex
	*/
	int find_not_union_ver(graph *gr);

	/**
	* Find union vertex with name @name in @gr
	* @gr pointer on graph
	* @name name of UNION_VERTEX
	*/
	bool find_union_ver(graph *gr, int name);

	/**
	* Change adjacent vertexes
	* @gr_result pointer on graph
	* @graphs array of graphs
	* @ver vertex from wich recurs was start
	* @vect vector of minimum cut
	*/
	void cg_adj(graph *&gr_result, graph **graphs, int ver, int *vect);

	/**
	* Condense graph
	* @gr graph
	* @half 0 - first, 1 - second half
	* @f_output file for output
	* @vect vertexes of minimum cut in graph
	* @ver vertex of UNION_VERTEX
	* @return condense graph
	*/
	graph* condense(graph *&gr, bool half, int *vect, int ver);

	/**
	* Define minimum cut in graph for Source @in and Sink @out
	* @gr pointer on preForeded graph
	* @in number of Source vertex
	* @return id's of vertexes in min cut
	*/
	int* def_min_cut(graph *gr, int in);

	/**
	* Find vertex @num in vector @vect
	* @vect vector
	* @num number of vertex
	* @return true if found, false if not found
	*/
	bool find_in_vect(int *vect, int num);

	/**
	* DFS for finding maximum streams
	* @pointer on graph
	* @start start vertex
	* @prev previous vertex
	* @in start vertex
	* @min minimum stream
	*/
	void DFS_Humori(graph *&gr, int start, int prev, int in, int min);

	/**
	* Free memory
	* @gr_result pointer on result graph
	* @graphs pointer on array of graphs
	*/
	void Humori_free(graph *&gr_result, graph **&graphs);

}
