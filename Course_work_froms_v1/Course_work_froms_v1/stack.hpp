#pragma once

#include "stdafx.hpp"

struct T_stack
{
	int data;
	T_stack *prev;
};

/**
* Add element to stack
* @head head of stack
* @data for stack
*/
void add_e(T_stack *&head, int data);

/**
* Get element from stack
* @head head of stack
*/
int get_e(T_stack *&head);
