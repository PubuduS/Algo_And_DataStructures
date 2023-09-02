#include <iostream>
#include "SinglelinkedList.h"

using std::cout;
using std::endl;

int main()
{
	SingleLinkedList myObj;

	myObj.InsertNode(5);
	myObj.InsertNode(1);
	myObj.InsertNode(1);
	myObj.InsertNode(6);
	myObj.InsertNode(8);
	myObj.InsertNode(2);
	myObj.InsertNode(3);

	cout << " middle "<< myObj.FindMiddleOrLastNode( false )->value << endl;
	SingleLinkedList myObj2( myObj );
		
	myObj.DeleteNode(6);
	myObj.PrintList();
	cout << "Second List" << endl;
	
	myObj2.DeleteNode(5);
	myObj2.DeleteNode(8);
	cout << "After delete" << endl;
	myObj2.PrintList();
		
	cout << myObj2.DirectSearchNode(6)->value << endl;	
	myObj.PrintList();
	cout << myObj2.GetTail()->value << endl;

	cout << "\n------Testing move constructor-------" << endl;
	SingleLinkedList myObj3;
	myObj3.InsertNode(1);
	myObj3.InsertNode(2);
	myObj3.InsertNode(3);
	myObj3.InsertNode(4);
	myObj3.PrintList();
	myObj3.PrintMap();

	SingleLinkedList myObj4( std::move( myObj3 ) );
	cout << " \n-----moved from obj3 to obj4----- " << endl;
	myObj3.PrintList();
	myObj4.PrintList();
	cout<<"Elements: "<<myObj4.GetElementCount() << endl;
	cout << "Nodes: " << myObj4.GetNodeCount() << endl;
	cout << "Value: " << myObj4.DirectSearchNode(4)->value<<endl;
	cout << "Linear Value: " << myObj4.LinearSearchNode(4)->value << endl;
	myObj4.PrintMap();

	cout << " \n----moving back from obj4 to obj3----- " << endl;
	myObj3 = std::move(myObj4);
	myObj3.PrintList();
	myObj4.PrintList();

	cout << "Prefix ++ " << endl;	
	++myObj3;
	++myObj3;
	++myObj3;	
	--myObj3;
	--myObj3;
	--myObj3;

	myObj3++;
	myObj3++;
	myObj3++;
	myObj3--;
	myObj3--;
	myObj3--;

	myObj3.PrintList();

	SingleLinkedList myObj5;
	myObj5--;
	myObj5.PrintList();
}