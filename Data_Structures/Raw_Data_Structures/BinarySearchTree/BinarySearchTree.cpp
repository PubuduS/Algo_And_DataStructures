#include <iostream>
#include <unordered_set>
#include "BinarySearchTree.h"

using std::cout;
using std::endl;

BinarySearchTree::BinarySearchTree() : m_Root( nullptr ), m_NoOfElems( 0 ), m_NoOfNodes( 0 )
{	
}

BinarySearchTree::BinarySearchTree( const BinarySearchTree& other ) : m_Root( DeepCopy( other.m_Root ) ), m_NoOfElems( other.m_NoOfElems ), m_NoOfNodes( other.m_NoOfNodes )
{
}

BinarySearchTree::TreeNode* BinarySearchTree::DeepCopy( BinarySearchTree::TreeNode* rhs )
{
	if( rhs == nullptr )
	{
		return nullptr;
	}

	TreeNode* lhs = new TreeNode;
	lhs->value = rhs->value;
	lhs->count = rhs->count;
	lhs->left = DeepCopy( rhs->left );
	lhs->right = DeepCopy( rhs->right );
	return lhs;
}

BinarySearchTree::~BinarySearchTree()
{
	cout << "---- Destroying Tree ----" << endl;
	DestroySubTree( m_Root );
	m_Root = nullptr;
	Display( OrderFlag::INORDER );
	cout << "---- Done Destroying Tree ----" << endl;
}

void BinarySearchTree::InsertNode( const int& value )
{
	TreeNode* newNode = new TreeNode( value );
	Insert( m_Root, newNode );
}

void BinarySearchTree::Insert( TreeNode*& nodePtr, TreeNode*& newNode )
{
	if (nodePtr == nullptr)
	{
		nodePtr = newNode;
		m_NoOfElems++;
		m_NoOfNodes++;
		return;
	}		
	else if( newNode->value < nodePtr->value )
		Insert( nodePtr->left, newNode );
	else if( newNode->value > nodePtr->value )
		Insert( nodePtr->right, newNode );
	else if (newNode->value == nodePtr->value)
	{
		delete newNode;
		nodePtr->count++;
		m_NoOfElems++;
	}	
}

void BinarySearchTree::Display( const BinarySearchTree::OrderFlag flag ) const
{
	if( IsEmpty() )
	{
		cout << "Nothing to display here. Tree is empty." << endl;
		return;
	}

	switch( flag )
	{
		case BinarySearchTree::OrderFlag::INORDER:
			cout << "In Order Travesal " << endl;
			DisplayInOrder( m_Root );
			break;

		case BinarySearchTree::OrderFlag::PREORDER:
			cout << "Pre Order Travesal " << endl;
			DisplayPreOrder( m_Root );
			break;

		case BinarySearchTree::OrderFlag::POSTORDER:
			cout << "Post Order Travesal " << endl;
			DisplayPostOrder( m_Root );
			break;

		default:
			break;
	}
}

void BinarySearchTree::DisplayInOrder( TreeNode* nodePtr ) const
{
	if( nodePtr == nullptr )
		return;
	
	DisplayInOrder( nodePtr->left );
	cout << nodePtr->value << " ( " << nodePtr->count << " ) " << endl;
	DisplayInOrder( nodePtr->right );	
}

void BinarySearchTree::DisplayPreOrder( TreeNode* nodePtr ) const
{
	if( nodePtr == nullptr )
		return;
	  
	cout << nodePtr->value << " ( " << nodePtr->count << " ) " << endl;
	DisplayPreOrder( nodePtr->left );
	DisplayPreOrder( nodePtr->right );	
}

void BinarySearchTree::DisplayPostOrder( TreeNode* nodePtr ) const
{
	if( nodePtr == nullptr )
		return;

	DisplayPostOrder( nodePtr->left );
	DisplayPostOrder( nodePtr->right );
	cout << nodePtr->value << " ( " << nodePtr->count << " ) " << endl;	
}

int BinarySearchTree::GetDepth( TreeNode* nodePtr )
{
	if( nodePtr == nullptr )
		return 0;

	return std::max( GetDepth( nodePtr->left ), GetDepth( nodePtr->right ) ) + 1;
}

bool BinarySearchTree::SearchNode( const int& value )
{
	if( IsEmpty() )
	{
		cout << "List is empty" << endl;
		return false;
	}

	TreeNode* nodePtr = m_Root;	

	while( nodePtr != nullptr )
	{
		if( nodePtr->value == value )
			return true;
		else if( value < nodePtr->value )		
			nodePtr = nodePtr->left;		
		else		
			nodePtr = nodePtr->right;		
	}
	
	return false;
}

void BinarySearchTree::RemoveNode( const int& value )
{
	if( IsEmpty() )
	{
		cout << "List is empty" << endl;
		return;
	}

	DeleteNode( value, m_Root );
}

void BinarySearchTree::DeleteNode( const int& value, TreeNode*& nodePtr )
{
	if( value < nodePtr->value )
		DeleteNode( value, nodePtr->left );
	else if( value > nodePtr->value )
		DeleteNode( value, nodePtr->right );
	else
		MakeDeletion( nodePtr );
}

void BinarySearchTree::MakeDeletion( TreeNode*& nodePtr )
{
	TreeNode* tempNode = nullptr;

	if( nodePtr == nullptr )
	{
		cout << "Cannot Delete an Empty Node." << endl;
		return;
	}
	else if( nodePtr->left == nullptr )
	{
		DeleteAndReLink( nodePtr, nodePtr->right );
	}
	else if( nodePtr->right == nullptr )
	{
		DeleteAndReLink( nodePtr, nodePtr->left );
	}
	else if( ( nodePtr->left != nullptr && nodePtr->right != nullptr ) )
	{
		if( nodePtr->count > 1 )
		{
			nodePtr->count--;
			m_NoOfElems--;
			return;
		}

		// Move one down to the right
		tempNode = nodePtr->right;

		// Travel to the end of the left branch
		while( tempNode->left != nullptr )
			tempNode = tempNode->left;

		// Reattach the left sub branch of the node about to be deleted.
		tempNode->left = nodePtr->left;

		DeleteAndReLink( nodePtr, nodePtr->right );
		
	}
	else
	{
		cout << "Unknown Error while deleting node -> " << nodePtr->value << endl;
		return;
	}	
}

void BinarySearchTree::DeleteAndReLink( TreeNode*& nodePtr, TreeNode*& branchToLink )
{
	TreeNode* tempNode = nullptr;
	
	m_NoOfElems--;

	if( nodePtr->count > 1 )
	{
		nodePtr->count--;		
		return;
	}

	tempNode = nodePtr;
	nodePtr = branchToLink;
	m_NoOfNodes--;
	delete tempNode;	
}

void BinarySearchTree::DestroySubTree( TreeNode* nodePtr )
{
	if( nodePtr != nullptr )
	{
		if( nodePtr->left != nullptr )		
			DestroySubTree( nodePtr->left );
		if( nodePtr->right != nullptr )
			DestroySubTree( nodePtr->right );

		cout << "Node "<<nodePtr->value<<" Deleted" << endl;
		delete nodePtr;
		nodePtr = nullptr;
	}	
}

int BinarySearchTree::GetMiniElement() const
{
	TreeNode* nodePtr = m_Root;

	if( nodePtr == nullptr )
	{
		cout << "No Elements in the tree." << endl;
		return -1;
	}		

	while( nodePtr->left != nullptr )
		nodePtr = nodePtr->left;

	return nodePtr->value;
}

const BinarySearchTree::TreeNode* BinarySearchTree::GetMinNode( TreeNode* nodePtr ) const
{
	if( nodePtr == nullptr || nodePtr->left == nullptr )
	{
		return nodePtr;
	}

	return GetMinNode( nodePtr->left );
}

int BinarySearchTree::GetMaxElement() const
{
	TreeNode* nodePtr = m_Root;

	if( nodePtr == nullptr )
	{
		cout << "No Element in the tree" << endl;
		return -1;
	}

	while( nodePtr->right != nullptr )	
		nodePtr = nodePtr->right;
	
	return nodePtr->value;
}

const BinarySearchTree::TreeNode* BinarySearchTree::GetMaxNode( TreeNode* nodePtr ) const
{
	if( nodePtr == nullptr || nodePtr->right == nullptr )
	{
		return nodePtr;
	}

	return GetMaxNode( nodePtr->right );
}

void BinarySearchTree::MirrorTree( TreeNode* nodePtr )
{
	if( nodePtr == nullptr )	
		return;
	
	TreeNode* temp = nullptr;

	MirrorTree( nodePtr->left );
	MirrorTree( nodePtr->right );

	std::swap( nodePtr->left, nodePtr->right );
}

void BinarySearchTree::ConstructBST( std::vector<int>& numbers )
{
	if( !IsEmpty() )
	{
		cout << "A binary tree is already exist. This function is to create a new tree from number sequence." << endl;
		return;
	}

	for( auto& num : numbers )
	{
		InsertNode( num );
	}

}

void BinarySearchTree::ConstructBST( std::vector<int>& order, std::vector<int>& inorder, bool isPreOrder )
{

	if( CheckBSTConstructionConditions( order, inorder ) == false )
	{
		return;
	}

	const int inorderLen = inorder.size();
	std::unordered_map<int, int> map;

	for( int i = 0; i < inorderLen; ++i )
	{
		map[inorder[i]] = i;
	}

	if( isPreOrder == true )
	{
		m_Root = ConstructBSTPreorder( order, 0, inorderLen - 1, inorder, 0, inorderLen - 1, map );
	}
	else
	{
		m_Root = ConstructBSTPostorder( order, 0, inorderLen - 1, inorder, 0, inorderLen - 1, map );
	}

}

BinarySearchTree::TreeNode* BinarySearchTree::ConstructBSTPreorder( std::vector<int>& preorder, int preStart, int preEnd, 
																	std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map )
{
	if( preStart > preEnd || inStart > inEnd )
	{
		return nullptr;
	}

	TreeNode* root = new TreeNode( preorder[preStart] );
	int mid = map[root->value];
	int numLeft = mid - inStart;

	root->left = ConstructBSTPreorder( preorder, preStart + 1, preStart + numLeft, inorder, inStart, mid - 1, map );
	root->right = ConstructBSTPreorder( preorder, preStart + numLeft + 1, preEnd, inorder, mid + 1, inEnd, map );

	return root;
}

BinarySearchTree::TreeNode* BinarySearchTree::ConstructBSTPostorder( std::vector<int>& postorder, int postStart, int postEnd, 
																	 std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map )
{
	if( postStart > postEnd || inStart > inEnd )
	{
		return nullptr;
	}

	TreeNode* root = new TreeNode( postorder[postEnd] );
	int mid = map[root->value];
	int numLeft = mid - inStart;

	root->left = ConstructBSTPostorder( postorder, postStart, postStart + numLeft - 1, inorder, inStart, mid - 1, map );
	root->right = ConstructBSTPostorder( postorder, postStart + numLeft, postEnd - 1, inorder, mid + 1, inEnd, map );

	return root;
}

bool BinarySearchTree::CheckBSTConstructionConditions( std::vector<int>& preorder, std::vector<int>& inorder )
{
	const int preorderLen = preorder.size();
	const int inorderLen = inorder.size();

	std::unordered_map<int, int> hashMap;
	std::unordered_set<int> uniqueMap;

	if( preorderLen != inorderLen )
	{
		cout << "length of both vectors must be same" << endl;
		return false;
	}

	// check whether the vectors have unique values or not
	for( int i = 0; i < inorderLen; ++i )
	{
		auto result = uniqueMap.insert( inorder[i] );

		if( result.second == false )
		{
			cout << "Both vectors must contain the unique values" << endl;
			cout << "Value " << inorder[i] << " is a duplicate " << endl;
			return false;
		}
	}

	// Check to see both vectors have same value or not
	for( int i = 0; i < inorderLen; ++i )
	{
		hashMap[inorder[i]] = i;
	}

	for( int i = 0; i < preorderLen; ++i )
	{
		if( hashMap.find( preorder[i]) == hashMap.end() )
		{
			cout << "Both vectors must contain the same values" << endl;
			return false;
		}
	}

	return true;
}

BinarySearchTree& BinarySearchTree::operator=( const BinarySearchTree& rhs )
{
	// Prevent self assignment
	if( this != &rhs )
	{
		if( this->m_Root != nullptr )
		{
			DestroySubTree( m_Root );
		}

		if( rhs.m_Root == nullptr )
		{
			this->m_Root = nullptr;
		}
		else
		{
			this->m_Root = DeepCopy( rhs.m_Root );
		}
	}
	return *this;
}