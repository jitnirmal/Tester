#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <stack>
//https://codereview.stackexchange.com/questions/201368/modern-c-singly-linked-list

template<typename T>
struct Node
{
	Node(const T& data, Node* next = nullptr) noexcept: 
		Data(data)
		,Next(next) {}

	T Data;
	Node* Next;
};

template<typename T>
class LinkedList
{
public:
	using NodeType = Node<T>;
	
	class iterator
	{
	public:
		
		iterator(NodeType* ptr = nullptr) :
			ptr_(ptr) 
		{
		}

		iterator operator++() // PREFIX
		{ 
			ptr_=ptr_->Next; 
			return *this; 
		} 
		
		iterator operator++(int junk)// POSTFIX
		{ 
			iterator current = *this;
			ptr_ = ptr_->Next;
			return current; 
		} 

		NodeType& operator*()
		{ 
			return *ptr_; 
		}
		
		NodeType* operator->()
		{ 
			return ptr_; 
		}

		bool operator==(const iterator& rhs) const
		{ 
			return ptr_ == rhs.ptr_; 
		}

		bool operator!=(const iterator& rhs) const
		{ 
			return ptr_ != rhs.ptr_; 
		}
	private:
		NodeType* ptr_;
	};



	LinkedList(NodeType* list = nullptr) :list_(list), size_(0){}
	
	LinkedList(const std::initializer_list<T>& list)
		:list_(nullptr), size_(0)
	{
		for (const auto& item : list)
		{
			emplace_back(item);
		}
	}

	LinkedList(const LinkedList& other)
		:list_(nullptr), size_(0) 
	{
		auto current = other.list_;
		while (current)
		{
			emplace_back(current->Data);
			current = current->Next;
		}
	}
	
	LinkedList& operator=(const LinkedList& other)
	{
		if (this != &other)
		{
			for (const auto& item : other)
			{
				emplace_back(item);
			}
		}
		return *this;
	}

	~LinkedList()
	{
		auto current = list_;
		std::cout << "destroying list : ";
		while (current)
		{
			auto deletionNode = current;
			current = current->Next;
			std::cout << deletionNode->Data << " ";
			delete deletionNode;
		}
	}

	NodeType* getNode(const T& data)
	{
		return new NodeType(data);
	}

	void push_back(const T& data)
	{
		auto node = getNode(data);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}

	void reverse()
	{
		NodeType* current = list_;
		NodeType* next = nullptr;
		NodeType* prev = nullptr;

		while (current)
		{
			next = current->Next;
			current->Next = prev;
			
			prev = current;
			current = next;
		}
		list_ = prev;
	}

	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		auto node = new NodeType(std::forward<Args>(args)...);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}
	
	iterator begin()
	{
		return iterator(list_);
	}
	
	iterator end()
	{
		auto current = list_;
		while (current)
		{
			current = current->Next;
		}
		return iterator(current);
	}

	size_t size()
	{
		return size_;
	}

private:
	NodeType* list_;
	size_t size_;
};

#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <stack>
//https://codereview.stackexchange.com/questions/201368/modern-c-singly-linked-list

template<typename T>
struct Node
{
	Node(const T& data, Node* next = nullptr) noexcept: 
		Data(data)
		,Next(next) {}

	T Data;
	Node* Next;
};

template<typename T>
class LinkedList
{
public:
	using NodeType = Node<T>;
	
	class iterator
	{
	public:
		
		iterator(NodeType* ptr = nullptr) :
			ptr_(ptr) 
		{
		}

		iterator operator++() // PREFIX
		{ 
			ptr_=ptr_->Next; 
			return *this; 
		} 
		
		iterator operator++(int junk)// POSTFIX
		{ 
			iterator current = *this;
			ptr_ = ptr_->Next;
			return current; 
		} 

		NodeType& operator*()
		{ 
			return *ptr_; 
		}
		
		NodeType* operator->()
		{ 
			return ptr_; 
		}

		bool operator==(const iterator& rhs) const
		{ 
			return ptr_ == rhs.ptr_; 
		}

		bool operator!=(const iterator& rhs) const
		{ 
			return ptr_ != rhs.ptr_; 
		}
	private:
		NodeType* ptr_;
	};



	LinkedList(NodeType* list = nullptr) :list_(list), size_(0){}
	
	LinkedList(const std::initializer_list<T>& list)
		:list_(nullptr), size_(0)
	{
		for (const auto& item : list)
		{
			emplace_back(item);
		}
	}

	LinkedList(const LinkedList& other)
		:list_(nullptr), size_(0) 
	{
		auto current = other.list_;
		while (current)
		{
			emplace_back(current->Data);
			current = current->Next;
		}
	}
	
	LinkedList& operator=(const LinkedList& other)
	{
		if (this != &other)
		{
			for (const auto& item : other)
			{
				emplace_back(item);
			}
		}
		return *this;
	}

	~LinkedList()
	{
		auto current = list_;
		std::cout << "destroying list : ";
		while (current)
		{
			auto deletionNode = current;
			current = current->Next;
			std::cout << deletionNode->Data << " ";
			delete deletionNode;
		}
	}

	NodeType* getNode(const T& data)
	{
		return new NodeType(data);
	}

	void push_back(const T& data)
	{
		auto node = getNode(data);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}

	void reverse()
	{
		NodeType* current = list_;
		NodeType* next = nullptr;
		NodeType* prev = nullptr;

		while (current)
		{
			next = current->Next;
			current->Next = prev;
			
			prev = current;
			current = next;
		}
		list_ = prev;
	}

	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		auto node = new NodeType(std::forward<Args>(args)...);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}
	
	iterator begin()
	{
		return iterator(list_);
	}
	
	iterator end()
	{
		auto current = list_;
		while (current)
		{
			current = current->Next;
		}
		return iterator(current);
	}

	size_t size()
	{
		return size_;
	}

private:
	NodeType* list_;
	size_t size_;
};

std::string rotate(const std::string str)
{
	std::string result(str);
	auto len = str.size()-1;
	for (size_t index = 0; index < str.size()-1; ++index)
	{
		result[len - index] = result[len - index -1];
	}
	result[0] = str[str.size() - 1];
	return result;
}

void permute(std::string str, std::string out)
{
	if (str.size() == 0)
	{
		return;
	}

	for (int i = 0; i < str.size(); i++)
	{
		permute(str.substr(1), out + str[0]);
		rotate(str.begin(), str.begin() + 1, str.end());
	}
}

auto maxPeopleEntrySlot()
{
	std::string str = "nirmal";
	for (size_t index = 0; index < str.size(); ++index)
	{
		str = rotate(str);
	}

	std::vector<int> in = { 1, 2, 9, 5, 5 };
	std::vector<int> out= { 4, 5, 12, 9, 12 };

	std::vector<int> timeRegistor(24,0);

	for (size_t i = 0 ; i < in.size(); ++i )
	{
		for (int j = in[i]; j < out[i]-1; ++j)
			timeRegistor[j]++;
	}

	auto maxSlot = std::max_element(timeRegistor.begin(), timeRegistor.end());
	std::cout << "max element at: " << std::distance(timeRegistor.begin(), maxSlot) << '\n';

	std::vector<int> result;
	for (size_t i = 0; i < timeRegistor.size(); ++i)
	{
		if (timeRegistor[i] == *maxSlot)
		{
			result.emplace_back(i);
		}
	}
	return result;
}

int main()
{
	try 
	{
		auto slots = maxPeopleEntrySlot();

		LinkedList<int> lt = {1,2,3,4,5,6,7};
		LinkedList<int> lt2 = lt;

		auto printList = []( LinkedList<int>& list)
		{
			std::cout << "size is  " << list.size() <<std::endl;
			for (const auto& item : list)
			{
				std::cout << item.Data << " " ;
			}
			std::cout << std::endl;
		};

		lt2.reverse();
		printList(lt2);
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception during testing..." << std::endl;
	}
}#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <stack>
//https://codereview.stackexchange.com/questions/201368/modern-c-singly-linked-list

template<typename T>
struct Node
{
	Node(const T& data, Node* next = nullptr) noexcept: 
		Data(data)
		,Next(next) {}

	T Data;
	Node* Next;
};

template<typename T>
class LinkedList
{
public:
	using NodeType = Node<T>;
	
	class iterator
	{
	public:
		
		iterator(NodeType* ptr = nullptr) :
			ptr_(ptr) 
		{
		}

		iterator operator++() // PREFIX
		{ 
			ptr_=ptr_->Next; 
			return *this; 
		} 
		
		iterator operator++(int junk)// POSTFIX
		{ 
			iterator current = *this;
			ptr_ = ptr_->Next;
			return current; 
		} 

		NodeType& operator*()
		{ 
			return *ptr_; 
		}
		
		NodeType* operator->()
		{ 
			return ptr_; 
		}

		bool operator==(const iterator& rhs) const
		{ 
			return ptr_ == rhs.ptr_; 
		}

		bool operator!=(const iterator& rhs) const
		{ 
			return ptr_ != rhs.ptr_; 
		}
	private:
		NodeType* ptr_;
	};



	LinkedList(NodeType* list = nullptr) :list_(list), size_(0){}
	
	LinkedList(const std::initializer_list<T>& list)
		:list_(nullptr), size_(0)
	{
		for (const auto& item : list)
		{
			emplace_back(item);
		}
	}

	LinkedList(const LinkedList& other)
		:list_(nullptr), size_(0) 
	{
		auto current = other.list_;
		while (current)
		{
			emplace_back(current->Data);
			current = current->Next;
		}
	}
	
	LinkedList& operator=(const LinkedList& other)
	{
		if (this != &other)
		{
			for (const auto& item : other)
			{
				emplace_back(item);
			}
		}
		return *this;
	}

	~LinkedList()
	{
		auto current = list_;
		std::cout << "destroying list : ";
		while (current)
		{
			auto deletionNode = current;
			current = current->Next;
			std::cout << deletionNode->Data << " ";
			delete deletionNode;
		}
	}

	NodeType* getNode(const T& data)
	{
		return new NodeType(data);
	}

	void push_back(const T& data)
	{
		auto node = getNode(data);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}

	void reverse()
	{
		NodeType* current = list_;
		NodeType* next = nullptr;
		NodeType* prev = nullptr;

		while (current)
		{
			next = current->Next;
			current->Next = prev;
			
			prev = current;
			current = next;
		}
		list_ = prev;
	}

	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		auto node = new NodeType(std::forward<Args>(args)...);
		if (!list_)
		{
			list_ = node;
			++size_;
			return;
		}

		auto current = list_;
		while (current->Next)
		{
			current = current->Next;
		}

		current->Next = node;
		++size_;
	}
	
	iterator begin()
	{
		return iterator(list_);
	}
	
	iterator end()
	{
		auto current = list_;
		while (current)
		{
			current = current->Next;
		}
		return iterator(current);
	}

	size_t size()
	{
		return size_;
	}

private:
	NodeType* list_;
	size_t size_;
};

std::string rotate(const std::string str)
{
	std::string result(str);
	auto len = str.size()-1;
	for (size_t index = 0; index < str.size()-1; ++index)
	{
		result[len - index] = result[len - index -1];
	}
	result[0] = str[str.size() - 1];
	return result;
}

void permute(std::string str, std::string out)
{
	if (str.size() == 0)
	{
		return;
	}

	for (int i = 0; i < str.size(); i++)
	{
		permute(str.substr(1), out + str[0]);
		rotate(str.begin(), str.begin() + 1, str.end());
	}
}

int testList()
{
	try 
	{
		auto slots = maxPeopleEntrySlot();

		LinkedList<int> lt = {1,2,3,4,5,6,7};
		LinkedList<int> lt2 = lt;

		auto printList = []( LinkedList<int>& list)
		{
			std::cout << "size is  " << list.size() <<std::endl;
			for (const auto& item : list)
			{
				std::cout << item.Data << " " ;
			}
			std::cout << std::endl;
		};

		lt2.reverse();
		printList(lt2);
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception during testing..." << std::endl;
	}
}		