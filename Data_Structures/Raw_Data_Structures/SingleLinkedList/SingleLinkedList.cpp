#include <iostream>
#include "SingleLinkedList.h"

using std::cout;
using std::endl;

SingleLinkedList::SingleLinkedList() : m_NodeCount( 0 ), m_ElementCount( 0 ), m_Head( nullptr ), m_Tail( nullptr )
{
}

SingleLinkedList::SingleLinkedList( const SingleLinkedList& rhs ) : m_NodeCount( rhs.m_NodeCount ), m_ElementCount( rhs.m_ElementCount ), 
                                                                    m_Head( DeepCopy( rhs.m_Head ) )
{
}

// Move Constructor
SingleLinkedList::SingleLinkedList( SingleLinkedList&& rhs ) noexcept : m_NodeCount( 0 ), m_ElementCount( 0 ), 
                                                                        m_Head( nullptr ), m_Tail( nullptr )
{
	*this = std::move( rhs );
}

// Copy Operator Overload
SingleLinkedList& SingleLinkedList::operator=( const SingleLinkedList& rhs )
{
	// prevent self assignment obj1 = obj1
	if( this != &rhs )
	{
		if( this->m_Head != nullptr )
		{
			MakeEmpty();
		}

		if( rhs.IsEmpty() == true )
		{
			this->m_Head = nullptr;
		}
		else
		{
			this->m_Head = DeepCopy( rhs.GetHead() );
			this->m_ElementCount = rhs.m_ElementCount;
			this->m_NodeCount = rhs.m_NodeCount;
		}
	}

	return *this;
}

SingleLinkedList& SingleLinkedList::operator=( SingleLinkedList&& rhs ) noexcept
{
	// Prevent Self Assignment
	// Prevent this -> DoubleLinkedList myObj = myObj;
	if( this != &rhs )
	{
		// If we have lvalue we destroy it.
		if( this->IsEmpty() == false )
		{
			this->MakeEmpty();
		}

		this->m_Head = rhs.m_Head;
		this->m_Tail = rhs.m_Tail;
		this->m_ElementCount = rhs.m_ElementCount;
		this->m_NodeCount = rhs.m_NodeCount;
		this->m_NodeMap = std::move( rhs.m_NodeMap );

		// Clean up
		rhs.m_Head = nullptr;
		rhs.m_Tail = nullptr;
		rhs.m_ElementCount = 0;
		rhs.m_NodeCount = 0;
		rhs.m_NodeMap.clear();
	}

	return *this;
}

SingleLinkedList::~SingleLinkedList()
{	
	MakeEmpty();	
}

SingleLinkedList::ListNode* SingleLinkedList::DeepCopy( ListNode* rhsPtr )
{
	if( rhsPtr == nullptr )
	{
		this->m_Head = rhsPtr;	
		this->m_Tail = rhsPtr;
		return m_Head;
	}

	/// Copy Head
	ListNode* newNode = new ListNode( rhsPtr->value );
	newNode->count = rhsPtr->count;
	this->m_Head = newNode;
	//this->AddToNodeMap( newNode->value, newNode, nullptr );

	ListNode* newListPtr = this->m_Head;
	ListNode* originalListPtr = rhsPtr->next;
	ListNode* previousNode = this->m_Head;

	/// Copy other elements
	while( originalListPtr != nullptr )
	{
		newListPtr->next = new ListNode( originalListPtr->value );
		newListPtr->next->count = originalListPtr->count;
		//this->AddToNodeMap( newListPtr->next->value, newListPtr->next, previousNode );

		previousNode = newListPtr;
		newListPtr = newListPtr->next;		
		originalListPtr = originalListPtr->next;
	}
		
	/// Copy NodeMap
	newListPtr = this->m_Head;
	previousNode = nullptr;
	while( newListPtr != nullptr )
	{
		std::vector<ListNode*> nodeAddrs;
		nodeAddrs.push_back( newListPtr );
		nodeAddrs.push_back( previousNode );

		m_NodeMap[newListPtr->value] = nodeAddrs;

		previousNode = newListPtr;
		newListPtr = newListPtr->next;
	}

	
	this->m_Tail = previousNode;
	return this->m_Head;
}

void SingleLinkedList::InsertNode( const int& value )
{
	ListNode* newNode = new ListNode( value );

	if( IsEmpty() == true )
	{
		m_Head = newNode;
		m_Tail = newNode;
		AddToNodeMap( value, m_Head, nullptr );
		++m_NodeCount;
		++m_ElementCount;
		return;
	}

	ListNode* previousNode = nullptr;

	if( value > m_Tail->value )
	{
		previousNode = m_Tail;
		m_Tail->next = newNode;
		m_Tail = m_Tail->next;
		AddToNodeMap( value, m_Tail, previousNode );		
		++m_NodeCount;
		++m_ElementCount;
		return;
	}

	if( value == m_Tail->value )
	{
		delete newNode;
		++m_Tail->count;
		++m_ElementCount;
		return;
	}

	ListNode* currentNode = m_Head;

	// Trevel while skipping all the lesser nodes
	while( currentNode != nullptr && value >= currentNode->value )
	{
		previousNode = currentNode;
		currentNode = currentNode->next;		
	}

	// If the node is less than head node, we insert it before head and change the head to newNode.
	if( previousNode == nullptr )
	{		
		m_Head = newNode;
		AddToNodeMap( value, m_Head, nullptr );
		newNode->next = currentNode;
		AddToNodeMap( currentNode->value, currentNode, m_Head );
		++m_NodeCount;
		++m_ElementCount;
		return;
	}

	// If the value is equal, no need to add another node. We can simply increment count
	if( value == previousNode->value )
	{
		delete newNode;
		++previousNode->count;
		++m_ElementCount;		
	}
	else
	{
		previousNode->next = newNode;
		AddToNodeMap( value, previousNode->next, previousNode );
		newNode->next = currentNode;
		AddToNodeMap( currentNode->value, currentNode, previousNode->next );
		++m_ElementCount;
		++m_NodeCount;
	}

}

void SingleLinkedList::InsertMultipleNodes( const std::vector<int>& valueList )
{
	if( valueList.empty() == true )
	{
		cout << "List is empty!" << endl;
		return;
	}

	for( auto& num: valueList )
	{
		InsertNode( num );
	}
}

void SingleLinkedList::PrintList() const
{
	ListNode* currentNode = m_Head;

	if( IsEmpty() == true )
	{
		cout << "List is empty!" << endl;
		return;
	}

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
void SingleLinkedList::RecursivePrint( ListNode* currentNode, int i ) const
{
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

void SingleLinkedList::AddToNodeMap( const int& key, ListNode* currentNode, ListNode* previousNode )
{
	std::vector<ListNode*> nodeAddrs;
	nodeAddrs.push_back( currentNode );
	nodeAddrs.push_back( previousNode );
	m_NodeMap[key] = nodeAddrs;
}

void SingleLinkedList::PrintMap() const
{
	if( m_NodeMap.empty() == true )
	{
		return;
	}

	for( auto& element : m_NodeMap )
	{
		cout << element.first << " " << element.second[0]<< " prev " << element.second[1] << endl;
	}
}

// Return a pointer to the previous node of the value
// Or return nullptr if value if not found. Takes O(1) time.
SingleLinkedList::ListNode* SingleLinkedList::DirectSearchNode( const int& value ) const
{
	if( m_NodeMap.find( value ) == m_NodeMap.end() )
	{
		return nullptr;
	}
	
	return m_NodeMap.find( value )->second[1];
}

// Return a pointer to the node of the value
// and return previous pointer. If not found both values will be nullptr. Takes O(N) time.
SingleLinkedList::ListNode* SingleLinkedList::LinearSearchNode( const int& value ) const
{
	ListNode* previousNode = nullptr;

	if( IsEmpty() == true )
	{
		cout << "Nothing to search. List is empty" << endl;		
		return previousNode;
	}

	ListNode* currentNode = m_Head;	

	while( currentNode != nullptr )
	{
		if( currentNode->value == value )
		{
			return previousNode;
		}
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	return nullptr;
}

void SingleLinkedList::DeleteNode( const int& value )
{
	ListNode* currentNode = m_Head;	

	if( IsEmpty() == true )
	{
		cout << "Nothing to delete. List is empty" << endl;
		return;
	}

	if( m_Head->value == value && m_Head->count == 1 )
	{
		if( m_Head == m_Tail )
		{
			m_Tail = nullptr;
		}
		
		currentNode = m_Head->next;
		delete m_Head;
		m_Head = currentNode;
		m_NodeMap.erase( value );
		--m_NodeCount;
		--m_ElementCount;
		return;

	}
	else if( m_Head->value == value && m_Head->count > 1)
	{
		--m_Head->count;
		--m_ElementCount;
		return;
	}

	ListNode* previousNode = DirectSearchNode( value );
	currentNode = previousNode->next;

	if( m_Tail->value == value && m_Tail->count == 1 )
	{
		delete m_Tail;
		previousNode->next = nullptr;
		m_NodeMap.erase( value );
		m_Tail = previousNode;
		--m_NodeCount;
		return;
	}
	else if( m_Tail->value == value && m_Tail->count > 1 )
	{
		--m_Tail->count;
		--m_ElementCount;		
		return;
	}

	if( currentNode != nullptr && currentNode->count == 1 )
	{
		ListNode* tempNode = currentNode->next;
		
		AddToNodeMap( tempNode->value, tempNode, previousNode );
		m_NodeMap.erase( value );
		delete currentNode;
		--m_NodeCount;
		--m_ElementCount;			
		previousNode->next = tempNode;
	}
	else if( currentNode != nullptr && currentNode->count > 1 )
	{
		--m_ElementCount;
		--currentNode->count;
	}

}

void SingleLinkedList::RemoveMultipleNodes( const std::vector<int>& valueList )
{
	if( valueList.empty() == true )
	{
		cout << "List is empty!" << endl;
		return;
	}

	for( auto& num : valueList )
	{
		DeleteNode( num );
	}
}

/// Invert the list.
/// This will modify the list
void SingleLinkedList::InvertList()
{
	if( IsEmpty() == true )
	{
		return;
	}

	ListNode* currentNode = m_Head;
	ListNode* previousNode = nullptr;
	ListNode* nextNode = m_Head;

	while( currentNode != nullptr )
	{
		nextNode = currentNode->next;
		currentNode->next = previousNode;
		previousNode = currentNode;
		currentNode = nextNode;		
	}

	m_Head = previousNode;
}

SingleLinkedList::ListNode* SingleLinkedList::FindMiddleOrLastNode( const bool getMiddle )
{

	if( IsEmpty() == true )
	{
		return nullptr;
	}

	ListNode* fast = m_Head;
	ListNode* slow = m_Head;
	ListNode* last = nullptr;

	while( fast != nullptr && fast->next != nullptr )
	{
		// This is to point to the last node in case list has even length
		// If the list is even, fast will end up nullptr
		// If the list is odd, fast will end up last node.
		if( fast != nullptr && fast->next->next == nullptr )
		{
			last = fast->next;
		}

		fast = fast->next->next;
		slow = slow->next;
	}

	if( last != nullptr )
	{
		fast = last;
	}	

	return getMiddle ? slow : fast;
}

void SingleLinkedList::MakeEmpty()
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
SingleLinkedList& SingleLinkedList::operator++()
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
SingleLinkedList& SingleLinkedList::operator--()
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
SingleLinkedList SingleLinkedList::operator++( int )
{
	SingleLinkedList temp;

	if( IsEmpty() == true )
	{
		temp.InsertNode( 0 );
		InsertNode( 0 );
		return temp;
	}

	temp.InsertNode( m_Tail->value );
	InsertNode( m_Tail->value + 1 );
	return temp;
}

// Postfix decrement
// If list is empty do nothing
// Otherwise, delete tail node and change the tail to one before it.
// Ex: if we have folloing list 1 -> 2 -> 3
// This will result 1 -> 2 ( Tail is now at 2 )
SingleLinkedList SingleLinkedList::operator--( int )
{
	SingleLinkedList temp;

	if( IsEmpty() == true )
	{
		return temp;
	}

	ListNode* previousNode = this->DirectSearchNode( m_Tail->value );

	temp.InsertNode( previousNode->value );
	temp.InsertNode( m_Tail->value );
	temp.DeleteNode( m_Tail->value );
	DeleteNode( m_Tail->value );
	return temp;
}
