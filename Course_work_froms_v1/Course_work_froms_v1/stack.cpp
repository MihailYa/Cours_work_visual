#include "stack.hpp"

void add_e(T_stack *&head, int data)
{
	T_stack *curr = new T_stack;
	curr->data = data;
	curr->prev = NULL;

	if (head == NULL)
	{
		head = curr;
		return;
	}

	curr->prev = head;
	head = curr;
	return;
}

int get_e(T_stack *&head)
{
	if (head == NULL)
	{
		T_exception e;
		e.text = "Пустий стек.";
		e.code = 8;
		throw(e);
	}

	int data = head->data;

	T_stack *temp;

	temp = head;
	head = head->prev;
	delete temp;

	return data;
}
