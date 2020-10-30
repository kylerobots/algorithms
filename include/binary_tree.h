#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>

/**
 * @brief Namespace for a collection of binary tree styles.
 * 
 * This includes:
 * - Plain
 * - Red-Black
 * */
namespace BinaryTree {
	/**
	 * @brief A plain binary tree.
	 * 
	 * This tree allows for the following functions:
	 * - Insertion
	 * - Deletion
	 * - Search
	 * - Finding the minimum and maximum values
	 * - Finding the successor and predecessor of a value
	 * */
	class BinaryTree {
		public:
		/**
		 * @brief Construct an empty tree.
		 * */
		BinaryTree() {
		}

		/**
		 * @brief Walk through the tree and get all values in sorted order.
		 * @return A vector containing all the values stored in the tree, sorted
		 * from smallest to largest.
		 * */
		std::vector<double> getSortedValues() {
			std::vector<double> output;
			return output;
		}

		/**
		 * @brief Insert a single number into the tree.
		 * @param value The value to insert into the tree.
		 * */
		void insert(double value) {
		}

		/**
		 * @brief Find the maximum value stored in the tree.
		 * @return The maximum value.
		 * @throw std::out_of_range Thrown if the tree is empty.
		 * */
		double max() {
			return 0;
		}

		/**
		 * @brief Find the minimum value stored in the tree.
		 * @return The minimum value.
		 * @throw std::out_of_range Thrown if the tree is empty.
		 * */
		double min() {
			return 0;
		}

		/**
		 * @brief Find the previous element in the tree, given a value.
		 * @param Value The value to find the predecessor of.
		 * @return The predecessor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has no predecessor.
		 * */
		double predecessor(double value) {
			return 0;
		}

		/**
		 * @brief Delete a number from the tree.
		 * 
		 * This will delete the first instance of the number that the tree finds.
		 * If the number does not exist, it will end execution anyways without
		 * error.
		 * @param value The value to delete from the tree.
		 * */
		void remove(double value) {
		}

		/**
		 * @brief Find the next element in the tree, given a value.
		 * @param Value The value to find the successor of.
		 * @return The successor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has no successor.
		 * */
		double successor(double value) {
			return 0;
		}
	};

} // namespace BinaryTree

#endif // BINARY_TREE_H