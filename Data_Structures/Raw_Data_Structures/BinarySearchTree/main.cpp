#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree bstObj;
	//std::vector<int> numbers { 5, 8, 8, 8, 7, 3, 12, 9 };
	//bstObj.ConstructBST( numbers );

	bstObj.InsertNode( 5 );
	bstObj.InsertNode( 8 );
	bstObj.InsertNode( 8 );
	bstObj.InsertNode( 8 );
	bstObj.InsertNode( 7 );
	bstObj.InsertNode( 3 );
	bstObj.InsertNode( 12 );
	bstObj.InsertNode( 9 );
	
	bstObj.Display( BinarySearchTree::OrderFlag::INORDER );	
	bstObj.Display( BinarySearchTree::OrderFlag::PREORDER );
	bstObj.Display( BinarySearchTree::OrderFlag::POSTORDER );

	std::cout << "Depth "<< bstObj.GetDepth( bstObj.GetRoot() ) << std::endl;
	std::cout << "------ No of elements -----" << std::endl;
	std::cout << bstObj.GetNoOfElements() << std::endl;
	std::cout << bstObj.GetNoOfNodes() << std::endl;

	std::cout << "------ Deleting -----" << std::endl;
	bstObj.RemoveNode(8);
	// bstObj.RemoveNode(8);
	// bstObj.RemoveNode(8);
	bstObj.MirrorTree( bstObj.GetRoot() );
	bstObj.Display( BinarySearchTree::OrderFlag::INORDER );
	std::cout << "Min -> "<< bstObj.GetMiniElement() << std::endl;
	std::cout << "Max -> " << bstObj.GetMaxElement() << std::endl;


	BinarySearchTree bstObj1( bstObj );
	std::cout << "Testing copy constructor " << std::endl;
	bstObj1.InsertNode( 33 );
	bstObj1.Display( BinarySearchTree::OrderFlag::INORDER );

	std::cout << "Testing overloaded = operator" << std::endl;
	BinarySearchTree bstObj2;
	BinarySearchTree bstObj3;
	bstObj3.InsertNode(15);

	bstObj2.InsertNode( 5 );
	bstObj2.InsertNode( 8 );
	bstObj2.InsertNode( 8 );

	bstObj3 = bstObj2;
	bstObj3.Display( BinarySearchTree::OrderFlag::INORDER );

	std::cout << "MinNode " << bstObj2.GetMinNode( bstObj2.GetRoot() )->value <<" min Elem " << bstObj2.GetMiniElement() << std::endl;
	std::cout << "MaxNode " << bstObj2.GetMaxNode( bstObj2.GetRoot() )->value << " max Elem " << bstObj2.GetMaxElement() << std::endl;

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