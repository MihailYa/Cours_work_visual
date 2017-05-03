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
*/
void output_graphviz(graph *gr, FILE **f);

/**
* Output graph as image in file_name
* @file_name name of image
* @gr pointer on gr
*/
void graphviz(char *file_name, graph *gr);
