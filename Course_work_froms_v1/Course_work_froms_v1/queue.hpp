#pragma once

#include "stdafx.hpp"

struct T_queue
{
	int data;
	T_queue *next;
};

/**
* Add element to queue
* @head head of queue
* @tail of queue
* @data for queue
*/
void add_e(T_queue *&head, T_queue *&tail, int data);

/**
* Get element from queue
* @head head of queue
* @tail of queue
*/
int get_e(T_queue *&head, T_queue *&tail);
