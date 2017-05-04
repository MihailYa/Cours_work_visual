#pragma once

#include "stdafx.hpp"
#include "graph.hpp"

/**
* Output graph in file
* @gr pointer on graph
* @f pointer on file
*/
void output(graph *gr, FILE **f);

/**
* Output matrix of streams in file
* @gr pointer on graph
* @f pointer on file
*/
void output_streams(graph *gr, FILE **f);

/**
* Output graph for graphviz
* @gr pointer on graph
* @f pointer on file
* @type if graph is gr_result
*/
void output_graphviz(graph *gr, FILE **f, bool type = false);

/**
* Output graph as image in file_name
* @file_name name of image
* @gr pointer on gr
* @type if graph is gr_result
*/
void graphviz(char *file_name, graph *gr, bool type = false);