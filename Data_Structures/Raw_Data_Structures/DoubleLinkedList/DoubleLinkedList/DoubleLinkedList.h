#pragma once
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <unordered_map>

class DoubleLinkedList
{

private:

	struct ListNode
	{
		int value;
		int count;
		ListNode* next;
		ListNode* prev;

		ListNode() = default;

		explicit ListNode( const int& val ) : value( val ), count( 1 ), next( nullptr ), prev( nullptr ) {}
	};

	int m_NodeCount;
	int m_ElementCount;
	std::unordered_map<int, ListNode*> m_NodeMap;

	ListNode* m_Head;
	ListNode* m_Tail;	

	void AddToNodeMap( const int& key, ListNode* currentNode );	
	ListNode* DeepCopy( ListNode* rhsPtr );

public:
	DoubleLinkedList();
	DoubleLinkedList( const DoubleLinkedList& rhs );
	DoubleLinkedList( DoubleLinkedList&& rhs ) noexcept;
	~DoubleLinkedList();

	// Operator overloads
	DoubleLinkedList& operator=( const DoubleLinkedList& rhs );
	DoubleLinkedList& operator=( DoubleLinkedList&& rhs ) noexcept;
	
	// Prefix
	DoubleLinkedList& operator++();
	DoubleLinkedList& operator--();

	// Postfix
	DoubleLinkedList operator++( int );
	DoubleLinkedList operator--( int );	

	void InsertNode( const int& value );
	void InsertMultipleNodes( const std::vector<int>& valueList );
	void DeleteNode( const int& value );
	void RemoveMultipleNodes( const std::vector<int>& valueList );
	void InvertList();
	void PrintList() const;
	void MakeEmpty();
	void RecursivePrint( ListNode* currentNode, int i ) const;	

	ListNode* LinearSearchNode( const int& value ) const;
	ListNode* DirectSearchNode( const int& value ) const;
	ListNode* FindMiddle( ListNode* head );	

	// Inline methods
	int GetNodeCount() const
	{
		return m_NodeCount;
	}

	int GetElementCount() const
	{
		return m_ElementCount;
	}

	size_t GetNodeMapSize() const
	{
		return m_NodeMap.size();
	}

	bool IsListEven() const
	{
		return ( m_NodeCount % 2 == 0 ) ? true : false;
	}

	bool IsEmpty() const
	{
		return ( m_Head == nullptr ) ? true : false;
	}

	ListNode* GetHead() const
	{
		return m_Head;
	}

	ListNode* GetTail() const
	{
		return m_Tail;
	}
};

#endif // !DOUBLELINKEDLIST_H

