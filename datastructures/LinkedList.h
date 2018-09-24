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

	void AddItem(const T& data)
	{
		LNode* node = new LNode(data);

		if (_head == nullptr){
			_head = node;
		}
		else{
			LNode* currentNode = _head;
			while (currentNode->next != nullptr){
				currentNode = currentNode->next;
			}
			currentNode->next = node;
		}
	}

	void PrintList()
	{
		LNode* currentNode = _head;
		while (currentNode->next != nullptr) {
			std::cout << " " << currentNode->data;
			currentNode = currentNode->next;
		}
		std::cout << std::endl;
	}

private:
	LNode * _head;
};