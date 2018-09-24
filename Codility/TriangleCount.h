
#include <iostream>
#include <random>
#include <unordered_set>
#include <atomic>
#include <thread>
#include <vector>
#include <set>
using namespace std;

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