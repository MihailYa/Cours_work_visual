#pragma once

#include "stdafx.hpp"
#include "graph.hpp"
#include "output.hpp"
#include "dynamic_array.hpp"
#include "globals.hpp"
#include "stack.hpp"

/**
* Ford's algorithm
* @file_name name of output file
* @gr pointer on graph
* @in number of Source vertex
* @out number of Sink vertex
* @iterations number of iterations
* @return maximum stream
*/
int Ford(const char *file_name, graph *&gr, int &iterations, int in = -1, int out = -1);

/**
* Ford's algorithm (output in opened file)
* @f pointer on file
* @gr pointer on graph
* @in number of Source vertex
* @out number of Sink vertex
* @return maximum stream
*/
int Ford(FILE **f, graph *&gr, int in = -1, int out = -1);

/**
* Define Source and Sink vertexes
* @mode 0 - define Sorce, 1 - define Sink
* @gr graph
* @return Source vertex if mode = 0, Sink vertex if mode = 1
*/
int def_ss(bool mode, graph *gr);

/**
* DFS finding path for Ford algorithm
* @gr pointer on graph
* @c_v start vertex
* @out out vertex
* @max current value by wich stream can be changed
* @visit array of visited vertexes
* @head head of stack
* @return true if way is found, false if not
*/
bool DFS_Ford(graph *gr, int c_v, int out, int &max, bool *visit, T_stack *&head);

/**
* Define current stream
* @gr pointer on graph
* @s_v number of sink vertex
*/
int def_stream(graph* gr, int s_v);

/**
* Change streams of graph
* @gr pointer on graph
* @value value by which streams must be changed
* @head pointer on stack of way
* @f file for output
*/
void cg_stream(graph *&gr, int value, T_stack *&head, FILE **f);
