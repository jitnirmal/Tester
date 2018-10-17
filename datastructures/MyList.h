#pragma once

template <typename Object>
struct Node
{
	Object data;
	Node *prev;
	Node *next;

	Node(const Object & d = Object{}, Node * p = nullptr, Node * n = nullptr)
		: data{ d }, prev{ p }, next{ n } { }

	Node(Object && d, Node * p = nullptr, Node * n = nullptr)
		: data{ std::move(d) }, prev{ p }, next{ n } { }
};

template <typename T>
class const_iterator
{
public:
	const_iterator(Node* ptr=nullptr) : current{ ptr }
	{ }

	const T& operator* () const
	{
		return current->data;
	}
	const T* operator-> () const
	{
		return current;
	}


	// ++x - prefix
	const_iterator& operator++ ()
	{
		current = current->next;
		return *this;
	}

	// x++ - postfix
	const_iterator operator++ (int)
	{
		const_iterator old = *this;
		++(*this);
		return old;
	}

	bool operator== (const const_iterator & rhs) const
	{
		return current == rhs.current;
	}
	bool operator!= (const const_iterator & rhs) const
	{
		return !(*this == rhs);
	}

private:
	Node * current;
	friend class List<T>;
};

template <typename T>
class iterator 
{
public:
	iterator(Node* ptr = nullptr) : current{ ptr }
	{ }

	T& operator* ()
	{
		return current->data;
	}
	
	T* operator* ()
	{
		return current;
	}

	iterator& operator++ ()
	{
		this->current = this->current->next;
		return *this;
	}

	iterator operator++ (int)
	{
		iterator old = *this;
		++(*this);
		return old;
	}

private:
	Node * current;
	friend class List<T>;
};

template <typename Object>
class List
{
public:
	List()
	{
		init();
	}

	~List()
	{
		clear();
		delete head;
		delete tail;
	}

	List(const List & rhs)
	{
		init();
		for (auto & x : rhs)
			push_back(x);
	}
	
	List(List && rhs)
		: theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}


	List & operator= (const List & rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List & operator= (List && rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);

		return *this;
	}

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	iterator begin()
	{
		return { head->next };
	}
	const_iterator begin() const
	{
		return { head->next };
	}
	iterator end()
	{
		return { tail };
	}
	const_iterator end() const
	{
		return { tail };
	}

	int size() const
	{
		return theSize;
	}
	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}
	Object & front()
	{
		return *begin();
	}
	const Object & front() const
	{
		return *begin();
	}
	Object & back()
	{
		return *--end();
	}
	const Object & back() const
	{
		return *--end();
	}
	void push_front(const Object & x)
	{
		insert(begin(), x);
	}
	void push_front(Object && x)
	{
		insert(begin(), std::move(x));
	}
	void push_back(const Object & x)
	{
		insert(end(), x);
	}
	void push_back(Object && x)
	{
		insert(end(), std::move(x));
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}

	// Insert x before itr.
	iterator insert(iterator itr, const Object & x)
	{
		Node *p = itr.current;
		theSize++;
		return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
	}

	// Insert x before itr.
	iterator insert(iterator itr, Object && x)
	{
		// current node
		// pn->cn->nn
		Node *cn = itr.current;
		theSize++;
		cn->prev->next = new Node{ std::move(x), cn->prev, cn };
		cn->prev = cn->prev->next;
		return cn->prev;
	}

	// Erase item at itr.
	iterator erase(iterator itr)
	{
		Node *p = itr.current;
		iterator retVal{ p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize--;

		return retVal;
	}

	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to; )
			itr = erase(itr);

		return to;
	}

private:
	int theSize;
	Node *head;
	Node *tail;

	
};
