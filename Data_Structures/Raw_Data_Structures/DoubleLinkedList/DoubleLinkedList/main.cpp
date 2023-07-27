#include <iostream>
#include "DoubleLinkedList.h"

using std::cout;
using std::endl;

int main()
{
	DoubleLinkedList myObj;

	myObj.InsertNode( 0 );
	myObj.InsertNode( 1 );
	myObj.InsertNode( 2 );
	myObj.InsertNode( 3 );
	myObj.InsertNode( 4 );
	//myObj.PrintList();

	myObj.InsertNode( 2 );
	myObj.InsertNode( 2 );
	myObj.InsertNode( 0 );
	myObj.InsertNode( -1 );
	myObj.InsertNode( 18 );
	myObj.InsertNode( 5 );	
	myObj.PrintList();	
	
	std::vector<int> numList { 5, 6, 7, 8, 9, 19, 20, 21};
	myObj.InsertMultipleNodes( numList );
	myObj.InsertNode(6);
	myObj.PrintList();	
	cout << "Search " << myObj.LinearSearchNode(9)->value << endl;
	cout << "Search " << myObj.DirectSearchNode(9)->value << endl;
	//myObj.DeleteNode(-1);
	//myObj.DeleteNode(21);
	//myObj.DeleteNode(0);
	//myObj.DeleteNode(18);
	//myObj.RemoveMultipleNodes( numList );
	myObj.PrintList();
	
	//myObj.PrintMap();
	//myObj.RecursivePrint( myObj.GetHead(), 0 );
	myObj.InvertList();	
	cout << "Tail " << myObj.GetTail()->value <<" Head "<< myObj.GetHead()->value << endl;
	//myObj.MakeEmpty();	
	myObj.PrintList();
	

	DoubleLinkedList myObj1;
	myObj1.InsertNode(1);
	myObj1.InsertNode(2);
	myObj1.InsertNode(8);
	myObj1.InsertNode(9);
	myObj1.PrintList();
	

	
	DoubleLinkedList myObj2( myObj );
	myObj2.PrintList();
	
	myObj1 = myObj2;
	myObj1.InsertNode(6);
	myObj1.InsertNode(21);
	myObj1.InsertNode(-1);	
	myObj1.PrintList();
	cout << "-------NodeCount " << myObj1.GetNodeCount() << " Element Count " << myObj1.GetElementCount() << endl;
	myObj1.RemoveMultipleNodes( { 5, 6, 7, 8, 9, 19, 0, 0, -1, -1, 21, 20, 18, 21, 6, 6, 5, 4, 3, 2, 1, 2, 2 } );
	cout << "NodeCount " << myObj1.GetNodeCount() <<" Element Count " <<myObj1.GetElementCount()<< endl;
	myObj1.PrintList();	
	//cout << "Direct Search Result " << myObj1.DirectSearchNode(6)->value << endl;
	//cout << "Direct Search Result " << myObj1.DirectSearchNode(-1)->value << endl;


	DoubleLinkedList myObj3;
	myObj3.InsertNode(1);
	myObj3.InsertNode(2);
	myObj3.InsertNode(3);
	myObj3.InsertNode(4);
	myObj3.PrintList();

	DoubleLinkedList myObj4( std::move( myObj3 ) );
	
	cout << " moved from obj3 to obj4 " << endl;
	myObj3.PrintList();
	myObj4.PrintList();

	cout << " moving back from obj4 to obj3 " << endl;
	myObj3 = std::move( myObj4 );
	//myObj3.PrintList();
	//myObj4.PrintList();

	cout << "Prefix ++ " << endl;
	DoubleLinkedList myObj5;
	++myObj3;
	++myObj3;
	++myObj3;
	++myObj3;
	--myObj3;
	--myObj3;
	--myObj3;
	--myObj3;

	myObj3.PrintList();
}