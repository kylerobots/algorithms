#include "binary_tree.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <vector>

/**
 * @brief Create a tree filled with random numbers.
 * 
 * This assists the test methods by creating a binary
 * tree. It also fills the tree with select numbers.
 * While this could be random, it uses a fixed seed for
 * repeatability.
 * @return A pair containing the vector of numbers and a shared pointer. The
 * vector is in sorted order.
 * to the tree.
 * */
std::pair<std::vector<double>, std::shared_ptr<BinaryTree::BinaryTree>> createTree() {
	// Use a random number generator for the insert
	// values, but give it a fixed seed for consistency.
	std::mt19937 engine(42);
	std::uniform_real_distribution<double> distribution(-100.0, 100.0);
	// Create a pair to return both values.
	auto results = std::make_pair(std::vector<double>(), std::make_shared<BinaryTree::BinaryTree>());
	// Add a bunch of numbers into the tree.
	for (size_t i = 0; i < 100; ++i) {
		double number = distribution(engine);
		results.first.push_back(number);
		results.second->insert(number);
	}
	// Sort the vector
	std::sort(results.first.begin(), results.first.end());
	return results;
}

/**
 * @brief Test traversal (and insertion).
 * 
 * This verifies that the tree can insert numbers properly and
 * traverse the tree correctly. If done right, it will return
 * an ordered list. I don't know how to seperate this function
 * without using friend classes to directly access the nodes.
 * */
TEST(BinaryTree, Insertion) {
	auto numbers_and_tree = createTree();
	// Get the numbers from a tree walk.
	std::vector<double> output = numbers_and_tree.second->getSortedValues();
	EXPECT_EQ(numbers_and_tree.first, output);
}

/**
 * @brief Test the ability to find the minimum and maximum values.
 * */
TEST(BinaryTree, MinMax) {
	auto numbers_and_tree = createTree();
	double min = numbers_and_tree.second->min();
	double max = numbers_and_tree.second->max();
	// Since the numbers are sorted, just compare to the first and last element.
	EXPECT_EQ(numbers_and_tree.first.front(), min);
	EXPECT_EQ(numbers_and_tree.first.back(), max);
}

/**
 * @brief Test deletion of a key (and search).
 * 
 * This deletes a number from the tree and then checks that it
 * was actually deleted by comparing with the traversal output.
 * */
TEST(BinaryTree, Deletion) {
	auto numbers_and_tree = createTree();
	auto expected_output = numbers_and_tree.first;
	// Delete a few times to explore the different branches in the
	// algorithm
	std::vector<size_t> indices {5, 10, 45, 42, 50, 32, 26, 43, 89, 90, 0, 14};
	for (size_t i = 0; i < indices.size(); ++i) {
		numbers_and_tree.second->remove(expected_output[i]);
		expected_output.erase(expected_output.begin() + i);
	}
	// Make sure the value was deleted
	auto output = numbers_and_tree.second->getSortedValues();
	EXPECT_EQ(expected_output, output);
}

/**
 * @brief Test successor and predecessor of a value.
 * 
 * This checks that the tree can find the predecessor and successor
 * of a given value.
 * */
TEST(BinaryTree, SuccessorPredecessor) {
	auto numbers_and_tree = createTree();
	// Pick an index to use.
	size_t index = 20;
	double predecessor = numbers_and_tree.second->predecessor(numbers_and_tree.first[index]);
	double successor = numbers_and_tree.second->successor(numbers_and_tree.first[index]);
	EXPECT_EQ(numbers_and_tree.first[index - 1], predecessor);
	EXPECT_EQ(numbers_and_tree.first[index + 1], successor);
	// Check that it handles errors as well. Try when there is no predecessor/successor or
	// the value isn't found. Exploit the knowledge of the range of possible inputs.
	EXPECT_THROW(numbers_and_tree.second->predecessor(-150.0), std::out_of_range);
	EXPECT_THROW(numbers_and_tree.second->successor(-150.0), std::out_of_range);
	EXPECT_THROW(numbers_and_tree.second->predecessor(numbers_and_tree.first.front()), std::out_of_range);
	EXPECT_THROW(numbers_and_tree.second->successor(numbers_and_tree.first.back()), std::out_of_range);
}

/**
 * @brief Check that an empty tree is handled correctly.
 * 
 * Namely, ensure that:
 * 
 * - The sorted values is an empty vector
 * - Deletion ends without error
 * - Predecessor, successor, min, and max all throw errors
 * */
TEST(BinaryTree, Empty) {
	BinaryTree::BinaryTree tree;
	EXPECT_NO_FATAL_FAILURE(tree.remove(0.0));
	EXPECT_THROW(tree.max(), std::out_of_range);
	EXPECT_THROW(tree.min(), std::out_of_range);
	EXPECT_THROW(tree.successor(0.0), std::out_of_range);
	EXPECT_THROW(tree.predecessor(0.0), std::out_of_range);
}