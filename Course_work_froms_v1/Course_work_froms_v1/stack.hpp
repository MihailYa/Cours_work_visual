#pragma once

#include "stdafx.hpp"
#include "globals.hpp"

namespace coursework
{

	struct T_stack_dat
	{
		int v;
		bool orient;
	};

	struct T_stack
	{
		T_stack_dat data;
		T_stack *prev;
	};

	/**
	* Add element to stack
	* @head head of stack
	* @data for stack
	*/
	void add_e(T_stack *&head, T_stack_dat data);

	/**
	* Get element from stack
	* @head head of stack
	*/
	T_stack_dat get_e(T_stack *&head);

}