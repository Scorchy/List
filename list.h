#ifndef LIST
#define LIST

template<typename T>
class List
{
public:
	struct Node
	{
		Node(T);
		T m_data;
		Node* m_pNext;
		Node* m_pPrev;
	};
	List();
	~List();
	void push_front(const T&);
	void push_back(const T&);
	void pop_front();
	void pop_back();
	T& front();
	T& back();
	class iterator
	{
	public:
		iterator(Node*&);
		T& operator*();
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator != (const iterator&);
		Node* m_ptr;
	};
	iterator begin();
	iterator end();
	void insert(iterator, const T&);
	void erase(iterator);
	void clear();
	bool empty();

private:
	int m_size;
	Node* head;
	Node* tail;
};

template<typename T>
List<T>::Node::Node(T data)
{
	m_data = data;
	m_pNext = m_pPrev = nullptr;
}

template<typename T>
List<T>::List()
{
	m_size = 0;
	head = tail = nullptr;
}

template<typename T>
List<T>::~List()
{
	if (!empty())
	{
		Node* i = head;
		while (true)
		{
			i = i->m_pNext;
			if (i != nullptr)
			{
				delete i->m_pPrev;
				i->m_pPrev = nullptr;
			}
			else
			{
				delete tail;
				tail = head = nullptr;
				break;
			}
		}
		m_size = 0;
	}
}

template<typename T>
void List<T>::push_front(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		Node* temp = new Node(value);
		temp->m_pNext = head;
		head->m_pPrev = temp;
		head = temp;
	}
	m_size++;
}

template<typename T>
void List<T>::push_back(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		Node* temp = new Node(value);
		tail->m_pNext = temp;
		temp->m_pPrev = tail;
		tail = temp;
	}
	m_size++;
}

template<typename T>
void List<T>::pop_front()
{
	if (!this->empty())
	{
		head = head->m_pNext;
		head->m_pPrev = nullptr;
		m_size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	if (!this->empty())
	{
		tail = tail->m_pPrev;
		tail->m_pNext = nullptr;
		m_size--;
	}
}

template<typename T>
T& List<T>::front()
{
	return head->m_data;
}

template<typename T>
T& List<T>::back()
{
	return tail->m_data;
}

template<typename T>
List<T>::iterator::iterator(Node*& ptr) : m_ptr(ptr)
{
}

template<typename T>
T& List<T>::iterator::operator*()
{
	return m_ptr->m_data;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
	m_ptr = m_ptr->m_pNext;
	return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
	iterator temp = *this;
	m_ptr = m_ptr->m_pNext;
	return temp;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
	m_ptr = m_ptr->m_pPrev;
	return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
	iterator temp = *this;
	m_ptr = m_ptr->m_pPrev;
	return temp;
}

template<typename T>
bool List<T>::iterator::operator != (const iterator& it)
{
	return m_ptr != it.m_ptr;
}

template<typename T>
typename List<T>::iterator List<T>::begin()
{
	iterator it(head);
	return it;
}

template<typename T>
typename List<T>::iterator List<T>::end()
{
	iterator it(tail->m_pNext);
	return it;
}

template<typename T>
void List<T>::insert(iterator it, const T& value)
{
	Node* temp = new Node(value);

	if (empty())
	{
		head = tail = temp;
		temp->m_pNext = temp->m_pPrev = nullptr;
	}
	else
	{
		if (it.m_ptr == nullptr)
		{
			temp->m_pNext = nullptr;

			tail->m_pNext = temp;
			temp->m_pPrev = tail;

			tail = temp;
		}
		else
		{
			if (it.m_ptr->m_pPrev == nullptr)
			{
				temp->m_pPrev = nullptr;
				head = temp;
			}
			else
			{
				it.m_ptr->m_pPrev->m_pNext = temp;
				temp->m_pPrev = it.m_ptr->m_pPrev;
			}

			temp->m_pNext = it.m_ptr;
			it.m_ptr->m_pPrev = temp;
		}
	}

	m_size++;
}

template<typename T>
void List<T>::erase(iterator it)
{
	if (it.m_ptr != nullptr)
	{
		if (it.m_ptr->m_pPrev == nullptr && it.m_ptr->m_pNext == nullptr)
		{
			head = tail = nullptr;
		}

		if (it.m_ptr->m_pPrev == nullptr && it.m_ptr->m_pNext != nullptr)
		{
			it.m_ptr->m_pNext->m_pPrev = nullptr;
			head = it.m_ptr->m_pNext;
		}

		if (it.m_ptr->m_pPrev != nullptr && it.m_ptr->m_pNext == nullptr)
		{
			it.m_ptr->m_pPrev->m_pNext = nullptr;
			tail = it.m_ptr->m_pPrev;
		}

		if (it.m_ptr->m_pPrev != nullptr && it.m_ptr->m_pNext != nullptr)
		{
			it.m_ptr->m_pPrev->m_pNext = it.m_ptr->m_pNext;
			it.m_ptr->m_pNext->m_pPrev = it.m_ptr->m_pPrev;
		}

		m_size--;
		delete it.m_ptr;
	}
	else
	{
		cout << "Erasing failed!" << endl;
	}
}

template<typename T>
void List<T>::clear()
{
	this->~List();
}

template<typename T>
bool List<T>::empty()
{
	return !m_size;
}

#endif LIST
