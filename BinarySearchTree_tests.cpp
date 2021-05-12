// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    
    tree.insert(1);
    ASSERT_TRUE(!tree.empty());
}

TEST(test_height1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    ASSERT_TRUE(tree.height() == 3);
}

TEST(test_height2) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    ASSERT_TRUE(tree.height() == 1u);
}

TEST(test_height3) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    ASSERT_TRUE(tree.height() == 7);
}

TEST(test_height4) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.height() == 0);
}

TEST(test_size1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    ASSERT_TRUE(tree.size() == 7);
}

TEST(test_size2) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.size() == 0u);
}

TEST(test_max_element1) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    
    ASSERT_TRUE(*tree.max_element() == 7);
}

TEST(test_max_element2) {
    BinarySearchTree<int> tree;
    tree.insert(21);
    
    ASSERT_TRUE(*tree.max_element() == 21);
}

TEST(test_max_element3) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator end = tree.end();

    ASSERT_TRUE(tree.max_element() == end);
}

TEST(test_min_element1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    ASSERT_TRUE(*tree.min_element() == 1);
}

TEST(test_min_element2) {
    BinarySearchTree<int> tree;
    tree.insert(21);
    
    ASSERT_TRUE(*tree.min_element() == 21);
}

TEST(test_min_element3) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator end = tree.end();

    ASSERT_TRUE(tree.min_element() == end);
}


TEST(test_find1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    BinarySearchTree<int>::Iterator find = tree.find(5);
    ASSERT_TRUE(*find == 5);
}

TEST(test_find2) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    BinarySearchTree<int>::Iterator end = tree.end();
    ASSERT_TRUE(tree.find(9) == end);
}

TEST(test_find3) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator end = tree.end();
    ASSERT_TRUE(tree.find(21) == end);
    
}

TEST(test_min_greater_than1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(2);
    ASSERT_TRUE(3 == *min_greater);
    ASSERT_EQUAL(*tree.min_greater_than(5), 6);
    ASSERT_EQUAL(*tree.min_greater_than(6), 7);
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
}

TEST(test_min_greater_than2) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(2);
    BinarySearchTree<int>::Iterator end = tree.end();
    ASSERT_TRUE(min_greater == end);
    tree.insert(5);
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
    *tree.begin() = 3;
    ASSERT_EQUAL(tree.min_greater_than(5), end);
}

TEST(test_min_greater_than3) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    
    BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(5);
    ASSERT_FALSE(6 != *min_greater);
}

TEST(test_min_greater_right) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(10);
    
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
    ASSERT_EQUAL(*tree.min_greater_than(5), 7);
    ASSERT_EQUAL(*tree.min_greater_than(9), 10);
}

TEST(test_min_greater_left) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    
    ASSERT_EQUAL(*tree.min_greater_than(0), 1);
    ASSERT_EQUAL(*tree.min_greater_than(3), 5);
    ASSERT_EQUAL(*tree.min_greater_than(1), 2);
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
}

TEST(test_sorting_invariant1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    
    ASSERT_TRUE(tree.check_sorting_invariant() == true);
}

TEST(test_sorting_invariant2) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    *tree.begin() = 6;
    ASSERT_TRUE(tree.check_sorting_invariant() == false);
}

TEST(test_sorting_invariant3) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant() == true);
    
    tree.insert(3);
    ASSERT_TRUE(tree.check_sorting_invariant() == true);
}

TEST(test_sorting_invariant_right) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(8);
    tree.insert(11);
    ASSERT_TRUE(tree.check_sorting_invariant() == true);
    *tree.begin() = 10;
    ASSERT_TRUE(tree.check_sorting_invariant() == false);
}

TEST(test_sorting_invariant_left) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    ASSERT_TRUE(tree.check_sorting_invariant() == true);
    *tree.begin() = 30;
    ASSERT_TRUE(tree.check_sorting_invariant() == false);
}

TEST(test_traverse_inorder1) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(6);
    tree.insert(3);
    tree.insert(5);
    tree.insert(2);
    
    std::ostringstream order;
    tree.traverse_inorder(order);
    
    ASSERT_TRUE(order.str() == "2 3 4 5 6 ");
}

TEST(test_traverse_inorder2) {
    BinarySearchTree<int> tree;
    
    std::ostringstream order;
    tree.traverse_inorder(order);
    
    ASSERT_TRUE(order.str() == "");
}

TEST(test_traverse_preorder1) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(9);
    tree.insert(5);

    std::ostringstream order;
    tree.traverse_preorder(order);

    ASSERT_TRUE(order.str() == "7 5 9 ");
}

TEST(test_traverse_preorder2) {
    BinarySearchTree<int> tree;
    
    std::ostringstream order;
    tree.traverse_preorder(order);
    
    ASSERT_TRUE(order.str() == "");
}

TEST(test_assignment1) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(9);
    tree.insert(4);
    tree.insert(8);
    
    BinarySearchTree<int> other;
    other = tree;
    
    ASSERT_TRUE(other.size() == tree.size());
}

TEST(test_assignment2) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    
    BinarySearchTree<int> other;
    other.insert(1);
    other.insert(2);
    other = tree;
    
    ASSERT_TRUE(other.height() == tree.height());
}

TEST(test_assignment3) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> other;
    other = tree;
    ASSERT_TRUE(other.size() == tree.size());
    ASSERT_TRUE(other.height() == tree.height());
}

TEST(test_increment) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(9);
    tree.insert(4);
    tree.insert(8);
    
    BinarySearchTree<int>::Iterator beg = tree.begin();
    ++beg;
    ++beg;
    ASSERT_TRUE(*beg == 8);
    
    beg++;
    ASSERT_TRUE(*beg == 9);
}

TEST_MAIN()
