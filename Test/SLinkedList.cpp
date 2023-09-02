#include "pch.h"
#include "SLinkedList.h"

std::unique_ptr<SingleLinkedList> SLinkedList::firstObj = nullptr;

TEST_F( SLinkedList, IsEmpty )
{
	EXPECT_TRUE( firstObj->IsEmpty() );
	EXPECT_EQ( firstObj->GetNodeCount(), 0 );
	EXPECT_EQ( firstObj->GetElementCount(), 0 );
	EXPECT_TRUE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead(), nullptr );
	EXPECT_EQ( firstObj->GetTail(), nullptr );
}

TEST_F( SLinkedList, InsertRoot )
{
	firstObj->InsertNode( 5 );
	EXPECT_FALSE( firstObj->IsEmpty() );
	EXPECT_EQ( firstObj->GetNodeCount(), 1 );
	EXPECT_EQ( firstObj->GetElementCount(), 1 );
	EXPECT_FALSE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead()->value, 5 );
	EXPECT_EQ( firstObj->GetTail(), firstObj->GetHead() );
}

TEST_F( SLinkedList, InsertSameRoot )
{
	firstObj->InsertNode( 5 );
	EXPECT_FALSE( firstObj->IsEmpty() );
	EXPECT_EQ( firstObj->GetNodeCount(), 1 );
	EXPECT_EQ( firstObj->GetElementCount(), 2 );
	EXPECT_FALSE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead()->value, 5 );
	EXPECT_EQ( firstObj->GetTail(), firstObj->GetHead() );
}

TEST_F( SLinkedList, FindMiddleValueTest1 )
{
	EXPECT_EQ( firstObj->FindMiddleOrLastNode()->value, 5 );
}

TEST_F( SLinkedList, InsertAnotherNode )
{
	firstObj->InsertNode( 1 );
	EXPECT_FALSE( firstObj->IsEmpty() );
	EXPECT_EQ( firstObj->GetNodeCount(), 2 );
	EXPECT_EQ( firstObj->GetElementCount(), 3 );
	EXPECT_TRUE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead()->value, 1 );
	EXPECT_EQ( firstObj->GetTail()->value, 5 );
}

TEST_F( SLinkedList, FindMiddleValueTest2 )
{	
	EXPECT_EQ( firstObj->FindMiddleOrLastNode()->value , 5 );
}

TEST_F( SLinkedList, DirectSearchTest1 )
{
	EXPECT_EQ( firstObj->DirectSearchNode( 5 )->next->value, 5 );
}

TEST_F( SLinkedList, PrintListTest1 )
{
	testing::internal::CaptureStdout();
	firstObj->PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Head -> 1 ( 1 ) -> 5 ( 2 ) -> NULL\n";
	EXPECT_EQ(expected, output);
}

TEST_F( SLinkedList, RecursivePrintListTest1 )
{
	testing::internal::CaptureStdout();
	firstObj->RecursivePrint( firstObj->GetHead(), 0 );
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Head -> 5 ( 2 ) -> 1 ( 1 ) -> NULL\n";
	EXPECT_EQ(expected, output);
}

TEST_F( SLinkedList, InvertListTest1 )
{
	firstObj->InvertList();
	testing::internal::CaptureStdout();
	firstObj->PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Head -> 5 ( 2 ) -> 1 ( 1 ) -> NULL\n";
	EXPECT_EQ( expected, output );
	firstObj->InvertList();
}

TEST_F( SLinkedList, DeleteNode )
{
	firstObj->DeleteNode( 5 );
	EXPECT_EQ( firstObj->GetNodeCount(), 2 );
	EXPECT_EQ( firstObj->GetElementCount(), 2 );
	EXPECT_TRUE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead()->value, 1 );
	EXPECT_EQ( firstObj->GetTail()->value, 5 );
	
	firstObj->DeleteNode( 1 );
	EXPECT_EQ( firstObj->GetNodeCount(), 1 );
	EXPECT_EQ( firstObj->GetElementCount(), 1 );
	EXPECT_FALSE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead()->value, 5 );
	EXPECT_EQ( firstObj->GetTail()->value, 5 );

	firstObj->DeleteNode( 5 );
	EXPECT_EQ( firstObj->GetNodeCount(), 0 );
	EXPECT_EQ( firstObj->GetElementCount(), 0 );
	EXPECT_TRUE( firstObj->IsListEven() );
	EXPECT_EQ( firstObj->GetHead(), nullptr );
	EXPECT_EQ( firstObj->GetTail(), nullptr );
}

TEST_F( SLinkedList, PrintEmptyList )
{
	testing::internal::CaptureStdout();
	firstObj->PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "List is empty!\n";
	EXPECT_EQ( expected, output );
}

TEST_F( SLinkedList, InsertMultipleVals )
{
	std::vector<int> valueList{ 5, 13, 98, 657, 3, 4, 5, 89, 44, 7, 11, 21, 21, 14, 61, 456, 31, 27, 56, 0 };
	firstObj->InsertMultipleNodes( valueList );
	testing::internal::CaptureStdout();
	firstObj->PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Head -> 0 ( 1 ) -> 3 ( 1 ) -> 4 ( 1 ) -> 5 ( 2 ) -> 7 ( 1 ) -> 11 ( 1 ) -> 13 ( 1 ) -> 14 ( 1 ) -> 21 ( 2 ) -> 27 ( 1 ) -> 31 ( 1 ) -> 44 ( 1 ) -> 56 ( 1 ) -> 61 ( 1 ) -> 89 ( 1 ) -> 98 ( 1 ) -> 456 ( 1 ) -> 657 ( 1 ) -> NULL\n";
	EXPECT_EQ( expected, output );
	EXPECT_EQ( firstObj->GetElementCount(), 20 );
	EXPECT_EQ( firstObj->GetNodeCount(), 18 );
	EXPECT_EQ( firstObj->GetHead()->value, 0 );
	EXPECT_EQ( firstObj->GetTail()->value, 657 );
	EXPECT_EQ( firstObj->FindMiddleOrLastNode()->value, 27 );
	EXPECT_EQ( firstObj->FindMiddleOrLastNode( false )->value, 657 );
	EXPECT_EQ( firstObj->DirectSearchNode( 5 )->value, firstObj->LinearSearchNode( 5 )->value );
}

TEST_F( SLinkedList, RemoveMultipleValues )
{
	std::vector<int> valueList{ 5, 21, 21, 0, 657, 27, 44 };
	firstObj->RemoveMultipleNodes( valueList );
	testing::internal::CaptureStdout();
	firstObj->PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Head -> 3 ( 1 ) -> 4 ( 1 ) -> 5 ( 1 ) -> 7 ( 1 ) -> 11 ( 1 ) -> 13 ( 1 ) -> 14 ( 1 ) -> 31 ( 1 ) -> 56 ( 1 ) -> 61 ( 1 ) -> 89 ( 1 ) -> 98 ( 1 ) -> 456 ( 1 ) -> NULL\n";
	EXPECT_EQ( expected, output );
	EXPECT_EQ( firstObj->GetElementCount(), 14 );
	EXPECT_EQ( firstObj->GetNodeCount(), 13 );
	EXPECT_EQ( firstObj->GetNodeMapSize(), firstObj->GetNodeCount() );
	EXPECT_EQ( firstObj->DirectSearchNode( 21 ), firstObj->LinearSearchNode( 21 ) );
	EXPECT_EQ( firstObj->DirectSearchNode( 456 )->value, firstObj->LinearSearchNode( 456 )->value);
}

TEST_F( SLinkedList, InvertListTest2 )
{
	
	testing::internal::CaptureStdout();
	firstObj->RecursivePrint( firstObj->GetHead(), 0 );	
	std::string output = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	firstObj->InvertList();
	firstObj->PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, output);
}

TEST_F( SLinkedList, DestroyList )
{
	firstObj->MakeEmpty();
	EXPECT_EQ( firstObj->GetElementCount(), 0 );
	EXPECT_EQ( firstObj->GetNodeCount(), 0 );
	EXPECT_EQ( firstObj->GetHead(), nullptr );
	EXPECT_EQ( firstObj->GetTail(), nullptr );
	EXPECT_EQ( firstObj->GetNodeMapSize(), 0 );
}

TEST_F( SLinkedList, CheckCopyConstructor )
{
	std::vector<int> valueList{ 5, 13, 98, 657, 3, 4, 5, 89, 44, 7, 11, 21, 21, 14, 61, 456, 31, 27, 56, 0 };
	SingleLinkedList myObj1;	
	myObj1.InsertMultipleNodes( valueList );

	SingleLinkedList myObj2( myObj1 );

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	myObj2.PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( expected, output );
}

TEST_F( SLinkedList, CheckCopyAssignmentOperator )
{
	std::vector<int> valueList{ 5, 13, 98, 657, 3, 4, 5, 89, 44, 7, 11, 21, 21, 14, 61, 456, 31, 27, 56, 0 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	SingleLinkedList myObj2 = myObj1;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	myObj2.PrintList();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ( expected, output );
}

// Move constructor also use move assignment. Therefore, we can check both with this test case
TEST_F( SLinkedList, CheckMoveConstructor )
{
	std::vector<int> valueList{ 5, 13, 98, 657, 3, 4, 5, 89, 44, 7, 11, 21, 21, 14, 61, 456, 31, 27, 56, 0 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	SingleLinkedList myObj2 = std::move( myObj1 );

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();
	EXPECT_EQ( expected, "List is empty!\n" );

	testing::internal::CaptureStdout();
	myObj2.PrintList();
	expected = testing::internal::GetCapturedStdout();
	EXPECT_EQ( expected, "Head -> 0 ( 1 ) -> 3 ( 1 ) -> 4 ( 1 ) -> 5 ( 2 ) -> 7 ( 1 ) -> 11 ( 1 ) -> 13 ( 1 ) -> 14 ( 1 ) -> 21 ( 2 ) -> 27 ( 1 ) -> 31 ( 1 ) -> 44 ( 1 ) -> 56 ( 1 ) -> 61 ( 1 ) -> 89 ( 1 ) -> 98 ( 1 ) -> 456 ( 1 ) -> 657 ( 1 ) -> NULL\n" );
}

TEST_F( SLinkedList, CheckPrefixIncrementOnEmptyList )
{
	SingleLinkedList myObj1;
	++myObj1;
	++myObj1;
	++myObj1;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "Head -> -2 ( 1 ) -> -1 ( 1 ) -> 0 ( 1 ) -> NULL\n" );
}

TEST_F( SLinkedList, CheckPrefixIncrementOnList )
{
	std::vector<int> valueList{ 4, 2, 3, 1 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	++myObj1;
	++myObj1;
	++myObj1;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "Head -> -2 ( 1 ) -> -1 ( 1 ) -> 0 ( 1 ) -> 1 ( 1 ) -> 2 ( 1 ) -> 3 ( 1 ) -> 4 ( 1 ) -> NULL\n" );
}

TEST_F( SLinkedList, CheckPrefixDecrementOnEmptyList )
{
	SingleLinkedList myObj1;
	--myObj1;
	--myObj1;
	--myObj1;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "List is empty!\n" );
}

TEST_F( SLinkedList, CheckPrefixDecrementOnList )
{
	std::vector<int> valueList{ 4, 2, 3, 1 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	--myObj1;
	--myObj1;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "Head -> 3 ( 1 ) -> 4 ( 1 ) -> NULL\n" );
}

TEST_F( SLinkedList, CheckPostfixIncrementOnEmptyList )
{
	SingleLinkedList myObj1;
	myObj1++;
	myObj1++;
	myObj1++;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expected, "Head -> 0 ( 1 ) -> 1 ( 1 ) -> 2 ( 1 ) -> NULL\n");
}

TEST_F( SLinkedList, CheckPostfixIncrementOnList )
{
	std::vector<int> valueList{ 4, 2, 3, 1 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	myObj1++;
	myObj1++;
	myObj1++;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "Head -> 1 ( 1 ) -> 2 ( 1 ) -> 3 ( 1 ) -> 4 ( 1 ) -> 5 ( 1 ) -> 6 ( 1 ) -> 7 ( 1 ) -> NULL\n" );
}

TEST_F( SLinkedList, CheckPostfixDecrementOnEmptyList )
{
	SingleLinkedList myObj1;
	myObj1--;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ( expected, "List is empty!\n" );
}

TEST_F( SLinkedList, CheckPostfixDecrementOnList )
{
	std::vector<int> valueList{ 4, 2, 3, 1 };
	SingleLinkedList myObj1;
	myObj1.InsertMultipleNodes( valueList );

	myObj1--;
	myObj1--;

	testing::internal::CaptureStdout();
	myObj1.PrintList();
	std::string expected = testing::internal::GetCapturedStdout();

	EXPECT_EQ(expected, "Head -> 1 ( 1 ) -> 2 ( 1 ) -> NULL\n");
}


