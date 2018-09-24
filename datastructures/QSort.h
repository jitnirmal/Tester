#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>

void quickSort(int arr[], int low, int high) {
	if (arr == nullptr )
		return;

	if (low >= high)
		return;

	// pick the pivot
	int middle = low + (high - low) / 2;
	int pivot = arr[middle];

	// make left < pivot and right > pivot
	int i = low, j = high;
	while (i <= j) {
		while (arr[i] < pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i <= j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}

	// recursively sort two sub parts
	if (low < j)
		quickSort(arr, low, j);

	if (high > i)
		quickSort(arr, i, high);
}