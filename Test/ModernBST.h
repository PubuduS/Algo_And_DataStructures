#pragma once
#include "pch.h"
#include "gtest/gtest.h"
#include <iostream>
#include "../Data_Structures/Modern_Data_Structures/BinarySearchTree/BinarySearchTree.h"
#include "../Data_Structures/Modern_Data_Structures/BinarySearchTree/BinarySearchTree.cpp"

class ModernBST : public testing::Test
{
protected:

    // Some expensive resource shared by all tests.
    static std::unique_ptr<BinarySearchTree> firstObj;

    // Per-test-suite set-up.
     // Called before the first test in this test suite.
     // Can be omitted if not needed.
    static void SetUpTestCase()
    {    
        //std::cerr << "TestSuiteSetup" << std::endl;
        firstObj = std::make_unique<BinarySearchTree>(); 
    }

    // Per-test-suite tear-down.
    // Called after the last test in this test suite.
    // Can be omitted if not needed.
    static void TearDownTestCase() {
        //std::cerr << "TestSuiteDeleted" << std::endl;
    }

    // You can define per-test set-up logic as usual.
    void SetUp() override 
    {    
        
    }

    // You can define per-test tear-down logic as usual.
    void TearDown() override 
    {
        std::cerr << "------------" << std::endl;
    }
};


