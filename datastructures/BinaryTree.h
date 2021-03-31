#pragma once

#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include <string>

/*
* Find the minimum depth of a binary tree
https://www.techiedelight.com/find-minimum-depth-binary-tree/

Print right view of a binary tree
https://www.techiedelight.com/print-right-view-binary-tree/

Spiral order traversal of a binary tree
https://www.techiedelight.com/spiral-order-traversal-binary-tree/


*/


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
	using NodeType = Node<T>;
	using NodePtr = NodeType*;

public:
	BinaryTree() noexcept :_root(nullptr) {}

	BinaryTree(std::vector<T>& nodes)
	{
		_root = createMinimalBST(nodes, 0, nodes.size() - 1);
	}


	void add(T value) {
		_root = addRecursive(_root, value);
	}

	bool containsNode(T value)  const noexcept
	{
		return containsNodeIterative(_root, value);
	}



	//Depth-First Search
	// goes deep as much as possible in every child before exploring the next sibling
	void TraverseInOrder()
	{
		std::cout << "in order traverse : ";
		traverseInOrder(_root);
		std::cout << "\n";
	}

	void TraverseInOrderIterative() const noexcept
	{
		traverseInOrderIterative(_root);
		std::cout << "\n";
	}

	void TraversePreOrder() const noexcept
	{
		std::cout << "pre order traverse : ";
		traversePreOrder(_root);
		std::cout << "\n";
	}

	void TraversePostOrder() const noexcept
	{
		std::cout << "pre order traverse : ";
		traversePostOrder(_root);
		std::cout << "\n";
	}

	//Breadth-First Search
	void TraverseLevelOrder()  const noexcept
	{
		std::cout << "level order traverse : ";
		if (_root == nullptr) {
			return;
		}

		traverseLevelOrder();
	}

	void remove(T value)
	{
		removeRecursive(_root, value);
	}

	int Height()
	{
		auto result = height(_root);
		std::cout << "height is  : " << result << std::endl;
		return result;
	}

	bool IsBalanced()
	{
		auto result = isBalanced(_root);
		auto message = (result == true) ? "Tree is Balanced" : "Tree is not balanced";
		std::cout << message << std::endl;
		return result;
	}

	void PrintLevelOrderTree()
	{
		auto lists = getLevelLinkedList(_root);
		for (const auto& list : lists)
		{
			for (const auto& item : list)
			{
				auto left = item.left ? std::to_string(item.left->value) : "NA";
				auto right = item.right ? std::to_string(item.right->value) : "NA";

				std::cout << item.value << " (" << left << "," << right << ")   |  ";
			}
			std::cout << "\n-----------------------------\n";
		}
	}

	NodePtr createMinimalBST(std::vector<T> arr, int start, int end)
	{
		if (end < start)
		{
			return nullptr;
		}

		int mid = (start + end) / 2;
		auto node = new NodeType(arr[mid]);

		node->left = createMinimalBST(arr, start, mid - 1);
		node->right = createMinimalBST(arr, mid + 1, end);
		return node;
	}

private:

	int height(NodePtr node) const noexcept
	{
		if (!node)
			return -1;
		auto lDepth = height(node->left);
		auto rDepth = height(node->right);

		auto height = lDepth > rDepth ? (lDepth + 1) : (rDepth + 1);
		//std::cout << node->value << "(" << height << ")" << " ";

		return height;
	}

	void traverseLevelOrder() const noexcept
	{
		std::list<NodePtr> nodes;
		nodes.push_back(_root);

		while (!nodes.empty())
		{
			auto Node = nodes.front();
			nodes.pop_front();

			std::cout << Node->value << " ";

			if (Node->left != nullptr)
			{
				nodes.push_back(Node->left);
			}

			if (Node->right != nullptr)
			{
				nodes.push_back(Node->right);
			}
		}
	}

	void traverseInOrderIterative(NodePtr node) const noexcept
	{
		std::stack<NodePtr> nodeStack;
		NodePtr current = node;
		while (!nodeStack.empty() || current)
		{
			if (current)
			{
				nodeStack.push(current);
				current = current->left;
			}
			else
			{
				current = nodeStack.top();
				nodeStack.pop();
				std::cout << current->value << " ";
				current = current->right;
			}
		}
	}

	void traverseInOrder(NodePtr Node) const noexcept
	{
		if (Node != nullptr) {
			traverseInOrder(Node->left);
			std::cout << Node->value << " ";
			traverseInOrder(Node->right);
		}
	}

	void traversePreOrder(NodePtr Node) const noexcept
	{
		if (Node != nullptr) {
			std::cout << Node->value << " ";
			traversePreOrder(Node->left);
			traversePreOrder(Node->right);
		}
	}

	void traversePreOrderIterative(NodePtr node) const noexcept
	{
		std::stack<NodePtr> nodeStack;
		auto current = node;
		nodeStack.push(current);

		std::queue<T> result;

		while (!nodeStack.empty())
		{
			auto node = nodeStack.top(); nodeStack.pop();
			result.push(node->value);

			if (node->right)
				nodeStack.push(node->right);

			if (node->left)
				nodeStack.push(node->left);
		}

		while (!result.empty())
		{
			std::cout << result.front() << " ";
			result.pop();
		}
	}

	void traversePostOrder(NodePtr Node) const noexcept
	{
		if (Node != nullptr) {
			traversePostOrder(Node->left);
			traversePostOrder(Node->right);
			std::cout << Node->value << " ";
		}
	}

	void traversePostOrderIterative(NodePtr node) const noexcept
	{
		std::stack<NodePtr> nodeStack;
		nodeStack.push(node);

		std::stack<T> result;

		while (!nodeStack.empty())
		{
			auto node = nodeStack.top(); nodeStack.pop();
			result.push(node->value);

			if (node->left)
				nodeStack.push(node->left);

			if (node->right)
				nodeStack.push(node->right);

		}

		while (!result.empty())
		{
			std::cout << result.top() << " ";
			result.pop();
		}
	}

	NodePtr addRecursive(NodePtr current, T value)
	{
		if (current == nullptr) {
			return new NodeType(value);
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



	bool containsNodeRecursive(NodePtr current, T value) const noexcept
	{
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


	bool containsNodeIterative(NodePtr current, T value)  const noexcept
	{
		NodePtr currentNode = current;
		while (currentNode != nullptr)
		{
			if (value == currentNode->value)
			{
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

	NodePtr removeRecursive(NodePtr current, T value) {
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

	T findSmallestValue(NodePtr root) {
		return root->left == nullptr ? root->value : findSmallestValue(root->left);
	}

	std::vector<std::list<NodeType>> getLevelLinkedList(NodePtr node)
	{
		auto result = std::vector<std::list<NodeType>>();
		auto currentLevelList = std::list<NodeType>();
		if (node)
		{
			currentLevelList.push_back(NodeType(*node));
		}

		while (!currentLevelList.empty())
		{
			result.emplace_back(currentLevelList);
			auto parents = currentLevelList;
			currentLevelList.clear();
			for (const auto& parent : parents)
			{
				if (parent.left)
				{
					currentLevelList.push_back(NodeType(*(parent.left)));
				}
				if (parent.right)
				{
					currentLevelList.push_back(NodeType(*(parent.right)));
				}
			}
		}
		return result;
	}

	bool isBalanced(NodePtr node)
	{
		if (!node) return true;

		int heightDiff = height(node->left) - height(node->right);

		if (std::abs(heightDiff) > 1)
			return false;

		return isBalanced(node->left) && isBalanced(node->right);
	}

private:
	NodePtr _root;

};



void TestBinaryTree()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8 };
	BinaryTree<int> bt(v);

	bt.PrintLevelOrderTree();
	bt.TraverseInOrder();
	bt.Height();
	bt.IsBalanced();

	//bt.TraversePreOrder();
	//bt.TraversePostOrder();
	//bt.TraverseLevelOrder();

	if (bt.containsNode(15) == false) {
		std::cout << "value not expected" << std::endl;
	}

	if (bt.containsNode(8) == true) {
		std::cout << "value expected" << std::endl;
	}
}

int main()
{
	TestBinaryTree();
}