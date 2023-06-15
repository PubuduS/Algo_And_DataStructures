#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <memory>
#include <vector>
#include <unordered_map>

class BinarySearchTree
{
	private:
		struct TreeNode
		{
			int value;
			int count;
			std::unique_ptr<TreeNode> left;
			std::unique_ptr<TreeNode> right;
						
			TreeNode() = default;

			// Prevents explicit conversions
			explicit TreeNode( const int& val ) : value( val ), count( 1 ), left( nullptr ), right( nullptr ) {}
		};

		std::unique_ptr<TreeNode> m_Root;
		int m_NoOfElems;
		int m_NoOfNodes;

		void Insert( std::unique_ptr<TreeNode>& nodePtr, std::unique_ptr<TreeNode>& newNode );
		void DestroySubTree( TreeNode* nodePtr );
		void DeleteNode( const int& value, std::unique_ptr<TreeNode>& nodePtr );
		void MakeDeletion( std::unique_ptr<TreeNode>& nodePtr );
		void DisplayInOrder( TreeNode* nodePtr ) const;
		void DisplayPreOrder( TreeNode* nodePtr ) const;
		void DisplayPostOrder( TreeNode* nodePtr ) const;
		void DeleteAndReLink( std::unique_ptr<TreeNode>& nodePtr, std::unique_ptr<TreeNode>& branchToLink );

		std::unique_ptr<TreeNode> ConstructBSTPreorder( std::vector<int>& preorder, int preStart, int preEnd, std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map );
		std::unique_ptr<TreeNode> ConstructBSTPostorder( std::vector<int>& postorder, int postStart, int postEnd, std::vector<int>& inorder, int inStart, int inEnd, std::unordered_map<int, int>& map );

		bool CheckBSTConstructionConditions( std::vector<int>& preorder, std::vector<int>& inorder);

	public:
		// Constructors
		BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& other );

		// Move Constructor
		BinarySearchTree( BinarySearchTree&& other ) noexcept;

		// = Operator overload for deep copy
		BinarySearchTree& operator=( const BinarySearchTree& rhs );

		// = Operator overload for move schemantic
		BinarySearchTree& operator=( BinarySearchTree&& rhs ) noexcept;

		// Destructor
		~BinarySearchTree() = default;

		enum class OrderFlag
		{
			INORDER = 0,
			PREORDER = 1,
			POSTORDER = 2
		};

		void InsertNode( const int& value );		
		void RemoveNode( const int& value );
		void MirrorTree( TreeNode* nodePtr );
		void ConstructBST( std::vector<int>& numbers );
		void ConstructBST( std::vector<int>& order, std::vector<int>& inorder, bool isPreOrder = true );
		void Display( const BinarySearchTree::OrderFlag flag = OrderFlag::INORDER ) const;

		bool SearchNode( const int& value );
		
		bool IsEmpty() const
		{
			return m_Root == nullptr;		
		}

		int GetDepth( TreeNode* nodePtr );
		int GetMiniElement() const;
		int GetMaxElement() const;

		std::unique_ptr<TreeNode> DeepCopy( TreeNode* rhs );
		const TreeNode* GetMaxNode( TreeNode* nodePtr ) const;
		const TreeNode* GetMinNode( TreeNode* nodePtr ) const;

		TreeNode* GetRoot() const
		{
			return m_Root.get();
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

