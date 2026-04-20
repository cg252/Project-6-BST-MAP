#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

// Empty tree, 
// check size is 0, height is 0, find returns end
TEST(empty_tree_test) {
    BinarySearchTree<int> testTree;
    
    ASSERT_EQUAL(testTree.size(), 0u);
    ASSERT_EQUAL(testTree.height(), 0u);
    ASSERT_EQUAL(testTree.find(0), testTree.end());
    ASSERT_TRUE(testTree.empty());
}

// Single node, 
// insert one element, check size is 1, height is 1
TEST(single_node_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(1);

    ASSERT_EQUAL(testTree.size(), 1u);
    ASSERT_EQUAL(testTree.height(), 1u);
    ASSERT_FALSE(testTree.empty());
}

// Multiple inserts, 
// insert several elements, check size and that iterating gives sorted order
TEST(multiple_inserts_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_EQUAL(testTree.size(), 5u);
    ASSERT_EQUAL(testTree.height(), 3u);
    ASSERT_FALSE(testTree.empty());

    auto it = testTree.begin();
    int previous = *it;
    ++it;
    while (it != testTree.end()) {
        ASSERT_TRUE(previous < *it);
        previous = *it;
        ++it;
    }
}

// Find existing and missing, 
// find something inserted and something that wasnt
TEST(existing_and_missing_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_NOT_EQUAL(testTree.find(5), testTree.end());
    ASSERT_NOT_EQUAL(testTree.find(1), testTree.end());
    ASSERT_NOT_EQUAL(testTree.find(10), testTree.end());
    ASSERT_NOT_EQUAL(testTree.find(2), testTree.end());
    ASSERT_NOT_EQUAL(testTree.find(9), testTree.end());

    ASSERT_EQUAL(testTree.find(11), testTree.end());
}

// Height shape, 
// insert in a known order, verify height
TEST(height_shape_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(1);
    testTree.insert(2);
    testTree.insert(3);
    testTree.insert(4);
    testTree.insert(5);

    ASSERT_EQUAL(testTree.size(), 5u);
    ASSERT_EQUAL(testTree.height(), 5u);
}

// Sorting invariant valid, 
// build a normal tree, check it passes
TEST(sorting_invariant_valid_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_TRUE(testTree.check_sorting_invariant());
}

// Sorting invariant broken, 
// insert nodes, corrupt one with *b.begin() = bad_value, check it fails
TEST(sorting_invariant_broken_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    *testTree.begin() = 100;
    ASSERT_FALSE(testTree.check_sorting_invariant());
}

// Copy constructor, 
// copy a tree, verify both have same elements independently
TEST(copy_constructor_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    BinarySearchTree<int> testTreeCopy = testTree;

    ASSERT_EQUAL(testTree.size(), testTreeCopy.size());
    ASSERT_EQUAL(testTree.height(), testTreeCopy.height());

    auto it = testTree.begin();
    auto itC = testTreeCopy.begin();

    while (it != testTree.end()) {
        ASSERT_TRUE(*itC == *it);
        ++it;
        ++itC;
    }
}

// Destructor, 
// just make sure things don't crash/leak
TEST(destructor_test) {
    {
        BinarySearchTree<int> testTree;
        testTree.insert(5);
        testTree.insert(1);
        testTree.insert(10);
        testTree.insert(2);
        testTree.insert(9);
    }
}

// min and max, 
// check they return the correct values on a non-empty tree
TEST(min_and_max_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_EQUAL(*testTree.min_element(), 1);
    ASSERT_EQUAL(*testTree.max_element(), 10);
}

// min_greater_than, 
// finds the smallest element greater than a given value
TEST(min_greater_than_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_EQUAL(*testTree.min_greater_than(5), 9);
}

// check_sorting_invariant,
// on a single node, should always be valid
TEST(check_sorting_invariant_one_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);

    ASSERT_TRUE(testTree.check_sorting_invariant());
}

// min_greater_than no element greater,
// call it with a value larger than everything in the tree, should return end()
TEST(min_greater_than_no_element_greater_test) {
    BinarySearchTree<int> testTree;
    testTree.insert(5);
    testTree.insert(1);
    testTree.insert(10);
    testTree.insert(2);
    testTree.insert(9);

    ASSERT_EQUAL(testTree.min_greater_than(10),testTree.end());
}

TEST_MAIN()