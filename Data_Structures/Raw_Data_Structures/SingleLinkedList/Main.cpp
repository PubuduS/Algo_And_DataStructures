#include <iostream>
#include "SinglelinkedList.h"

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

	std::cout << " middle "<< myObj.FindMiddleOrLastNode(false)->value << std::endl;
	SingleLinkedList myObj2( myObj );
		
	myObj.DeleteNode(6);
	myObj.PrintList();
	std::cout << "Second List" << std::endl;
	
	myObj2.DeleteNode(5);
	myObj2.DeleteNode(8);
	std::cout << "After delete" << std::endl;
	myObj2.PrintList();
		
	std::cout << myObj2.DirectSearchNode(6)->value << std::endl;
	myObj.PrintList();
	std::cout << myObj2.GetTail()->value << std::endl;
}