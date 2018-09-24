#pragma once

#include <iostream>
#include <queue>
#include <list>

template<typename T>
class Node {
public:
	T value;
	Node* left;
	Node* right;

	Node() :left(nullptr), right(nullptr) {}

	Node(T value) {
		this->value = value;
		right = nullptr;
		left = nullptr;
	}
};

template<typename T>
class BinaryTree {
public:
	BinaryTree() noexcept :_root(nullptr) {}

	void add(T value) {
		_root = addRecursive(_root, value);
	}

	bool containsNode(T value) {
		//return containsNodeRecursive(_root, value);
		return containsNodeIterative(_root, value);
	}
	//Depth-First Search
	// goes deep as much as possible in every child before exploring the next sibling
	void traverseInOrder() {
		std::cout << "in order traverse : ";
		traverseInOrder(_root);
		std::cout <<  "\n";
	}

	void traversePreOrder() {
		std::cout << "pre order traverse : ";
		traversePreOrder(_root);
		std::cout << "\n";
	}
	void traversePostOrder() {
		std::cout << "pre order traverse : ";
		traversePostOrder(_root);
		std::cout << "\n";
	}
	
	//Breadth-First Search
	void traverseLevelOrder() {
		std::cout << "level order traverse : ";
		if (_root == nullptr) {
			return;
		}
		traverseLevelOrder(_root);
	
	}

	void remove(T value) {
		removeRecursive(_root, value);
	}
	
private:

	void traverseLevelOrder(Node<T>* node) {
		std::list<Node<T>*> nodes;
		nodes.push_back(_root);

		while (!nodes.empty()) {
			auto node = nodes.front();
			nodes.pop_front();

			std::cout << node->value << " ";

			if (node->left != nullptr) {
				nodes.push_back(node->left);
			}

			if (node->right != nullptr) {
				nodes.push_back(node->right);
			}
		}
	}

	void traverseInOrder(Node<T>* node) {
		if (node != nullptr) {
			traverseInOrder(node->left);
			std::cout << node->value << " ";
			traverseInOrder(node->right);
		}
	}
	
	void traversePreOrder(Node<T>* node) {
		if (node != nullptr) {
			std::cout << node->value <<" ";
			traversePreOrder(node->left);
			traversePreOrder(node->right);
		}
	}
	void traversePostOrder(Node<T>* node) {
		if (node != nullptr) {
			traversePostOrder(node->left);
			traversePostOrder(node->right);
			std::cout << node->value << " ";
		}
	}

	Node<T>* addRecursive(Node<T>* current, T value) {
		if (current == nullptr) {
			return new Node<T>(value);
		}

		if (value < current->value) {
			current->left = addRecursive(current->left, value);
		}
		else if (value > current->value) {
			current->right = addRecursive(current->right, value);
		}
		else {
			// value already exists
			return current;
		}

		return current;
	}
	
	bool containsNodeRecursive(Node<T>* current, T value) {
		if (current == nullptr) {
			return false;
		}
		if (value == current->value) {
			return true;
		}
		return value < current->value
			? containsNodeRecursive(current->left, value)
			: containsNodeRecursive(current->right, value);
	}
	/*
	Node x = root;
        while (x != null) {
            int res = key.compareTo(x.key);
            if      (res < 0) x = x.left;
            else if (res > 0) x = x.right;
            else return x.val;
        }
        return null;
	*/
		

	bool containsNodeIterative(Node<T>* current, T value) {
		Node<T>* currentNode = current;
		while (currentNode !=  nullptr)
		{
			if (value == currentNode->value) {
				return true;
			}
			else if (value > currentNode->value)
			{
				currentNode = currentNode->right;
			}
			else
			{
				currentNode = currentNode->left;
			}
		}
		return false;
	}


	Node<T>* removeRecursive(Node<T>* current, T value) {
		if (current == nullptr) {
			return nullptr;
		}

		if (value == current->value) {
			// Case 1: no children
			if (current->left == nullptr && current->right == nullptr) {
				return nullptr;
			}

			// Case 2: only 1 child
			if (current->right == nullptr) {
				return current->left;
			}

			if (current->left == nullptr) {
				return current->right;
			}

			// Case 3: 2 children
			int smallestValue = findSmallestValue(current->right);
			current->value = smallestValue;
			current->right = removeRecursive(current->right, smallestValue);
			return current;
		}

		if (value < current->value) {
			current->left = removeRecursive(current->left, value);
			return current;
		}

		current->right = removeRecursive(current->right, value);
		return current;
	}

	T findSmallestValue(Node<T>* root) {
		return root->left == nullptr ? root->value : findSmallestValue(root->left);
	}


	

private:
	Node<T>* _root;

};



void TestBinaryTree()
{
	BinaryTree<int> bt;

	bt.add(6);
	bt.add(4);
	bt.add(8);
	bt.add(3);
	bt.add(5);
	bt.add(7);
	bt.add(9);
	bt.add(2);

	bt.remove(2);

	bt.traverseInOrder();
	bt.traversePreOrder();
	bt.traversePostOrder();
	bt.traverseLevelOrder();
	if (bt.containsNode(15) == false){
		std::cout << "value not expected" << std::endl;
	}
	
	if (bt.containsNode(8) == true) {
		std::cout << "value expected" << std::endl;
	}
}