#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include <unordered_map>

class BinarySearchTree
{
	private:
		struct TreeNode
		{
			int value;
			int count;
			TreeNode* left;
			TreeNode* right;
						
			TreeNode() = default;

			// Prevents explicit conversions
			explicit TreeNode( const int& val ) : value( val ), count( 1 ), left( nullptr ), right( nullptr ) {}
		};

		TreeNode* m_Root;
		int m_NoOfElems;
		int m_NoOfNodes;

		void Insert( TreeNode*& nodePtr, TreeNode*& newNode  );
		void DestroySubTree( TreeNode* nodePtr );
		void DeleteNode( const int& value, TreeNode*& nodePtr );
		void MakeDeletion( TreeNode*& nodePtr );
		void DisplayInOrder( TreeNode* nodePtr ) const;
		void DisplayPreOrder( TreeNode* nodePtr ) const;
		void DisplayPostOrder( TreeNode* nodePtr ) const;
		void DeleteAndReLink( TreeNode*& nodePtr, TreeNode*& branchToLink );

		TreeNode* ConstructBSTPreorder( std::vector<int>& preorder, int preStart, int preEnd, std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map );
		TreeNode* ConstructBSTPostorder( std::vector<int>& postorder, int postStart, int postEnd, std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map );

		bool CheckBSTConstructionConditions( std::vector<int>& preorder, std::vector<int>& inorder );

	public:
		// Constructor
		BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& other );
		BinarySearchTree& operator=( const BinarySearchTree& rhs );
		// Destructor
		~BinarySearchTree();

		const enum class OrderFlag
		{
			INORDER = 0,
			PREORDER = 1,
			POSTORDER = 2
		};

		void InsertNode( const int& value );		
		void RemoveNode( const int& value );
		void MirrorTree( TreeNode* nodePtr );
		void ConstructBST( std::vector<int>& );
		void ConstructBST( std::vector<int>&, std::vector<int>&, bool isPreOrder = true );
		void Display( const BinarySearchTree::OrderFlag flag = OrderFlag::INORDER ) const;

		bool SearchNode( const int& numbers );
		
		bool IsEmpty() const
		{
			return m_Root == nullptr;
		}

		int GetDepth( TreeNode* nodePtr );
		int GetMiniElement() const;
		int GetMaxElement() const;

		TreeNode* DeepCopy( TreeNode* rhs );
		const TreeNode* GetMaxNode( TreeNode* nodePtr ) const;
		const TreeNode* GetMinNode( TreeNode* nodePtr ) const;

		TreeNode* GetRoot() const
		{
			return m_Root;
		}

		int GetNoOfElements() const
		{
			return m_NoOfElems;
		}

		int GetNoOfNodes() const
		{
			return m_NoOfNodes;
		}			
};

#endif

