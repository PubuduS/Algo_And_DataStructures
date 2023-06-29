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


public:
	SingleLinkedList();
	SingleLinkedList( const SingleLinkedList& rhs );
	~SingleLinkedList();

	void InsertNode( const int& value );
	void InsertMultipleNodes( const std::vector<int>& valueList );
	void DeleteNode( const int& value );
	void RemoveMultipleNodes( const std::vector<int>& valueList );
	void InvertList();
	void PrintList() const;
	void MakeEmpty();	
	void RecursivePrint( ListNode* currentNode, int i ) const;

	ListNode* LinearSearchNode( const int& value, ListNode*& nodePtr ) const;
	ListNode* DirectSearchNode( const int& value ) const;	
	ListNode* FindMiddleOrLastNode( const bool getMiddle = true );
	ListNode* DeepCopy( ListNode* rhsPtr );

	SingleLinkedList& operator=( const SingleLinkedList& rhs );

	int GetNodeCount() const
	{
		return m_NodeCount;
	}

	int GetElementCount() const
	{
		return m_ElementCount;
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

	void PrintMap() const;


};

#endif // !SINGLELINKEDLIST_H

