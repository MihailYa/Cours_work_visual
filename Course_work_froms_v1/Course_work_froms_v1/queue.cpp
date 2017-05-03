#include "queue.hpp"

void add_e(T_queue *&head, T_queue *&tail, int data)
{
	T_queue *curr = new T_queue;
	curr->data = data;
	curr->next = NULL;
	
	if (head == NULL)
	{
		head = curr;
		tail = head;
		return;
	}

	tail->next = curr;
	tail = curr;
	return;
}

int get_e(T_queue *&head, T_queue *&tail)
{
	if (head == NULL)
	{
		printf("\nError: empty head of queue.\n");
		getch();
		exit(1);
	}

	int data = head->data;

	if (head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
		return data;
	}

	T_queue *temp;

	temp = head;
	head = head->next;
	delete temp;

	return data;
}
