#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <stack>
#include <stdexcept>
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

		private:
		/**
		 * @brief Finds if a value exists within the tree.
		 * @param value The value to search for
		 * @return A pointer to the node containing the value. It is null if the value isn't found.
		 * */
		std::shared_ptr<detail::Node> findValue(double value) {
			// Find the target node by following the binary properties.
			auto current_node = root;
			// Search until a value is found, or the search moves past
			// a leaf (meaning it was unsuccessful).
			while (current_node && current_node->key != value) {
				// Decide which way to go on the tree. Ties technically go to the right,
				// but won't actually come up, since that would exit the loop.
				if (value < current_node->key) {
					current_node = current_node->left;
				} else {
					current_node = current_node->right;
				}
			}
			// This node is either pointing at a node with a value or nullptr.
			// Either way, go ahead and return it.
			return current_node;
		}

		/**
		 * @brief A helper method to replace a node with one of its childer.
		 * 
		 * This method takes two nodes and swaps the one out for the other,
		 * including the parent.
		 * @param old_node The old node to replace.
		 * @param new_node The child node to put where the old node goes.
		 * */
		void transplant(std::shared_ptr<detail::Node> old_node, std::shared_ptr<detail::Node> new_node) {
			// If the old node is the root, this is an easy swap.
			if (old_node == root) {
				root = new_node;
			} else if (old_node == old_node->parent->left) {
				old_node->parent->left = new_node;
			} else {
				old_node->parent->right = new_node;
			}
			if (new_node) {
				new_node->parent = old_node->parent;
			}
		}

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
			new_node->left = nullptr;
			new_node->right = nullptr;
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
			// Start at the root and walk right until there isn't a
			// new right to follow.
			auto current_node = root;
			// There is a chance the tree is empty. If so, current_node
			// will be null.
			if (!current_node) {
				throw std::out_of_range("Binary tree is empty");
			}
			// Otherwise, look to see if there is a child or not.
			while (current_node->right) {
				current_node = current_node->right;
			}
			// The loop exits when there is no right child, meaning the
			// current node is the maximum.
			return current_node->key;
		}

		/**
		 * @brief Find the minimum value stored in the tree.
		 * @return The minimum value.
		 * @throw std::out_of_range Thrown if the tree is empty.
		 * */
		double min() {
			// Start at the root and walk left until there isn't a
			// new left to follow.
			auto current_node = root;
			// There is a chance the tree is empty. If so, current_node
			// will be null.
			if (!current_node) {
				throw std::out_of_range("Binary tree is empty");
			}
			// Otherwise, look to see if there is a child or not.
			while (current_node->left) {
				current_node = current_node->left;
			}
			// The loop exits when there is no left child, meaning the
			// current node is the minimum.
			return current_node->key;
		}

		/**
		 * @brief Find the previous element in the tree, given a value.
		 * @param value The value to find the predecessor of.
		 * @return The predecessor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has no predecessor.
		 * */
		double predecessor(double value) {
			// See if the value is even in the tree. Throw an error if not.
			auto target_node = findValue(value);
			if (!target_node) {
				throw std::out_of_range("Value not found");
			}
			auto predecessor_node = target_node->left;
			// If there is a left child, the successor is the maximum of the left
			// subtree, so keep going right.
			if (predecessor_node) {
				// Keep following the path to the maximum of this subtree.
				while (predecessor_node->right) {
					predecessor_node = predecessor_node->right;
				}
				// When the loop exits, there will be no left child, so the current
				// node is the predecessor
				return predecessor_node->key;
			}
			// Otherwise, the predecessor is the first ancestor that has this chain on the
			// right child path.
			auto parent_node = target_node->parent;
			while (parent_node && target_node == parent_node->left) {
				// Keep working up the tree
				target_node = parent_node;
				parent_node = parent_node->parent;
			}
			// This breaks in two cases - either the parent is not null, so the parent
			// is the successor, or it is. If it is, this means the given value was
			// actually the max. Throw an error then.
			if (!parent_node) {
				throw std::out_of_range("Value has no successor, as it is the maximum value of the tree.");
			}
			return parent_node->key;
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
			// First, see if the value even exists. If not, go ahead and just return,
			// since the work is done.
			std::shared_ptr<detail::Node> target_node = findValue(value);
			// If this is null, then the value doesn't exist and our work is done.
			if (!target_node) {
				return;
			}
			// If the node only has one child, replace it with that child.
			if (!target_node->left) {
				transplant(target_node, target_node->right);
			} else if (!target_node->right) {
				auto left = target_node->left;
				transplant(target_node, left);
			} else {
				// If the node has two children, its successor will take its
				// place. Since it has two children, the successor is certain
				// to be a descendant.
				auto successor_node = findValue(successor(target_node->key));
				// If the successor is not the immediate child, splice it out
				// of its current location in the tree.
				if (successor_node->parent != target_node) {
					// By definition of being a successor, this node only has
					// a right child (if any).
					transplant(successor_node, successor_node->right);
					// Move the children of the target node over to the new one
					successor_node->right = target_node->right;
					successor_node->right->parent = successor_node;
				}
				// Drop the successor in to where the target node currently resides.
				transplant(target_node, successor_node);
				// Replace its left child too
				successor_node->left = target_node->left;
				successor_node->left->parent = successor_node;
			}
		}

		/**
		 * @brief Find the next element in the tree, given a value.
		 * @param value The value to find the successor of.
		 * @return The successor of the provided value.
		 * @throw std::out_of_range Thrown if the value is not found or has no successor.
		 * */
		double successor(double value) {
			// See if the value is even in the tree. Throw an error if not
			auto target_node = findValue(value);
			if (!target_node) {
				throw std::out_of_range("Value not found");
			}
			auto successor_node = target_node->right;
			// If there is a right child, the successor is the minimum of the right
			// subtree, so keep going left.
			if (successor_node) {
				// Keep following the path to the minimum of this subtree.
				while (successor_node->left) {
					successor_node = successor_node->left;
				}
				// When the loop exits, there will be no left child, so the current
				// node is the successor
				return successor_node->key;
			}
			// Otherwise, the successor is the first ancestor that has this chain on the
			// left child path.
			auto parent_node = target_node->parent;
			while (parent_node && target_node == parent_node->right) {
				// Keep working up the tree
				target_node = parent_node;
				parent_node = parent_node->parent;
			}
			// This breaks in two cases - either the parent is not null, so the parent
			// is the successor, or it is. If it is, this means the given value was
			// actually the max. Throw an error then.
			if (!parent_node) {
				throw std::out_of_range("Value has no successor, as it is the maximum value of the tree.");
			}
			return parent_node->key;
		}
	};

} // namespace BinaryTree

#endif // BINARY_TREE_H