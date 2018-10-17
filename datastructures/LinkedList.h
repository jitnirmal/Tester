#pragma once

#include <iostream>
//https://gist.github.com/harish-r/873ce92a91bb7b685b81

template<typename T>
struct LNode
{
	LNode(const T& data)
		:data(data),
		next(nullptr)
		 {}

	LNode* next;
	T data;
};

template<typename T>
class linkedList
{
public:
	linkedList() :_head(nullptr){}
	~linkedList() {};

	void Append(const T& data)
	{
		LNode<T>* newNode = new LNode<T>(data);

		if (_head == nullptr){
			_head = newNode;
		}
		else{
			LNode<T>* currentNode = _head;
			while (currentNode->next != nullptr){
				currentNode = currentNode->next;
			}
			currentNode->next = newNode;
		}
	}


	void AddAtBegin(const T& data)
	{
		LNode<T>* newNode = new LNode<T>(data);
		if (_head == nullptr)
		{
			_head = newNode;
		}
		else
		{
			newNode->next = _head;
			_head = newNode;
		}
	}

	int count()
	{
		int count = 0;
		LNode<T>* current = _head;
		while (current != NULL)
		{
			current = current->next;
			++count;
		}
		return count;
	}

	void AddAfter(int loc, const T& data) {
		if (count() < loc)
		{
			printf("%s \n", " error, not valid location to insert ** ");
			return;
		}

		LNode<T>* new_node = new LNode<T>(data);
		if (_head == nullptr)
		{
			_head = new_node;
		}
		else
		{
			LNode<T>* current = _head;
			int count = 0;
			while (current->next != NULL && ++count != loc)
			{
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
		}

	}
	void DeleteData(const T& data)
	{
		if (_head == nullptr)
		{
			printf("%s \n", " error, number not found to delete ** ");
			return;
		}
		else
		{
			LNode<T>* current = _head;
			LNode<T>* prev = nullptr;
			while (current != nullptr)
			{
				if (current->data == data)
				{
					LNode<T>* node_to_delete = current;
					if (prev != nullptr) {
						// if it is not the first node
						prev->next = current->next;
					}
					else {
						_head = nullptr;
					}
					delete node_to_delete;
					return;
				}
				prev = current;
				current = current->next;
			}

		}
	}

	void reverse()
	{
		LNode<T>* current = _head;
		LNode<T>* next = nullptr;
		LNode<T>* prev = nullptr;
		while (current)
		{
			next = current->next;
			current->next = prev;

			prev = current;
			current = next;
		}
		_head =  prev;
	}



	void PrintList()
	{
		LNode<T>* currentNode = _head;
		if (currentNode == nullptr)
		{
			printf("%s\n", "list is empty");
			return;
		}
		
		while (currentNode != nullptr) {
			std::cout << " " << currentNode->data;
			currentNode = currentNode->next;
		}
		std::cout <<" **"<< std::endl;
	}

private:
	LNode<T> * _head;
};

/// <summary>
/// check if linked list has loop
/// </summary>
template<typename T>
bool hasLoop(LNode<T>* head) {
	Node* slow = head;
	Node* fast = head;

	while (fast != nullptr && fast.next != nullptr) {
		slow = slow->next;          // 1 hop
		fast = fast->next.next;     // 2 hops 

		if (slow == fast)  // fast caught up to slow, so there is a loop
			return true;
	}
	return false;  // fast reached null, so the list terminates
}

void testLinkList()
{
	std::cout << "---------------------------------" << std::endl;
	linkedList<int> list;
	list.PrintList();

	list.AddAfter(3, 9);
	list.DeleteData(3);
	list.Append(3);
	list.DeleteData(3);
	
	for (int i = 10; i < 20; ++i) {
		list.Append(i);
	}

	for (int i = 8; i >= 0; --i) {
		list.AddAtBegin(i);
	}
	list.PrintList();
	list.AddAfter(9,9);
	list.DeleteData(17);
	list.PrintList();

	list.reverse();
	list.PrintList();

}


