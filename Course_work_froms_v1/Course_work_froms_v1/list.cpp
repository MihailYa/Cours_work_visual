#include "list.hpp"

void add_e(T_list *&head, T_list *&tail, std::string dat)
{
	T_list *temp = new T_list;
	temp->data = dat;
	temp->next = NULL;
	temp->prev = NULL;

	if (head == NULL)
	{
		head = temp;
		temp->next = temp;
		temp->prev = temp;
		tail = temp;
		return;
	}

	if (head == tail)
	{
		tail = temp;
		head->next = temp;
		head->prev = temp;
		temp->next = head;
		temp->prev = head;
		return;
	}

	tail->next = temp;
	temp->prev = tail;
	temp->next = head;
	head->prev = temp;
	tail = temp;
}

void free_list_(T_list *&head, T_list *&tail)
{
	if (head == NULL)
		return;

	T_list *temp;
	while (head != tail)
	{
		temp = head->next;
		delete[] head;
		head = temp;
	}

	delete[] head;
	head = NULL;
	tail = NULL;
}
