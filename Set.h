// Set.h

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

//using ItemType = std::string;
template <typename ItemType>
class Set
{
public:
	Set() { createEmpty(); }               // Create an empty set (i.e., one with no items).
	bool empty() const;  // Return true if the set is empty, otherwise false.
	int size() const;    // Return the number of items in the set.

	bool insert(const ItemType& value);


	bool erase(const ItemType& value);


	bool contains(const ItemType& value) const;

	bool get(int i, ItemType& value) const;

	void swap(Set& other);

	// Housekeeping functions
	~Set();
	Set(const Set& other);
	Set& operator=(const Set& rhs);

private:
	// Representation:
	//   a circular doubly-linked list with a dummy node.
	//   m_head points to the dummy node.
	//   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
	//   m_size == 0  iff  m_head->m_next == m_head->m_prev == m_head
	//   If p and p->m_next point to nodes other than the dummy node,
	//      p->m_value < p->m_next->m_value

	struct Node
	{
		ItemType m_value;
		Node*    m_next;
		Node*    m_prev;
	};

	Node* m_head;
	int   m_size;

	void createEmpty();
	// Create an empty list.  (Will be called only by constructors.)

	void insertBefore(Node* p, const ItemType& value);
	// Insert value in a new Node before Node p, incrementing m_size.

	void doErase(Node* p);
	// Remove the Node p, decrementing m_size.

	Node* findFirstAtLeast(const ItemType& value) const
	{
		{
			Node* p = m_head->m_next;
			for (; p != m_head && p->m_value < value; p = p->m_next)
				;
			return p;
		}
	}
};

// Declarations of non-member functions
template <typename ItemType>
void unite(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result)
{
	const Set<ItemType>* sp = &s2;
	if (&result == &s1)
	{
		if (&result == &s2)
			return;
	}
	else if (&result == &s2)
		sp = &s1;
	else
	{
		result = s1;
		if (&s1 == &s2)
			return;
	}
	for (int k = 0; k < sp->size(); k++)
	{
		ItemType v;
		sp->get(k, v);
		result.insert(v);
	}
}
// result = { x | (x in s1) OR (x in s2) }

template <typename ItemType>
void subtract(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result)
{
	Set<ItemType> s2copy(s2);
	result = s1;
	for (int k = 0; k < s2copy.size(); k++)
	{
		ItemType v;
		s2copy.get(k, v);
		result.erase(v);
	}
}
// result = { x | (x in s1) AND NOT (x in s2) }

// Inline implementations

template <typename ItemType>
inline
int Set<ItemType>::size() const
{
	return m_size;
}

template <typename ItemType>
inline
bool Set<ItemType>::empty() const
{
	return size() == 0;
}

template <typename ItemType>
inline
bool Set<ItemType>::insert(const ItemType& value)
{
	// Fail if value already present

	Node* p = findFirstAtLeast(value);
	if (p != m_head && p->m_value == value)
		return false;

	// Insert new Node preserving ascending order and incrementing m_size

	insertBefore(p, value);
	return true;
}

template <typename ItemType>
inline
bool Set<ItemType>::erase(const ItemType& value)
{
	// Find the Node with the value, failing if there is none.

	Node* p = findFirstAtLeast(value);
	if (p == m_head || p->m_value != value)
		return false;

	// Erase the Node, decrementing m_size
	doErase(p);
	return true;
}

template <typename ItemType>
inline
bool Set<ItemType>::contains(const ItemType& value) const
{
	Node* p = findFirstAtLeast(value);
	return p != m_head && p->m_value == value;
}

template <typename ItemType>
inline
bool Set<ItemType>::get(int i, ItemType& value) const
{
	if (i < 0 || i >= m_size)
		return false;

	Node* p;
	if (i < m_size / 2)  // closer to head
	{
		p = m_head->m_next;
		for (int k = 0; k != i; k++)
			p = p->m_next;
	}
	else  // closer to tail
	{
		p = m_head->m_prev;
		for (int k = m_size - 1; k != i; k--)
			p = p->m_prev;
	}

	value = p->m_value;
	return true;
}

template <typename ItemType>
inline
void Set<ItemType>::swap(Set<ItemType>& other)
{
	// Swap head pointers

	Node* p = other.m_head;
	other.m_head = m_head;
	m_head = p;

	// Swap sizes

	int s = other.m_size;
	other.m_size = m_size;
	m_size = s;
}

template <typename ItemType>
Set<ItemType>::~Set()
{
	// Delete all Nodes from first non-dummy up to but not including
	// the dummy

	while (m_head->m_next != m_head)
		doErase(m_head->m_next);

	// delete the dummy

	delete m_head;
}

template <typename ItemType>
inline
Set<ItemType>::Set(const Set<ItemType>& other)
{
	createEmpty();

	for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
		insertBefore(m_head, p->m_value);
}

template <typename ItemType>
inline
Set<ItemType>& Set<ItemType>::operator=(const Set<ItemType>& rhs)
{
	if (this != &rhs)
	{
		// Copy and swap idiom

		Set<ItemType> temp(rhs);
		swap(temp);
	}
	return *this;
}

template <typename ItemType>
void Set<ItemType>::createEmpty()
{
	m_size = 0;

	// Create dummy node

	m_head = new Node;
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}

template <typename ItemType>
void Set<ItemType>::insertBefore(Node* p, const ItemType& value)
{
	// Create a new node

	Node* newp = new Node;
	newp->m_value = value;

	// Insert new item before p

	newp->m_prev = p->m_prev;
	newp->m_next = p;
	newp->m_prev->m_next = newp;
	newp->m_next->m_prev = newp;

	m_size++;
}

template <typename ItemType>
void Set<ItemType>::doErase(Node* p)
{
	// Unlink p from the list and destroy it

	p->m_prev->m_next = p->m_next;
	p->m_next->m_prev = p->m_prev;
	delete p;

	m_size--;
}

#endif // SET_INCLUDED