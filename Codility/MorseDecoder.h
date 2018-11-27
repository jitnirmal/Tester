#pragma once
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
constexpr char SEPERATOR = '#';

class MorseCodeDecoder {
private:

	std::string decode(std::string& result) {
		std::string decodeStr;
		std::string temp;

		for (int i = 0; i < result.length(); ++i)
		{
			if (result[i] == SEPERATOR)
			{
				decodeStr += _morseDecryptCode.at(temp);
				temp = "";
			}
			else {
				temp += result[i];

				if (i == result.length() - 1) {
					decodeStr += _morseDecryptCode.at(temp);
					temp = "";
				}
			}
		}
		return decodeStr;
	}

	void processCodeforTextRecursive(const std::string morseCode, std::string subCodes, int codeSize)
	{
		for (int i = 1; i <= codeSize; i++) {

			std::string prefix = morseCode.substr(0, i);
			// only valid subcodes will be docoded..
			if (_morseDecryptCode.find(prefix) != _morseDecryptCode.end())
			{
				if (i == codeSize)
				{
					subCodes += prefix;
					_textCodeTable.push_back(decode(subCodes));
					return;
				}
				//std::cout << "found >> "<<subCodes <<" :  " <<prefix << std::endl;
				processCodeforTextRecursive(morseCode.substr(i, codeSize - i), subCodes + prefix + SEPERATOR, codeSize - i);
			}
		}
	}

	void processCodeforTextIterative(const std::string morseCode)
	{
		for (int i = 1; i <= morseCode.length(); i++) {
			//std::cout << i << std::endl;
			string decodedText;
			for (int j = 0; (j + i) <= morseCode.length(); j++)
			{
				std::string subCode = morseCode.substr(j, i);
				if (_morseDecryptCode.find(subCode) != _morseDecryptCode.end())
				{
					decodedText += _morseDecryptCode.at(subCode);
					//std::cout << i <<" : "<<j <<" -- "<< decodedText << std::endl;
				}
				std::cout << i << " : " << j << " -- " << subCode << std::endl;
			}
			if (decodedText.size())
			{
				_textCodeTable.push_back(decodedText);
			}
			//std::cout << "------------------" << std::endl;
		}
	}

public:
	std::vector<std::string> getTextForMorseCode(const std::string& code)
	{
		std::string emptySubCodes;
		_textCodeTable.clear();
		processCodeforTextRecursive(code, emptySubCodes, code.size());

		// sort it alphabetically.
		std::sort(std::begin(_textCodeTable), std::end(_textCodeTable));
		return _textCodeTable;
	}
private:
	std::vector<string> _textCodeTable;
	const std::unordered_map<std::string, char> _morseDecryptCode{ { ".",'E' },{ "..",'I' },{ "---",'O' },
	{ ".--.",'P' },{ ".-.",'R' },{ "-",'T' },{ "...-",'V' } };
};



vector<string> decode_all_words(string code) {
	MorseCodeDecoder decoder;
	return decoder.getTextForMorseCode(code);
}

void TestMorseCode() {
	auto wordList = decode_all_words(".-...-");

	for (const auto& item : wordList)
	{
		std::cout << item << std::endl;
	}
}

class MorseCodeDecoder3 {
private:

	std::string decode(std::string& concatedCodes) {
		std::string decodeStr;
		std::string codeStr;
		std::stringstream ss(concatedCodes);

		while (std::getline(ss, codeStr, SEPERATOR)) {
			decodeStr += _morseDecryptCode.at(codeStr);
		}

		return decodeStr;
	}

	void processCodeforTextRecursive(const std::string morseCode, std::string concatedCodes)
	{
		for (int i = 1; i <= morseCode.size(); i++) {
			std::string subCode = morseCode.substr(0, i);
			if (_morseDecryptCode.find(subCode) != _morseDecryptCode.end()) {
				// all the valid codes are concatenated 
				if (i == morseCode.size()) {
					concatedCodes += subCode + SEPERATOR;
					_textCodeTable.push_back(decode(concatedCodes));
				}
				else {
					//std::cout << "recurse >> " << data << std::endl;
					processCodeforTextRecursive(morseCode.substr(i, morseCode.size() - i),
						(concatedCodes + subCode + SEPERATOR));
				}
			}
		}
	}


public:
	std::vector<std::string> getTextForMorseCode(const std::string& code)
	{
		std::string emptySubCodes;
		_textCodeTable.clear();
		processCodeforTextRecursive(code, emptySubCodes);
		//processCodeforTextIterative(code);
		// sort it alphabetically.
		std::sort(std::begin(_textCodeTable), std::end(_textCodeTable));
		return _textCodeTable;
	}
private:
	std::vector<string> _textCodeTable;
	const std::unordered_map<std::string, char> _morseDecryptCode{ { "a",'E' },{ "aa",'I' },{ "bbb",'O' },
	{ "abba",'P' },{ "aba",'R' },{ "b",'T' },{ "aaab",'V' } };

	//const std::unordered_map<std::string, char> _morseDecryptCode{ { ".",'E' },{ "..",'I' },{ "---",'O' },
	//{ ".--.",'P' },{ ".-.",'R' },{ "-",'T' },{ "...-",'V' } };
};

vector<string> decode_all_words3(string code) {
	MorseCodeDecoder3 decoder;
	return decoder.getTextForMorseCode(code);
}

void testMorseCode3()
{
	auto textTable = decode_all_words3("abaaab");
	//auto textTable = decode_all_words2(".-...-");
	//MorseCodeDecoder2().getTextForMorseCode("ABCDEF");
	//multiply("12", "1234");

	for (const auto& item : textTable) {
		std::cout << item << std::endl;
	}

	bool resultOK = true;
	std::cout << "-----------------------" << std::endl;
	auto textTable2 = decode_all_words(".-...-");
	if (textTable2.size() == textTable.size())
	{
		for (int i = 0; i < textTable.size(); ++i) {
			if (textTable[i] != textTable2[i])
			{
				resultOK = false;
			}
		}
	}
	else
	{
		resultOK = false;
	}
	std::cout << "resultOK : " << resultOK << std::endl;
}
