#pragma once

#include "stdafx.hpp"
#include "graph.hpp"
#include "output.hpp"
#include "dynamic_array.hpp"
#include "globals.hpp"
#include "stack.hpp"

namespace coursework
{

	/**
	* Ford's algorithm
	* @param file_name name of output file
	* @param gr pointer on graph
	* @param in number of Source vertex
	* @param out number of Sink vertex
	* @param iterations get number of iterations
	* @return maximum stream
	*/
	int Ford(const char *file_name, graph *&gr, int &iterations, int in = -1, int out = -1);

	/**
	* Ford's algorithm (output in opened file)
	* @param f pointer on file
	* @param gr pointer on graph
	* @param in number of Source vertex
	* @param out number of Sink vertex
	* @return maximum stream
	*/
	int Ford(FILE **f, graph *&gr, int in = -1, int out = -1);

	/**
	* Define Source and Sink vertexes
	* @param mode 0 - define Sorce, 1 - define Sink
	* @param gr graph
	* @return Source vertex if mode = 0, Sink vertex if mode = 1
	*/
	int def_ss(bool mode, graph *gr);

	/**
	* DFS finding path for Ford algorithm
	* @param gr pointer on graph
	* @param c_v start vertex
	* @param out out vertex
	* @param max current value by wich stream can be changed
	* @param visit array of visited vertexes
	* @param head head of stack
	* @return true if way is found, false if not
	*/
	bool DFS_Ford(graph *gr, int c_v, int out, int &max, bool *visit, T_stack *&head);

	/**
	* Define current stream
	* @param gr pointer on graph
	* @param s_v number of sink vertex
	*/
	int def_stream(graph* gr, int s_v);

	/**
	* Change streams of graph
	* @param gr pointer on graph
	* @param value value by which streams must be changed
	* @param head pointer on stack of way
	* @param f file for output
	*/
	void cg_stream(graph *&gr, int value, T_stack *&head, FILE **f);

}
