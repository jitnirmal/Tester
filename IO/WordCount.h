#pragma once

#include <cstdio> // easier than iostream for formatted output
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>

const char* filename = "F:\\2018\\Coding\\Tester\\IO\\files\\alice_in_wonderland.txt";

typedef std::unordered_map<std::string, std::size_t> WordCountMapType;

WordCountMapType wordsInFile() // for each word
{ // in file, return
	WordCountMapType wordCounts; // occurrences
	std::ifstream file(filename); // # of
	if (file.is_open()) {
		for (std::string word; file >> word; ) {
			int index;
			//while ((index = word.find_first_of(".,!?\\;-*+")) != std::string::npos)
			//	word.erase(index, 1);

			++wordCounts[word];
		}
	}
	return wordCounts;
}

void top20Words()
{

	auto comp = [](const int a, const int b) { return a > b; };

	auto words = wordsInFile();
	int count{ 0 };
	std::map<int, std::string, decltype(comp) > sorted(comp);
	for (const auto& item : words)
	{
		sorted[item.second] = item.second;
	}

	for (const auto& item : sorted)
	{
		if (count == 20)
			break;
		std::cout << item.first <<" : " <<item.second << std::endl;
		++count;
	}
}