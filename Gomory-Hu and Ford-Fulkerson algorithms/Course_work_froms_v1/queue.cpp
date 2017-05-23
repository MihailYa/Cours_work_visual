#include "queue.hpp"

namespace coursework
{

	void add_e(T_queue *&head, T_queue *&tail, int data)
	{
		// Create new element
		T_queue *curr = new T_queue;
		curr->data = data;
		curr->next = nullptr;

		// Insert element in head
		if (head == nullptr)
		{
			head = curr;
			tail = head;
			return;
		}

		// Insert element in tail
		tail->next = curr;
		tail = curr;
		return;
	}

	int get_e(T_queue *&head, T_queue *&tail)
	{
		if (head == nullptr)
		{
			T_exception e;
			e.text = "Пуста черга.";
			e.code = 7;
			throw(e);
		}

		int data = head->data;

		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return data;
		}

		T_queue *temp;

		temp = head;
		head = head->next;
		delete temp;

		return data;
	}

}
