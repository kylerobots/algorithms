#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <stack>
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
	 * @brief This is a namespace with some under the hood functions.
	 * 
	 * These should generally not be called by the user unless you are
	 * very sure what you are doing and have a very good reason for
	 * doing so.
	 * */
	namespace detail {
		/**
		 * @param A struct for the representation of nodes in a binary tree.
		 * */
		struct Node {
			/// The value stored in this node.
			double key;
			/// The left child of this node.
			std::shared_ptr<Node> left;
			/// The parent of this node.
			std::shared_ptr<Node> parent;
			/// The right child of this node.
			std::shared_ptr<Node> right;
		};
	} // namespace detail

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
		protected:
		/// The root of the tree.
		std::shared_ptr<detail::Node> root;

		public:
		/**
		 * @brief Construct an empty tree.
		 * */
		BinaryTree() :
				root(nullptr) {
		}

		/**
		 * @brief Walk through the tree and get all values in sorted order.
		 * @return A vector containing all the values stored in the tree, sorted
		 * from smallest to largest.
		 * */
		std::vector<double> getSortedValues() {
			std::vector<double> output;
			// Use a stack to store which nodes are halfway through processing
			std::stack<std::shared_ptr<detail::Node>> stack;
			auto current_node = root;
			while (current_node || !stack.empty()) {
				// Follow down the left path of the nodes.
				while (current_node) {
					// If this node exists, try it's left child first
					stack.push(current_node);
					current_node = current_node->left;
				}
				// The current node is null at the top of the stacks left child.
				current_node = stack.top();
				stack.pop();
				// Place this value
				output.push_back(current_node->key);
				// Since left is completely covered, follow right.
				current_node = current_node->right;
			}
			return output;
		}

		/**
		 * @brief Insert a single number into the tree.
		 * @param value The value to insert into the tree.
		 * */
		void insert(double value) {
			std::shared_ptr<detail::Node> parent_node(nullptr);
			auto target_node = root;
			// Walk through the tree to find a leaf based on the
			// order condition.
			while (target_node) {
				// Move to the next node down, since this isn't a leaf.
				parent_node = target_node;
				if (value < target_node->key) {
					target_node = target_node->left;
				} else {
					target_node = target_node->right;
				}
			}
			// target_node is now pointing to nullptr and parent_node is the future
			// parent of the new value.
			// Create a node for the new value.
			auto new_node = std::make_shared<detail::Node>(detail::Node());
			new_node->key = value;
			new_node->parent = parent_node;
			// If parent_node is nullptr, then the tree was empty, so this new value is the root.
			// Otherwise, figure out if the new node should be a left or right node.
			if (!parent_node) {
				root = new_node;
			} else if (value < parent_node->key) {
				parent_node->left = new_node;
			} else {
				parent_node->right = new_node;
			}
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