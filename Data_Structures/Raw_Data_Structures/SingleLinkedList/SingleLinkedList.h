#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <unordered_map>

class SingleLinkedList
{

private:

	struct ListNode
	{
		int value;
		int count;
		ListNode* next;

		ListNode() = default;

		explicit ListNode( const int& val ) : value( val ), count( 1 ), next( nullptr ) {}
	};

	int m_NodeCount;
	int m_ElementCount;
	std::unordered_map<int, std::vector<ListNode*>> m_NodeMap;

	ListNode* m_Head;
	ListNode* m_Tail;
		
	void AddToNodeMap( const int& key, ListNode* currentNode, ListNode* previousNode );
	ListNode* DeepCopy( ListNode* rhsPtr );

public:
	SingleLinkedList();
	SingleLinkedList( const SingleLinkedList& rhs );
	SingleLinkedList( SingleLinkedList&& rhs ) noexcept;
	~SingleLinkedList();

	void InsertNode( const int& value );
	void InsertMultipleNodes( const std::vector<int>& valueList );
	void DeleteNode( const int& value );
	void RemoveMultipleNodes( const std::vector<int>& valueList );
	void InvertList();
	void PrintList() const;
	void MakeEmpty();	
	void RecursivePrint( ListNode* currentNode, int i ) const;
	void PrintMap() const;

	ListNode* LinearSearchNode( const int& value ) const;
	ListNode* DirectSearchNode( const int& value ) const;	
	ListNode* FindMiddleOrLastNode( const bool getMiddle = true );	


	// Operator overloads
	SingleLinkedList& operator=( const SingleLinkedList& rhs );
	SingleLinkedList& operator=( SingleLinkedList&& rhs ) noexcept;

	// Prefix
	SingleLinkedList& operator++();
	SingleLinkedList& operator--();

	// Postfix
	SingleLinkedList operator++(int);
	SingleLinkedList operator--(int);

	int GetNodeCount() const
	{
		return m_NodeCount;
	}

	int GetElementCount() const
	{
		return m_ElementCount;
	}

	int GetNodeMapSize() const
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

#endif // !SINGLELINKEDLIST_H

