#pragma once

#include "stdafx.hpp"
#include "graph.hpp"

namespace coursework
{

	/**
	* Input graph from file
	* @file_name name of file
	* @gr pointer on graph
	*/
	void input(const char *file_name, graph *&gr);

	/**
	* Input graph from char
	* @text list of edges
	* @gr pointer on graph
	*/
	void input_char(const char *text, graph *&gr);

}
