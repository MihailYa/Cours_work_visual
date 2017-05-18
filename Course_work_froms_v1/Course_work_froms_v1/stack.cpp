#include "stack.hpp"

namespace coursework
{

	void add_e(T_stack *&head, T_stack_dat data)
	{
		// Create new element
		T_stack *curr = new T_stack;
		curr->data = data;
		curr->prev = NULL;

		// Insert element in head
		if (head == NULL)
		{
			head = curr;
			return;
		}

		curr->prev = head;
		head = curr;
		return;
	}

	T_stack_dat get_e(T_stack *&head)
	{
		if (head == NULL)
		{
			T_exception e;
			e.text = "Пустий стек.";
			e.code = 8;
			throw(e);
		}

		T_stack_dat data = head->data;

		T_stack *temp;

		temp = head;
		head = head->prev;
		delete temp;

		return data;
	}

}
