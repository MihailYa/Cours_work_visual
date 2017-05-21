#pragma once

#include "graph.hpp"

namespace coursework
{

	/**
	* Input graph from file
	* @param file_name name of file
	* @param gr pointer on graph
	*/
	void input(const char *file_name, graph *&gr);

	/**
	* Input graph from char
	* @param text list of edges
	* @param gr pointer on graph
	*/
	void input_char(const char *text, graph *&gr);

}
