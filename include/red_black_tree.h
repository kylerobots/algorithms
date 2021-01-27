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
	 * @brief This is a namespace with some under the hood functions.
	 * 
	 * These should generally not be called by the user unless you are
	 * very sure what you are doing and have a very good reason for
	 * doing so.
	 * */
	namespace detail {
		/**
		 * @brief The colors to use for the @ref RedBlackTree class.
		 * */
		enum class Color {
			RED,
			BLACK
		};

		/**
		 * @brief A struct for the representation of nodes in the red black
		 * tree.
		 * */
		struct RedBlackNode {
			/// The value stored in this node.
			double key;
			/// The left child of this node.
			std::shared_ptr<RedBlackNode> left;
			/// The parent of this node.
			std::shared_ptr<RedBlackNode> parent;
			// The right child of this node.
			std::shared_ptr<RedBlackNode> right;
			// The color of this node.
			Color color;
		}
	} // namespace detail

	/**
	 * @brief A red-black tree.
	 * 
	 * This tree provides an alternative to @ref BinaryTree by adding
	 * color properties to help keep the tree balanced. See the book
	 * for full details, but all nodes are either red or black and
	 * certain relationships between them must hold.
	 * */
	class RedBlackTree {
		protected:
		/// The root of the tree.
		std::shared_ptr<detail::RedBlackNode> root;

		private:
		/**
		 * @brief Ensures the tree adheres to the color requirements after
		 * an insertion.
		 * 
		 * This goes through and makes sure that no two successive nodes are
		 * both red. If they are, it applies several operations:
		 * 1. If the parent and parent's sibling are both red, it changes
		 * both of those and their parent colors. This keeps all sets of
		 * child nodes the same color, which is required because of the
		 * black height constraint.
		 * 2. If the uncle is a different color from the parent, and the 
		 * parent and child are opposite sides (e.g. the parent is a left
		 * child while the node is a right child), rotate the nodes so
		 * they both are the same direction. Then proceed to case 3.
		 * 3. If the uncle is a different color from the parent, and the
		 * parent and child are the same sides (e.g. the parent is a left
		 * child and the node is a left child), rotate the nodes so what
		 * was once the grandparent is now the uncle, and the new node is
		 * where the parent was. Along with some color changes, this
		 * restores the tree properties, since it basically adds a red
		 * node on the uncle's side, which doesn't violate anything.
		 * 
		 * These steps then continue up the tree until no red node has a red
		 * parent.
		 * @param node The node that was just inserted.
		 * */
		void insertFixup(std::shared_ptr<detail::RedBlackNode> node) {
			while (node->parent && node->parent->color == detail::Color::RED) {
				if (node->parent == node->parent->parent->left) {
					auto uncle = node->parent->parent->right;
					if (uncle->color == detail::Color::RED) {
						// Since the parent and uncle are both red, just
						// swap the color with their parent, which restores
						// the no two reds in a row property and maintains
						// the black height property.
						node->parent->color = detail::Color::BLACK;
						uncle->color = detail::Color::BLACK;
						node->parent->parent->color = detail::Color::RED;
						// Move up the tree and keep checking. We already know
						// that from the parents on down the tree is good.
						node = node->parent->parent;
					} else {
						if (node == node->parent->right) {
							// If the parent is a left child but the node is a right
							// child, rotate them so the node is in the new parent
							// spot with its former parent as its left child. This
							// prepares for step 3.
							node = node->parent;
							leftRotate(node);
						}
					}
					// The node is a red, left child. Its parent is a red, left
					// child, its grandparent is black, and its uncle is black.
					// Therefore, perform a right rotation to move the parent
					// into the grandparent spot and the grandparent into the
					// uncle spot. Swap their colors as well. This has the effect
					// of introducting a red node on the right part of the tree
					// (which doesn't violate anything, since the grandparent and
					// uncle were black). It also removes a red node from this side
					// of the tree, which restores the 2-red constraint. Since only
					// red nodes were introduced or removed, the black height is
					// unchanged.
					node->parent->color = detail::Color::BLACK;
					node->parent->parent->color = detail::Color::RED;
					rightRotate(node->parent->parent);
				} else {
					// This is just the same process as above but with left and
					// right mirrored.
					auto uncle = node->parent->parent->left;
					if (uncle->color == detail::Color::RED) {
						node->parent->color = detail::Color::BLACK;
						uncle->color = detail::Color::BLACK;
						node->parent->parent->color = detail::Color::RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							rightRotate(node);
						}
						node->parent->color = detail::Color::BLACK;
						node->parent->parent->color = detail::Color::RED;
						leftRotate(node->parent->parent);
					}
				}
			}
			// Lastly, there is a chance the root might be turned red. If so,
			// just change it back, since all nodes below it will already be
			// correct and this by definition maintains the black height.
			root->color = detail::Color::BLACK;
		}

		/**
		 * @brief Perform a left rotation on a node.
		 * 
		 * In a left rotation, a node's right child is made its parent and
		 * it is placed as the left child of this new parent. This assists
		 * in cleaning up the tree. Their other children are
		 * */
		void leftRotate(std::shared_ptr<detail::RedBlackNode> node) {
			auto right = node->right;
			node->right = right->left;
		}

		/**
		 * @brief
		 * */
		void rightRotate(std::shared_ptr<detail::RedBlackNode> node) {
		}

		public:
		/**
		 * @brief Construct an empty tree.
		 * */
		RedBlackTree() :
				root(nullptr) {
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
			// First, find where this new node should go by walking
			// through the tree.
			std::shared_ptr<detail::RedBlackNode> parent_node(nullptr);
			auto target_node = root;
			// Continue until it has moved past a leaf (so is pointing
			// at null)
			while (target_node) {
				// Move to the next node down, since this isn't a leaf.
				parent_node = target_node;
				if (value < target_node->key) {
					target_node = target_node->left;
				} else {
					target_node = target_node->right;
				}
			}
			// target_node is now pointing to nullptr and parent_node is the
			// future parent of the new value. Create the new node.
			auto new_node = std::make_shared<detail::RedBlackNode>(detail::RedBlackNode());
			new_node->key = value;
			new_node->parent = parent_node;
			new_node->left = nullptr;
			new_node->right = nullptr;
			new_node->color = detail::Color::RED;
			// If the parent is nullptr, then the tree was empty. If so, this new
			// value is the root. Otherwise, it should be a left or right
			// child.
			if (!parent_node) {
				root = new_node;
			} else if (value < parent_node->key) {
				parent_node->left = new_node;
			} else {
				parent_node->right = new_node;
			}
			// Lastly, fix up the tree to adhere to color properties.
			insertFixup(new_node);
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
