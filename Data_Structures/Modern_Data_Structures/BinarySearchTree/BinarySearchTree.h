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

		void Insert( std::unique_ptr<TreeNode>&, std::unique_ptr<TreeNode>&  );
		void DestroySubTree( TreeNode* );
		void DeleteNode( const int&, std::unique_ptr<TreeNode>& );
		void MakeDeletion( std::unique_ptr<TreeNode>& );
		void DisplayInOrder( TreeNode* ) const;
		void DisplayPreOrder( TreeNode* ) const;
		void DisplayPostOrder( TreeNode* ) const;
		void DeleteAndReLink( std::unique_ptr<TreeNode>&, std::unique_ptr<TreeNode>& );

		std::unique_ptr<TreeNode> ConstructBSTPreorder( std::vector<int>&, int, int, std::vector<int>&, int, int, std::unordered_map<int, int>& );
		std::unique_ptr<TreeNode> ConstructBSTPostorder( std::vector<int>&, int, int, std::vector<int>&, int, int, std::unordered_map<int, int>& );

		bool CheckBSTConstructionConditions( std::vector<int>&, std::vector<int>& );

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

		void InsertNode( const int& );		
		void RemoveNode( const int& );		
		void MirrorTree( TreeNode* );
		void ConstructBST( std::vector<int>& );
		void ConstructBST( std::vector<int>&, std::vector<int>&, bool isPreOrder = true );
		void Display( const BinarySearchTree::OrderFlag flag = OrderFlag::INORDER ) const;

		bool SearchNode( const int& );
		bool IsEmpty() const;

		int GetDepth( TreeNode* );
		int GetMiniElement() const;
		int GetMaxElement() const;

		std::unique_ptr<TreeNode> DeepCopy( TreeNode* );
		const TreeNode* GetMaxNode( TreeNode* ) const;
		const TreeNode* GetMinNode( TreeNode* ) const;

		inline TreeNode* GetRoot() const
		{
			return m_Root.get();
		}

		inline int GetNoOfElements() const
		{
			return m_NoOfElems;
		}

		inline int GetNoOfNodes() const
		{
			return m_NoOfNodes;
		}			
};

#endif

