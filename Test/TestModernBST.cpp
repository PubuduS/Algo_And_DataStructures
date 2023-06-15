#include "pch.h"
#include "ModernBST.h"

std::unique_ptr<BinarySearchTree> ModernBST::firstObj = nullptr;

TEST_F( ModernBST, CheckEmptyTree )
{	
	
	ASSERT_TRUE( firstObj->IsEmpty() );	
}

TEST_F( ModernBST, InsertRootValue )
{		
	firstObj->InsertNode( 30 );
	ASSERT_EQ( firstObj->GetRoot()->value, 30 );
	ASSERT_EQ( firstObj->GetRoot()->count, 1 );
	ASSERT_EQ( firstObj->GetRoot()->left, nullptr );
	ASSERT_EQ( firstObj->GetRoot()->right, nullptr );
	ASSERT_FALSE( firstObj->IsEmpty() );
	
}

TEST_F( ModernBST, CheckEmptyTreeAfterInsertion )
{
	ASSERT_FALSE( firstObj->IsEmpty() );	
}

TEST_F( ModernBST, InsertFirstLeftValue )
{
	firstObj->InsertNode( 20 );
	ASSERT_EQ( firstObj->GetRoot()->left->value, 20 );
	ASSERT_EQ( firstObj->GetRoot()->left->count, 1 );
	ASSERT_NE( firstObj->GetRoot()->left, nullptr );
	ASSERT_EQ( firstObj->GetRoot()->right, nullptr );	
}

TEST_F( ModernBST, InsertFirstRightValue )
{
	firstObj->InsertNode( 40 );
	ASSERT_EQ( firstObj->GetRoot()->right->value, 40 );
	ASSERT_EQ( firstObj->GetRoot()->right->count, 1 );
	ASSERT_NE( firstObj->GetRoot()->left, nullptr );
	ASSERT_NE( firstObj->GetRoot()->right, nullptr );	
}

TEST_F( ModernBST, CheckGetRoot )
{	
	ASSERT_EQ( firstObj->GetRoot()->value, 30 );	
}

TEST_F( ModernBST, CheckNoOfElementsNoDuplicates )
{
	EXPECT_EQ( firstObj->GetNoOfElements(), 3 );	
}

TEST_F( ModernBST, CheckNoOfNodesNoDuplicates )
{
	EXPECT_EQ( firstObj->GetNoOfNodes(), 3 );	
}

TEST_F( ModernBST, InsertDuplicateValue )
{
	firstObj->InsertNode( 40 );
	ASSERT_EQ( firstObj->GetRoot()->right->value, 40 );
	ASSERT_EQ( firstObj->GetRoot()->right->count, 2 );
	ASSERT_NE( firstObj->GetRoot()->left, nullptr );
	ASSERT_NE( firstObj->GetRoot()->right, nullptr );	
}

TEST_F( ModernBST, CheckNoOfElementsDuplicates )
{
	EXPECT_EQ( firstObj->GetNoOfElements(), 4 );	
}

TEST_F( ModernBST, CheckNoOfNodesDuplicates )
{
	EXPECT_EQ( firstObj->GetNoOfNodes(), 3 );	
}

TEST_F( ModernBST, RemoveFirstLeftNode )
{
	firstObj->RemoveNode( 20 );
	ASSERT_EQ( firstObj->GetRoot()->left, nullptr );	
}

TEST_F( ModernBST, RemoveFirstRightDuplicateNode )
{
	firstObj->RemoveNode( 40 );
	ASSERT_EQ(firstObj->GetRoot()->right->count, 1 );	
}

TEST_F( ModernBST, RemoveRoot )
{
	firstObj->RemoveNode( 30 );
	ASSERT_EQ( firstObj->GetRoot()->value, 40 );
	ASSERT_EQ( firstObj->GetRoot()->left, nullptr );
	ASSERT_EQ( firstObj->GetRoot()->right, nullptr );
	EXPECT_EQ( firstObj->GetNoOfElements(), 1 );
	EXPECT_EQ( firstObj->GetNoOfNodes(), 1 );	
}

TEST_F( ModernBST, RemoveLastNode )
{
	firstObj->RemoveNode( 40 );
	ASSERT_EQ( firstObj->GetRoot(), nullptr );
	EXPECT_EQ( firstObj->GetNoOfElements(), 0 );
	EXPECT_EQ( firstObj->GetNoOfNodes(), 0 );
	EXPECT_TRUE( firstObj->IsEmpty() );	
}

TEST_F( ModernBST, DisplayInOrderEmptyTree ) 
{
	testing::internal::CaptureStdout();
	firstObj->Display();
	std::string output = testing::internal::GetCapturedStdout();
	//EXPECT_EQ("In Order Travesal \n40 ( 1 ) \n", output);
	EXPECT_EQ("Nothing to display here. Tree is empty.\n", output);	
}

TEST_F( ModernBST, ConstructFromList )
{
	std::vector<int> numList { 30, 20, 40, 15, 25, 35, 45, 12, 18, 22, 27, 31, 39, 42, 48 };	
	firstObj->ConstructBST( numList );

	testing::internal::CaptureStdout();
	firstObj->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );	
}

TEST_F( ModernBST, GetDepthBalancedTree )
{	
	ASSERT_EQ( firstObj->GetDepth( firstObj->GetRoot() ), 4 );	
}

TEST_F( ModernBST, GetMinElement )
{
	EXPECT_EQ( firstObj->GetMiniElement(), 12 );	
}

TEST_F( ModernBST, GetMinNode )
{
	ASSERT_EQ( firstObj->GetMinNode( firstObj->GetRoot() )->value, 12 );	
}

TEST_F( ModernBST, GetMaxElement )
{
	EXPECT_EQ( firstObj->GetMaxElement(), 48 );	
}

TEST_F( ModernBST, GetMaxNode )
{
	ASSERT_EQ( firstObj->GetMaxNode( firstObj->GetRoot() )->value, 48 );	
}

TEST_F( ModernBST, SearchNonExistingVal )
{
	ASSERT_FALSE( firstObj->SearchNode( 100 ) );	
}

TEST_F( ModernBST, SearchExistingVal )
{
	ASSERT_TRUE( firstObj->SearchNode( 25 ) );	
}

TEST_F( ModernBST, DisplayPreOrder )
{
	testing::internal::CaptureStdout();
	firstObj->Display( BinarySearchTree::OrderFlag::PREORDER );
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Pre Order Travesal \n30 ( 1 ) \n20 ( 1 ) \n15 ( 1 ) \n12 ( 1 ) \n18 ( 1 ) \n25 ( 1 ) \n22 ( 1 ) \n27 ( 1 ) \n40 ( 1 ) \n35 ( 1 ) \n31 ( 1 ) \n39 ( 1 ) \n45 ( 1 ) \n42 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );	
}

TEST_F( ModernBST, DisplayPostOrder )
{
	testing::internal::CaptureStdout();
	firstObj->Display( BinarySearchTree::OrderFlag::POSTORDER );
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Post Order Travesal \n12 ( 1 ) \n18 ( 1 ) \n15 ( 1 ) \n22 ( 1 ) \n27 ( 1 ) \n25 ( 1 ) \n20 ( 1 ) \n31 ( 1 ) \n39 ( 1 ) \n35 ( 1 ) \n42 ( 1 ) \n48 ( 1 ) \n45 ( 1 ) \n40 ( 1 ) \n30 ( 1 ) \n";
	EXPECT_EQ( expected, output );
}

TEST_F( ModernBST, InverseTree )
{	
	firstObj->MirrorTree( firstObj->GetRoot() );

	testing::internal::CaptureStdout();
	firstObj->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n48 ( 1 ) \n45 ( 1 ) \n42 ( 1 ) \n40 ( 1 ) \n39 ( 1 ) \n35 ( 1 ) \n31 ( 1 ) \n30 ( 1 ) \n27 ( 1 ) \n25 ( 1 ) \n22 ( 1 ) \n20 ( 1 ) \n18 ( 1 ) \n15 ( 1 ) \n12 ( 1 ) \n";
	EXPECT_EQ( expected, output );
	firstObj->MirrorTree( firstObj->GetRoot() );
}

TEST_F( ModernBST, ConstructFromInandPreOrder )
{
	std::vector<int> inorder { 12, 15, 18, 20, 22, 25, 27, 30, 31, 35, 39, 40, 42, 45, 48 };
	std::vector<int> preorder{ 30, 20, 15, 12, 18, 25, 22, 27, 40, 35, 31, 39, 45, 42, 48 };

	auto construct = std::make_unique<BinarySearchTree>();	
	construct->ConstructBST( preorder, inorder, true );

	testing::internal::CaptureStdout();
	construct->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );	
}

TEST_F( ModernBST, ConstructFromInandPostOrder )
{
	std::vector<int> inorder{ 12, 15, 18, 20, 22, 25, 27, 30, 31, 35, 39, 40, 42, 45, 48 };
	std::vector<int> postorder{ 12, 18, 15, 22, 27, 25, 20, 31, 39, 35, 42, 48, 45, 40, 30 };

	auto construct = std::make_unique<BinarySearchTree>();
	construct->ConstructBST( postorder, inorder, false );

	testing::internal::CaptureStdout();
	construct->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );
}

TEST_F( ModernBST, CopyConstructorCheck )
{
	auto construct = std::make_unique<BinarySearchTree>( *firstObj );

	testing::internal::CaptureStdout();
	construct->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );
}

TEST_F( ModernBST, CopyConstructorOperatorOverloadCheck )
{
	auto construct = std::make_unique<BinarySearchTree>( *firstObj );	

	testing::internal::CaptureStdout();
	construct->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ(expected, output);
}

TEST_F( ModernBST, MoveConstructorCheck )
{
	auto copiedObject = std::make_unique<BinarySearchTree>( *firstObj );
	testing::internal::CaptureStdout();
	copiedObject->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );

	auto newObj = std::make_unique<BinarySearchTree>( std::move( *copiedObject ) );

	ASSERT_TRUE( copiedObject->IsEmpty() );
	ASSERT_FALSE( newObj->IsEmpty() );

	testing::internal::CaptureStdout();
	newObj->Display();
	output = testing::internal::GetCapturedStdout();
	expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	ASSERT_EQ( expected, output );
	ASSERT_EQ( newObj->GetNoOfNodes(), 15 );

}

TEST_F( ModernBST, MoveConstructorOperatorOverloadCheck )
{
	auto copiedObject = std::make_unique<BinarySearchTree>( *firstObj );
	testing::internal::CaptureStdout();
	copiedObject->Display();
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	EXPECT_EQ( expected, output );

	auto newObj = std::move( *copiedObject );

	ASSERT_TRUE( copiedObject->IsEmpty() );
	ASSERT_FALSE( newObj.IsEmpty() );

	testing::internal::CaptureStdout();
	newObj.Display();
	output = testing::internal::GetCapturedStdout();
	expected = "In Order Travesal \n12 ( 1 ) \n15 ( 1 ) \n18 ( 1 ) \n20 ( 1 ) \n22 ( 1 ) \n25 ( 1 ) \n27 ( 1 ) \n30 ( 1 ) \n31 ( 1 ) \n35 ( 1 ) \n39 ( 1 ) \n40 ( 1 ) \n42 ( 1 ) \n45 ( 1 ) \n48 ( 1 ) \n";
	ASSERT_EQ( expected, output );
	ASSERT_EQ( newObj.GetNoOfNodes(), 15 );

}