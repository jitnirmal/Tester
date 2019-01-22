#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_set>
#include <array>
#include <memory>

int power(int base, int n)
{
	int result = 1;
	for (unsigned int i = 0; i < n; ++i)
	{
		result *= base;
	}
	return result;
}

void tcopy(char to[], const char from[])
{
	int i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}

char* rtrim(char* str, char replaceChar=' '){
	char* end = str + strlen(str);
	while (*(--end) == replaceChar)
	{
		*end = '\0';
	}
	return str;
}

void ltrim(char *src){
	char *dst =src;
	while (*src == ' '){
		++src;
	}

	if (dst == src) return;

	while ((*dst++ = *src++)) { ; }

	return;
}

void testStrings() {
	power(3, 3);
	char buffer[100];
	const char* str = "nirmaljit";
	tcopy(buffer, str);

	char str2[] = "nirmal  ";
	rtrim(str2);

	char str3[] = "   nirmal";
	ltrim(str3);
}

/// <summary>
/// integer to binary
/// </summary>

/// <summary>
/// Explain what the following code does:
/// </summary>
bool isPowerOf2(int n) {
	return ((n & (n - 1)) == 0);
}




void testPointers()
{
	auto adjustArray = [](int* arr) {
		arr[4] = 15;
		*(arr + 5) = 16;
	};

	int arr[] = { 1,2,3,4,5,6 };
	int i = 2;

	// i[arr] is same as arr[i]
	//*(arr+1) = a[i]
	*(arr + i) = arr[i] + i[arr];

	int* temp = arr;
	adjustArray(temp);


	char* s[] = { "nirmal","jit", "singh","rauni" };
	char **ptr[] = { s + 3,s + 2, s + 1, s };
	char ***parent = ptr;

	std::cout << **++parent << std::endl;
}

void reserveVectorTable()
{
	std::vector<std::vector<int>> vTable(3, std::vector<int>(5));

}

void updateAndPrint(const int row, const int col, int** arr)
{
	int count = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			arr[i][j] = ++count;
		}
	}
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void D2Array1()
{
	const int row(3), col(4);
	int** arr = (int**)malloc(row * sizeof(int));

	for (int i = 0; i < col; ++i)
	{
		arr[i] = (int*)malloc(col * sizeof(int));
	}
	updateAndPrint(row, col, arr);
}

void D2Array2()
{
	const int row(3), col(4);
	int* arr[row];

	for (int i = 0; i < col; ++i)
	{
		arr[i] = (int*)malloc(col * sizeof(int));
	}
	updateAndPrint(row,col,arr);
}


void Test_C_Recipies()
{
	//testPointers();
	//reserveVectorTable();
//	D2Array1();
	D2Array2();
}