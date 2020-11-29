#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

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
	 * @brief A red-black tree.
	 * 
	 * This tree provides an alternative to @ref BinaryTree by adding
	 * color properties to help keep the tree balanced. See the book
	 * for full details, but all nodes are either red or black and
	 * certain relationships between them must hold.
	 * */
	class RedBlackTree {
		public:
		/**
		 * @brief Construct an empty tree.
		 * */
		RedBlackTree() {
		}

		/**
		 * @brief Walk through the tree and get all values in sorted order.
		 * @return A vector containing all the values stored in the tree,
		 * sorted from smallest to largest.
		 * */
		std::vector<double> getSortedValues() {
			std::vector<double> output;
			return output;
		}

		/**
		 * @brief Insert a value into the tree.
		 * 
		 * This inserts the value, then performs a cleanup to ensure color
		 * properties are upheld.
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
			return 0.0;
		}

		/**
		 * @brief Find the minimum value stored in the tree.
		 * @return The minimum value.
		 * @throw std::out_of_range Thrown if the tree is empty.
		 * */
		double min() {
			return 0.0;
		}

		/**
		 * @brief Find the previous element in the tree, given a value.
		 * @param value The value to find the predecessor of.
		 * @return The predecessor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has
		 * no predecessor.
		 * */
		double predecessor(double value) {
			return 0.0;
		}

		/**
		 * @brief Delete a number from the tree.
		 * @param value The value to delete from the tree.
		 * */
		void remove(double value) {
		}

		/**
		 * @brief Find the next element in the tree, given a value.
		 * @param value The value to find the successor of.
		 * @return The successor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has
		 * no successor.
		 * */
		double successor(double value) {
			return 0.0;
		}
	};

} // namespace BinaryTree

#endif // RED_BLACK_TREE_H
