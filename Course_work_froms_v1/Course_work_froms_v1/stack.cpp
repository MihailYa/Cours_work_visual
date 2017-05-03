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
		printf("\nError: empty head of stack.\n");
		getch();
		exit(1);
	}

	int data = head->data;

	T_stack *temp;

	temp = head;
	head = head->prev;
	delete temp;

	return data;
}
