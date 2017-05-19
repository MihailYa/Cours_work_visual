#pragma once

#include "stdafx.hpp"
#include "Ford.hpp"
#include "queue.hpp"
#include "output.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Gomory's and Hu's algorithm
	* @param file_name name of file for output
	* @param gr pointer on graph
	*/
	void Gomory(char *file_name, graph *&gr);

	/**
	* Recurse function for Gomory & Hu algorithm
	* @param gr_result pointer on rebuilded @gr (each vertex of this graph is a graph from @graps array)
	* @param graphs array of graphs
	* @param ver current graph
	* @param f_output file for output
	*/
	void recurs_Gomory(graph *&gr_result, graph **&graphs, int ver, FILE **f_output);

	/**
	* Check if end of recurse
	* @param gr pointer on graph
	* @return true in end, else false
	*/
	bool if_end_recurs(graph *gr);

	/**
	* Find two not union vertexes
	* @param gr pointer on graph
	* @return dynamic array with two variables( [0] - first vertex, [1] - second vertex )
	*/
	int* find_not_union_vers(graph *gr);

	/**
	* Find first not union vertexes
	* @param gr pointer on graph
	* @return name of not union vertex
	*/
	int find_not_union_ver(graph *gr);

	/**
	* Find union vertex with name @name in @gr
	* @param gr pointer on graph
	* @param name name of UNION_VERTEX
	*/
	bool find_union_ver(graph *gr, int name);

	/**
	* Change adjacent vertexes
	* @param gr_result pointer on graph
	* @param graphs array of graphs
	* @param ver vertex from wich recurs was start
	* @param vect vector of minimum cut
	*/
	void cg_adj(graph *&gr_result, graph **graphs, int ver, int *vect);

	/**
	* Condense graph
	* @param gr graph
	* @param half 0 - first, 1 - second half
	* @param f_output file for output
	* @param vect vertexes of minimum cut in graph
	* @param ver vertex of "union vertex"
	* @return condense graph
	*/
	graph* condense(graph *&gr, bool half, int *vect, int ver);

	/**
	* Define minimum cut in graph for Source @in and Sink @out
	* @param gr pointer on preForeded graph
	* @param in number of Source vertex
	* @return id's of vertexes in min cut
	*/
	int* def_min_cut(graph *gr, int in);

	/**
	* Find vertex @num in vector @vect
	* @param vect vector
	* @param num number of vertex
	* @return true if found, false if not found
	*/
	bool find_in_vect(int *vect, int num);

	/**
	* DFS for finding maximum streams
	* @param pointer on graph
	* @param start start vertex
	* @param prev previous vertex
	* @param in start vertex
	* @param min minimum stream
	*/
	void DFS_Gomory(graph *&gr, int start, int prev, int in, int min);

	/**
	* Free memory
	* @param gr_result pointer on result graph
	* @param graphs pointer on array of graphs
	*/
	void Gomory_free(graph *&gr_result, graph **&graphs);

}
