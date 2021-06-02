#pragma once
#include "list.h"

template <class Data>
class Queue
{
private:

	class queueNode 
	{
	public:
		Data data;
		queueNode* next;

		queueNode(Data data = nullptr, queueNode* next = nullptr)
		{
			this->data = data;
			this->next = next;
		};
	};

public:
	queueNode* head;
	queueNode* tail;
	unsigned int size;

	Queue() 
	{
		tail = nullptr;
		head = nullptr;
		size = 0;
	}

	~Queue() 
	{
		clear();
	}

	void clear() 
	{
		while (size != 0)
		{
			pop();
		}
	}

	void push(Data data) 
	{
		if (size == 0) {
			head = new queueNode(data);
			tail = head;
		}
		else {
			tail->next = new queueNode(data);
			tail = tail->next;
		}
		size++;
	}

	void pop() 
	{
		if (size == 0) {
			return;
		}
		if (size == 1) {
			delete head;
			reset_list();
		}
		else {
			queueNode* current = head;
			head = head->next;
			delete current;
		}
		size--;
	}

	Data first() 
	{
		return head->data;
	}

	bool empty()
	{
		return !size;
	}

	void reset_list()
	{
		head = nullptr;
		tail = nullptr;
	}
};