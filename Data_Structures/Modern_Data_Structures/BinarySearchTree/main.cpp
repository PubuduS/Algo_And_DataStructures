#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree myBST;
	myBST.InsertNode( 15 );
	myBST.InsertNode( 10 );
	myBST.InsertNode( 5 );
	myBST.InsertNode( 4 );
	myBST.InsertNode( 25 );
	myBST.Display();
	std::cout << "Depth " << myBST.GetDepth( myBST.GetRoot() ) << std::endl;
	myBST.MirrorTree( myBST.GetRoot() );
	myBST.Display( BinarySearchTree::OrderFlag::INORDER );
	//myBST.Display( BST::OrderFlag::PREORDER );
	//myBST.Display( BST::OrderFlag::POSTORDER );

	BinarySearchTree myBST1;
	myBST1.InsertNode( 32 );
	myBST1.InsertNode( 48 );
	myBST1.InsertNode( 12 );
	myBST1.InsertNode( 8) ;
	myBST1.InsertNode( 16 );
	myBST1.InsertNode( 36 );
	myBST1.InsertNode( 52 );
	myBST1.Display();

	std::cout << "---------------" << std::endl;
	BinarySearchTree myBST3( myBST1 );
	myBST3.Display();

	std::cout << "------Opr Overloaded-------" << std::endl;
	myBST3 = myBST;
	myBST3.Display();

	std::cout << "------Construct from in and pre order -------" << std::endl;
	std::vector<int> preorder{ 3, 9, 20, 15, 7 };
	std::vector<int> postorder{ 9, 15, 7, 20, 3 };
	std::vector<int> inorder{ 9, 3, 15, 20, 7 };

	BinarySearchTree myBST4;
	//myBST4.ConstructBST( preorder, inorder, true );
	myBST4.ConstructBST(postorder, inorder, false);
	myBST4.Display();

	return 0;
}