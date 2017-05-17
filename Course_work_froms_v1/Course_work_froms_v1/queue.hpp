#pragma once

#include "stdafx.hpp"
#include "globals.hpp"

namespace coursework
{

	/**
	* Structure of queue element
	* @data data of queue
	* @next pointer on next element
	*/
	struct T_queue
	{
		int data;
		T_queue *next;
	};

	/**
	* Add element to queue
	* @param head head of queue
	* @param tail of queue
	* @param data for queue
	*/
	void add_e(T_queue *&head, T_queue *&tail, int data);

	/**
	* Get element from queue
	* @param head head of queue
	* @param tail of queue
	*/
	int get_e(T_queue *&head, T_queue *&tail);

}
