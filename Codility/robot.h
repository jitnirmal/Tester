#include <iostream>
#include <vector>
using namespace std;
using matrix = std::vector<vector<int>>;

int numberOfPaths(const matrix& mt)
{
	int rows = mt.size();
	int cols = mt[0].size();
	matrix paths(rows, std::vector<int>(cols));

	// Count of paths to reach any cell in first column is 1
	for (int row = 0; row < rows; row++)
		paths[row][0] = 1;

	// Count of paths to reach any cell in first column is 1
	for (int col = 0; col < cols; col++)
		paths[0][col] = 1;

	// Calculate count of paths for other cells in bottom-up manner using
	// the recursive solution
	for (int row = 1; row < rows - 1; row++)
	{
		for (int col = 1; col < cols - 1; col++)
		{
			// By uncommenting the last part of the code calculates the total
			// possible paths if the diagonal Movements are allowed
			paths[row][col] = !mt[row - 1][col] + !mt[row][col - 1];  //+ count[i-1][j-1];
		}



	}
	return paths[rows - 1][cols - 1];
}


int main()
{
	matrix A = { { 0, 0, 0 },
							  { 0, 1, 0 },
							  { 0, 0, 0 } };

	cout << numberOfPaths(A) << " \n";
}