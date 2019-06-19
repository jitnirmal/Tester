#pragma once
#include <numeric> 
#include <chrono>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
constexpr auto MAX_SIZE = 1'000'000;
constexpr auto ITERATIONs = 10;



auto getData = [](const auto & size) {
	std::vector<int> vRandom(size);
	std::generate(vRandom.begin(), vRandom.end(), [&]() {return rand() % size; });
	return vRandom;
};

using Clock = std::chrono::high_resolution_clock;

template <typename Time>
auto average = [](std::vector<Time> & vi) {
	long sum = 0;
	for (auto p : vi) {
		sum = sum + p.count();
	}
	return (sum / vi.size());
};

void printHeader() {
	std::cout << " ------------------------------------------------------------------" << std::endl;
	std::cout << " Hash Table Tests : Iterations = " << ITERATIONs << " Max Items : " << MAX_SIZE << std::endl;
}
