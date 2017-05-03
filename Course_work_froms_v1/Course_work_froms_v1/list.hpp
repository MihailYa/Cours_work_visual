#pragma once
#include "stdafx.hpp"

struct T_list
{
	std::string data;
	T_list *next;
	T_list *prev;
};

void add_e(T_list *&head, T_list *&tail, std::string dat);

void free_list(T_list *&head, T_list *&tail);
