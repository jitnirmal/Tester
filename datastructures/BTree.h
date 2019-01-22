#pragma once

#include <iostream>
#include <queue>
#include <list>

template<typename T>
class Node {
public:
	T value;
	Node* leftChild;
	Node* rightChild;

	Node() :leftChild(nullptr), rightChild(nullptr) {}

	Node(T value) {
		this->value = value;
		rightChild = nullptr;
		leftChild = nullptr;
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

	void traverseLevelOrder(Node<T>* Node) {
		std::list<Node<T>*> nodes;
		nodes.push_back(_root);

		while (!nodes.empty()) {
			auto Node = nodes.front();
			nodes.pop_front();

			std::cout << Node->value << " ";

			if (Node->leftChild != nullptr) {
				nodes.push_back(Node->leftChild);
			}

			if (Node->rightChild != nullptr) {
				nodes.push_back(Node->rightChild);
			}
		}
	}

	void traverseInOrder(Node<T>* Node) {
		if (Node != nullptr) {
			traverseInOrder(Node->leftChild);
			std::cout << Node->value << " ";
			traverseInOrder(Node->rightChild);
		}
	}
	
	void traversePreOrder(Node<T>* Node) {
		if (Node != nullptr) {
			std::cout << Node->value <<" ";
			traversePreOrder(Node->leftChild);
			traversePreOrder(Node->rightChild);
		}
	}
	void traversePostOrder(Node<T>* Node) {
		if (Node != nullptr) {
			traversePostOrder(Node->leftChild);
			traversePostOrder(Node->rightChild);
			std::cout << Node->value << " ";
		}
	}

	Node<T>* addRecursive(Node<T>* current, T value) {
		if (current == nullptr) {
			return new Node<T>(value);
		}

		if (value < current->value) {
			current->leftChild = addRecursive(current->leftChild, value);
		}
		else if (value > current->value) {
			current->rightChild = addRecursive(current->rightChild, value);
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
			? containsNodeRecursive(current->leftChild, value)
			: containsNodeRecursive(current->rightChild, value);
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
				currentNode = currentNode->rightChild;
			}
			else
			{
				currentNode = currentNode->leftChild;
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
			if (current->leftChild == nullptr && current->rightChild == nullptr) {
				return nullptr;
			}

			// Case 2: only 1 child
			if (current->rightChild == nullptr) {
				return current->leftChild;
			}

			if (current->leftChild == nullptr) {
				return current->rightChild;
			}

			// Case 3: 2 children
			int smallestValue = findSmallestValue(current->rightChild);
			current->value = smallestValue;
			current->rightChild = removeRecursive(current->rightChild, smallestValue);
			return current;
		}

		if (value < current->value) {
			current->leftChild = removeRecursive(current->leftChild, value);
			return current;
		}

		current->rightChild = removeRecursive(current->rightChild, value);
		return current;
	}

	T findSmallestValue(Node<T>* root) {
		return root->leftChild == nullptr ? root->value : findSmallestValue(root->leftChild);
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