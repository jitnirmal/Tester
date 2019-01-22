
#include <iostream>
#include <random>
#include <unordered_set>
#include <atomic>
#include <thread>
#include <vector>
#include <set>
using namespace std;

/// <summary>
/// K’th Smallest/Largest Element in Unsorted Array | Set 1
/// Method 1 (Simple Solution) - sort the given array using a O(nlogn) sorting algorithm like Merge Sort, Heap Sort, etc and return the element at index k - 1 in the sorted array
///    Time Complexity of this solution is O(nLogn).
/// 
/// Method 2 (Using Min Heap – HeapSelect)
///		Time complexity of this solution is O(n + kLogn).
/// 
/// 
/// Method 3 (QuickSelect) 
///		This is an optimization over method 1 if QuickSort is used as a sorting algorithm in first step.
///		In QuickSort, we pick a pivot element, then move the pivot element to its correct position and partition the array around it.
///		The idea is, not to do complete quicksort, but stop at the point where pivot itself is k’th smallest element.
///		Also, not to recur for both left and right sides of pivot, but recur for one of them according to the position of pivot.
///		The worst case time complexity of this method is O(n2), but it works in O(n) on average.
/// 
/// </summary>


/// <summary>
/// Remove duplicates from unsorted array
///		1. Take a hash map, in which will store all the elements which has appeared before.
/// </summary>


/// <summary>
/// Find floor and ceil in an unsorted array
/// </summary>


/// <summary>
/// Largest Sum Contiguous Subarray
/// </summary>

/// <summary>
/// Heap works on a comparison based sorting algorithm. It is one of the most efficient sorting algorithms, because of the fact that no extra space is used for sorting as the heap can be constructed in the same array where we got as input.
/// Another important factor here is that though, Heap sort is considered order of nlog(n) but the actual Heap sort is lesser than O(nlog(n)).
/// This is because of the fact that after each extraction or deletion from the tree(while sorting) the size of Heap is reduced, thus affecting the time taken for the next extraction or deletion from the tree.The heap is reconstructed after each removal.
/// Applications of HEAP Sort :
///   1. To quickly find the smallest and largest element from a collection of items or array.
///   2. In the implementation of Priority queue in graph algorithms like Dijkstra's algorithm (shortest path), Prim's algorithm(minimum spanning tree) and Huffman encoding(data compression).
///   3. Comparing with Quick Sort, it has better worst case O(nlog(n)).Quick Sort has complexity of O(n ^ 2).
///   4. Heap Sort is very fast because it has O(nlog(n)) time complexities for all the cases(best case, average case and worst case).
///   5. Systems concerned with security and embedded system such as Linux Kernel uses Heap Sort because of the O(nlog(n)) which reduces the processing time of the system.
/// </summary>

/// <summary>
/// 1. Sort the array in non-decreasing order.
/// 2. Initialize two pointers ‘i’ and ‘j’ to first and second elements respectively, and initialize count of triangles as 0.
/// 3. Fix ‘i’ and ‘j’ and find the rightmost index ‘k’(or largest ‘arr[k]’) such that ‘arr[i] + arr[j] > arr[k]’.The number of triangles that can be formed with ‘arr[i]’ and ‘arr[j]’ as two sides is ‘k – j’.Add ‘k – j’ to count of triangles.
/// Let us consider ‘arr[i]’ as ‘a’, ‘arr[j]’ as b and all elements between ‘arr[j + 1]’ and ‘arr[k]’ as ‘c’.The above mentioned conditions(ii) and (iii)are satisfied because ‘arr[i] < arr[j] < arr[k]'. And we check for condition (i) when we pick 'k'
/// 4. Increment ‘j’ to fix the second element again.
/// Note that in step 3, we can use the previous value of ‘k’.The reason is simple, if we know that the value of ‘arr[i] + arr[j - 1]’ is greater than ‘arr[k]’, then we can say ‘arr[i] + arr[j]’ will also be greater than ‘arr[k]’, because the array is sorted in increasing order.
/// 5. If ‘j’ has reached end, then increment ‘i’.Initialize ‘j’ as ‘i + 1’, ‘k’ as ‘i + 2’ and repeat the steps 3 and 4.
/// </summary>
/// <param name="A"></param>
/// <returns></returns>
int solution(vector<int> A) {
	std::sort(A.begin(), A.end());
	int count = 0;
	for (int i = 0; i < A.size() - 2; ++i)
	{
		int k = i + 2;
		for (int j = i + 1; j < A.size(); ++j)
		{
			while ((k < A.size()) && (A[i] + A[j] > A[k]))
				++k;
			count += k - j - 1;
		}
	}
	return count;
}

int main() {
	std::vector<int> v = { 10, 21, 22, 100, 101, 200, 300 };
	auto result = solution(v);
	
}