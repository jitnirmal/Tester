#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
//http://interactivepython.org/courselib/static/pythonds/Trees/BinaryHeapImplementation.html
using namespace std;

class BinaryHeap
{
private:
	std::vector<int> vect;
	int heapSize;

	// three helper navigation function
	int parent(int i) { return i >> 1; } // i/2
	int leftChild(int i) { return i << 1; } // i*2
	int rightChild(int i) { return (i << 1) + 1; } // i*2+1

	void ShiftUp(int index);
	void ShiftDown(int i);

public:
	BinaryHeap():heapSize(0){
		// vector zeroth index will not be used...
		vect.push_back(-1);
	}
	BinaryHeap(const vector<int>& data) :heapSize(0) {
		// vector zeroth index will not be used...
		vect.push_back(-1);
		for (const auto& i : data)
		{
			Insert(i);
		//	print();
		}
	}

	bool IsEmpty();
	void Insert(int key);
	int ExtractMax();
	int GetMax();
	void print(){
		for (size_t index = 1; index <= heapSize; ++index)
		{
			std::cout << vect[index] << ", ";
		}
		std::cout << endl;
	}
};

bool BinaryHeap::IsEmpty()
{
	// Heap is empty if only
	// heapSize = 0
	return heapSize == 0;
}

void BinaryHeap::ShiftDown(int i)
{
	if (i > heapSize)
		return;
	
	int swapId = i;

	if (leftChild(i) <= heapSize && vect[i] < vect[leftChild(i)])
		swapId = leftChild(i);

	if (rightChild(i) <= heapSize && vect[swapId] < vect[rightChild(i)])
		swapId = rightChild(i);
		
	if (swapId != i)		                 // Swap with the larger of the two children
	{
		std::swap(vect[i], vect[swapId]);   // Swap downwards with the larger of the two children
		ShiftDown(swapId);					// Recurse until the index
	}
}

int BinaryHeap::ExtractMax() {
	int maxVal = vect[1];					// Maximum value is in root
	std::swap(vect[1], vect[heapSize]);     // Swap with the last existing leaf

	--heapSize;
	ShiftDown(1);							// Fix heap property downwards
	return maxVal;							// Return the maximum value
}


/*
void BinaryHeap::ShiftUp(int index) {
	
	for (int index = heapSize; index > 0; index = parent(index)) 
	{
		if (vect[index] > vect[parent(index)])
		{
			std::swap(vect[index], vect[parent(index)]);  // Swap Upwards
		}
		else {
			break;
		}
	}
}
*/
void BinaryHeap::ShiftUp(int index) {
	if (index == 1)							// Do nothing in root
		return;

	if (vect[index] > vect[parent(index)])
	{
		std::swap(vect[index], vect[parent(index)]);  // Swap Upwards
		ShiftUp(parent(index));							// Recurse until root
	}
}

void BinaryHeap::Insert(int key)
{
//	if (heapSize + 1 >= (int)vect.size())				// Add a new element in vector
//		vect.push_back(0);

	vect.push_back(key);
	++heapSize;
	ShiftUp(heapSize);									// Shift upwards
}

int BinaryHeap::GetMax()
{
	// Return root's key
	return vect[1];
}

void TestBinaryHeap() {
	
	std::vector<int> data { 5, 7, 13, 8, 3, 9, 12, 10};
	// Instantiate priority queue
	BinaryHeap priorityQueue(data);
	priorityQueue.print();

	cout << "GetMax() = " << priorityQueue.GetMax() << endl;
	cout << "ExtractMax() = " << priorityQueue.ExtractMax() << endl;
	cout << "GetMax() = " << priorityQueue.GetMax() << endl;
	priorityQueue.print();
}