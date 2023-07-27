#include <iostream>
#include "DoubleLinkedList.h"

using std::cout;
using std::endl;

DoubleLinkedList::DoubleLinkedList() : m_NodeCount( 0 ), m_ElementCount( 0 ), m_Head( nullptr ), m_Tail( nullptr )
{
}

// Use only when necessary because copy is expensive.
DoubleLinkedList::DoubleLinkedList( const DoubleLinkedList& rhs ) : m_NodeCount( rhs.m_NodeCount ), m_ElementCount( rhs.m_ElementCount ),
									m_Head( DeepCopy( rhs.GetHead() ) )
{	
}

// Move constructor. Less expensive than copy constructor
DoubleLinkedList::DoubleLinkedList( DoubleLinkedList&& rhs ) noexcept : m_NodeCount( 0 ), m_ElementCount( 0 ), 
																		m_Head( nullptr ), m_Tail( nullptr )
{
	*this = std::move( rhs );	
}

// Use only when necessary because copy is expensive.
DoubleLinkedList& DoubleLinkedList::operator=( const DoubleLinkedList& rhs )
{
	// prevent self assignment obj1 = obj1
	if( this != &rhs )
	{
		this->m_Head = DeepCopy( rhs.GetHead() );		
		this->m_ElementCount = rhs.m_ElementCount;
		this->m_NodeCount = rhs.m_NodeCount;
	}

	return *this;
}

DoubleLinkedList& DoubleLinkedList::operator=( DoubleLinkedList&& rhs ) noexcept
{
	// Prevent Self Assignment
	// Prevent this -> DoubleLinkedList myObj = myObj;
	if( this != &rhs )
	{
		// If we have values in lvalue, we destroy it
		if( this->IsEmpty() == false )
		{
			this->MakeEmpty();
		}		

		this->m_Head = rhs.m_Head;
		this->m_Tail = rhs.m_Tail;
		this->m_ElementCount = rhs.m_ElementCount;
		this->m_NodeCount = rhs.m_NodeCount;
		this->m_NodeMap = std::move( rhs.m_NodeMap );

		// We adjust to new m_Head and m_Tail addresses. 
		// Otherwise, it will point to rhs.m_Head and rhs.m_Tail.
		this->AddToNodeMap( this->m_Head->value, this->m_Head );
		this->AddToNodeMap( this->m_Tail->value, this->m_Tail );

		// Clean up
		rhs.m_Head = nullptr;
		rhs.m_Tail = nullptr;
		rhs.m_ElementCount = 0;
		rhs.m_NodeCount = 0;
	}

	return *this;
}

DoubleLinkedList::~DoubleLinkedList()
{
	MakeEmpty();
}

DoubleLinkedList::ListNode* DoubleLinkedList::DeepCopy( ListNode* rhsPtr )
{
	// If the lhs is not empty, clear it.
	if( this->m_Head != nullptr )
	{
		MakeEmpty();
	}

	if( rhsPtr == nullptr )
	{
		this->m_Head = nullptr;		
		this->m_Tail = nullptr;
		return this->m_Head;
	}

	/// Start by copying head
	ListNode* newHead = new ListNode( rhsPtr->value );
	newHead->count = rhsPtr->count;
	this->m_Head = newHead;
	this->AddToNodeMap( this->m_Head->value, this->m_Head );

	ListNode* newNode = this->m_Head;
	ListNode* originalList = rhsPtr->next;

	// Copy the other elements
	while( originalList != nullptr )
	{
		newNode->next = new ListNode( originalList->value );
		newNode->next->count = originalList->count;
		newNode->next->prev = newNode;

		this->AddToNodeMap( newNode->next->value, newNode->next );

		newNode = newNode->next;
		originalList = originalList->next;
	}

	this->m_Tail = newNode;	
	return this->m_Head;
}

// Add a node to the list
void DoubleLinkedList::InsertNode( const int& value )
{
	ListNode* newNode = new ListNode( value );

	if( IsEmpty() == true )
	{
		m_Head = newNode;
		m_Tail = newNode;		
		AddToNodeMap( value, m_Head );
		++m_NodeCount;
		++m_ElementCount;
		return;
	}

	// If the value is equal, no need to add another node. We can simply increment count in O(1) time
	if( DirectSearchNode( value ) != nullptr )
	{
		delete newNode;
		++DirectSearchNode( value )->count;
		++m_ElementCount;
		return;
	}

	// Insert after tail
	if( value > m_Tail->value )
	{
		m_Tail->next = newNode;
		newNode->prev = m_Tail;
		m_Tail = m_Tail->next;
		AddToNodeMap( value, m_Tail );		
		++m_NodeCount;
		++m_ElementCount;		
		return;
	}

	// If the value is less than the head simply add new node before head.
	if( value < m_Head->value )
	{
		ListNode* temp = m_Head;
		m_Head = newNode;
		m_Head->prev = nullptr;
		m_Head->next = temp;
		AddToNodeMap( value, m_Head );
		AddToNodeMap( temp->value, m_Head->next );
		++m_ElementCount;
		++m_NodeCount;		
		return;
	}

	ListNode* currentNode = m_Head;

	// Trevel while skipping all the lesser nodes
	while( currentNode != nullptr &&  currentNode->value <= value )
	{
		currentNode = currentNode->next;
	}

	if( currentNode != nullptr && currentNode->prev->value != value )
	{
		currentNode->prev->next = newNode;
		newNode->prev = currentNode->prev;
		newNode->next = currentNode;
		AddToNodeMap( value, newNode );
		AddToNodeMap( currentNode->value, currentNode );
		currentNode->prev = newNode;
		++m_ElementCount;
		++m_NodeCount;		
		return;
	}	
}

void DoubleLinkedList::InsertMultipleNodes( const std::vector<int>& valueList )
{
	if( valueList.empty() == true)
	{
		cout << "Input List is empty!" << endl;
		return;
	}

	for( auto& num : valueList )
	{
		InsertNode( num );
	}
}

void DoubleLinkedList::DeleteNode( const int& value )
{
	if( IsEmpty() == true )
	{
		cout << "Nothing to delete. List is empty" << endl;
		return;
	}
	
	ListNode* nodeToBeDeleted = DirectSearchNode( value );

	if( nodeToBeDeleted == nullptr )
	{
		cout << "Nothing to be deleted. The value is not in the list." << endl;
		return;
	}

	if( nodeToBeDeleted != nullptr && nodeToBeDeleted->count > 1 )
	{
		--nodeToBeDeleted->count;
		--m_ElementCount;
		return;
	}

	if( m_Head->value == value )
	{
		if( m_Head == m_Tail )
		{
			m_Tail = nullptr;
		}

		m_Head = m_Head->next;

		if( m_Head != nullptr )
		{
			delete m_Head->prev;
			m_Head->prev = nullptr;
		}

		m_NodeMap.erase( value );		
		--m_NodeCount;
		--m_ElementCount;
		return;
	}

	if( m_Tail->value == value )
	{
		m_Tail = m_Tail->prev;

		if( m_Tail != nullptr )
		{
			delete m_Tail->next;
			m_Tail->next = nullptr;
		}

		m_NodeMap.erase( value );		
		--m_NodeCount;
		--m_ElementCount;
		return;
	}

	if( nodeToBeDeleted->count == 1 )
	{
		nodeToBeDeleted->prev->next = nodeToBeDeleted->next;
		nodeToBeDeleted->next->prev = nodeToBeDeleted->prev;
		delete nodeToBeDeleted;
		m_NodeMap.erase( value );
		--m_NodeCount;
		--m_ElementCount;
		return;
	}
}

void DoubleLinkedList::RemoveMultipleNodes( const std::vector<int>& valueList )
{
	if( valueList.empty() == true )
	{
		cout << "Input List is empty!" << endl;
		return;
	}

	for( auto& num : valueList )
	{
		DeleteNode( num );
	}
}

void DoubleLinkedList::PrintList() const
{
	if( IsEmpty() == true )
	{
		cout << "List is empty!" << endl;
		return;
	}

	ListNode* currentNode = m_Head;
	int i = 0;
	
	while( currentNode != nullptr )
	{
		if( i == 0 )
		{
			cout << "Head -> " << currentNode->value << " ( " << currentNode->count << " )";
		}
		else if( currentNode->next != nullptr )
		{
			cout << " -> " << currentNode->value << " ( " << currentNode->count << " )";
		}

		if( currentNode->next == nullptr && i != 0 )
		{
			cout << " -> " << currentNode->value << " ( " << currentNode->count << " )" << " -> NULL" << endl;
		}
		else if( currentNode->next == nullptr && i == 0 )
		{
			cout << " -> NULL" << endl;
		}

		currentNode = currentNode->next;
		i++;
	}
}

/// Print reversed list without modifying the original list.
void DoubleLinkedList::RecursivePrint( ListNode* currentNode, int i ) const
{
	if( IsEmpty() == true )
	{
		cout << "Head -> NULL <- Tail" << endl;
		return;
	}

	if( currentNode != nullptr )
	{
		RecursivePrint( currentNode->next, ++i );
		cout << currentNode->value << " ( " << currentNode->count << " )" << " -> ";
	}
	else
	{
		cout << "Head -> ";
	}

	if( i == 1 )
	{
		cout << "NULL" << endl;
	}
}

void DoubleLinkedList::InvertList()
{
	if( IsEmpty() == true )
	{
		return;
	}

	ListNode* currentNode = m_Head;
	ListNode* nextNode = currentNode->next;	
	
	m_Tail = m_Head;	
	
	currentNode->next = nullptr;
	currentNode->prev = nextNode;

	while( nextNode != nullptr )
	{
		nextNode->prev = nextNode->next;
		nextNode->next = currentNode;		
		currentNode = nextNode;		
		nextNode = nextNode->prev;		
	}
	
	m_Head = currentNode;

	currentNode = m_Head;
	while( currentNode != nullptr )
	{
		AddToNodeMap( currentNode->value, currentNode );
		currentNode = currentNode->next;
	}
}

// Return a pointer to the node of the value
// If value is not there, return a nullptr
// Takes O(n) time
DoubleLinkedList::ListNode* DoubleLinkedList::LinearSearchNode( const int& value ) const
{
	if( IsEmpty() == true )
	{
		cout << "Nothing to search. List is empty" << endl;
		return nullptr;
	}

	if( m_Head->value == value )
	{
		return m_Head;
	}

	if( m_Tail->value == value )
	{
		return m_Tail;
	}

	ListNode* currentNode = m_Head;
	
	while( currentNode != nullptr )
	{
		if( currentNode->value == value )
		{
			return currentNode;
		}

		currentNode = currentNode->next;
	}

	return nullptr;
}

// Return a pointer to the node of the value
// If value is not there, return a nullptr
// Takes O(1) time
DoubleLinkedList::ListNode* DoubleLinkedList::DirectSearchNode( const int& value ) const
{
	if( m_NodeMap.find( value ) == m_NodeMap.end() )
	{
		return nullptr;
	}
	
	return m_NodeMap.find( value )->second;
}

// Add node to hashmap
void DoubleLinkedList::AddToNodeMap( const int& key, ListNode* currentNode )
{
	m_NodeMap[key] = currentNode;
}

// Find the middle node using fast and slow pointer method
DoubleLinkedList::ListNode* DoubleLinkedList::FindMiddle( ListNode* head )
{
	if( IsEmpty() == true )
	{
		return nullptr;
	}

	ListNode* fast = head;
	ListNode* slow = head;	

	while( fast != nullptr && fast->next != nullptr )
	{
		slow = slow->next;
		fast = fast->next->next;		
	}

	return slow;
}

// Destroy the list
void DoubleLinkedList::MakeEmpty()
{
	if( IsEmpty() == true )
	{
		return;
	}

	ListNode* tempNode = nullptr;

	while( m_Head != nullptr )
	{
		tempNode = m_Head->next;
		delete m_Head;
		m_Head = tempNode;
	}

	m_ElementCount = 0;
	m_NodeCount = 0;
	m_NodeMap.clear();
	m_Head = nullptr;
	m_Tail = nullptr;
}

// Prefix increment
// If list is empty add 0 as the first node
// Otherwise, add a newNode with ( head->value - 1 ) and change the head to newNode
// Ex: if we have folloing list 1 -> 2 -> 3
// This will result 0 -> 1 -> 2 -> 3 ( Head is now 0 )
DoubleLinkedList& DoubleLinkedList::operator++()
{
	if( IsEmpty() == true )
	{
		InsertNode( 0 );
		return *this;
	}

	InsertNode( m_Head->value - 1 );

	return *this;
}

// Prefix decrement
// If list is empty do nothing
// Otherwise, delete a current headnode and update the head to the next node
// Ex: if we have folloing list 1 -> 2 -> 3
// This will result 2 -> 3 ( Head is now at 2 )
DoubleLinkedList& DoubleLinkedList::operator--()
{
	if( IsEmpty() == true )
	{		
		return *this;
	}

	DeleteNode( m_Head->value );

	return *this;
}

// Postfix increment
// If list is empty add 0 as the first node
// Otherwise, add a newNode with ( tail->value + 1 ) and change the tail to newNode
// Ex: if we have folloing list 1 -> 2 -> 3
// This will result 1 -> 2 -> 3 -> 4 ( Tail is now at 4 )
DoubleLinkedList DoubleLinkedList::operator++( int )
{
	DoubleLinkedList temp;

	if( IsEmpty() == true )
	{
		
		temp.InsertNode( 0 );
		InsertNode( 0 );
		return temp;
	}
	
	temp.InsertNode( m_Tail->value );
	InsertNode( m_Tail->value + 1);
	return temp;
}

// Postfix decrement
// If list is empty do nothing
// Otherwise, delete tail node and change the tail to one before it.
// Ex: if we have folloing list 1 -> 2 -> 3
// This will result 1 -> 2 ( Tail is now at 2 )
DoubleLinkedList DoubleLinkedList::operator--( int )
{
	DoubleLinkedList temp;

	if( IsEmpty() == true )
	{
		
		return temp;
	}

	temp.InsertNode( m_Tail->prev->value );
	temp.InsertNode( m_Tail->value );
	temp.DeleteNode( m_Tail->value );
	DeleteNode( m_Tail->value );
	return temp;
}