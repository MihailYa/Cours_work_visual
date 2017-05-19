#pragma once

#include "stdafx.hpp"
#include "graph.hpp"
#include "stdafx.hpp"
#include <graphviz/gvc.h>

namespace coursework
{

	/**
	* Output graph in file
	* @param gr pointer on graph
	* @param f pointer on file
	*/
	void output(graph *gr, FILE **f);

	/**
	* Output matrix of streams in file
	* @param gr pointer on graph
	* @param f pointer on file
	*/
	void output_streams(graph *gr, FILE **f);

	/**
	* Output graph for graphviz
	* @param gr pointer on graph
	* @param type if graph is gr_result
	*/
	std::string output_graphviz(graph *gr, bool type = false);

	/**
	* Output graph as image in file_name
	* @param file_name name of image
	* @param gr pointer on gr
	* @param type if graph is gr_result
	*/
	void graphviz(char *file_name, graph *gr, bool type = false);

}
