#pragma once

#include "stdafx.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Structure of stack data
	* @v id of vertex
	* @orient if we move along edge
	*/
	struct T_stack_dat
	{
		int v;
		bool orient;
	};

	/**
	* Structure of stack element
	* @data data of element
	* @prev pointer on previous element
	*/
	struct T_stack
	{
		T_stack_dat data;
		T_stack *prev;
	};

	/**
	* Add element to stack
	* @param head head of stack
	* @param data for stack
	*/
	void add_e(T_stack *&head, T_stack_dat data);

	/**
	* Get element from stack
	* @param head head of stack
	*/
	T_stack_dat get_e(T_stack *&head);

}