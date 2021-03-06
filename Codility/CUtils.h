#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_set>
#include <array>


// size of operator
#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)

// A utility function that returns true if x is perfect square
bool isPerfectSquare(int x)
{
	int s = static_cast<int>(sqrt(x));
	return (s*s == x);
}

// Returns true if n is a Fibinacci Number, else false
bool isFibonacci(int n)
{
	// n is Fibinacci if one of 5*n*n + 4 or 5*n*n - 4 or both
	// is a perferct square
	return isPerfectSquare(5 * n*n + 4) ||
		isPerfectSquare(5 * n*n - 4);
}

size_t mystrlen(char *str)
{
	size_t len = 0;
	for (int i = 0; str[i] != 0; ++i)
	{
		len++;
	}
	
	return(len);
}

int myatoi(char *str)
{
	int result = 0; 
	for (int i = 0; str[i] != '\0'; ++i)
		result = result * 10 + str[i] - '0';
	return result;
}

char* mystrcpy(char *dest, const char* src)
{
	char *ret = dest;
	while (*dest++ = *src++)
		;
	return ret;
}

char* mystrncpy(char *dst, const char*src, size_t n)
{
	char *ret = dst;
	size_t i = 0;
	while ((i++ != n) && (*dst++ = *src++));
		;
	return ret;
}

int mystrcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2)) ++s1, ++s2;

	return (*s1 > *s2) - (*s2  > *s1);
}

char * my_strcat(char *dest, const char *src)
{
	char *rdest = dest;

	while (*dest)
		dest++;

	while (*dest++ = *src++)
		;

	return rdest;
}

void test_strcmp()
{
	const char* str1 = "nirmaljit";
	const char* str2 = "nirmalji";
	auto result = mystrcmp(str1, str2);
}

void * myMemcpy(void *dest, const void *src, size_t len)
{
	char *d = (char*)dest;
	const char *s = (const char*)src;
	while (len--)
		*d++ = *s++;
	return (void*)dest;
}

void myStrReverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	while (start < end)
	{
		std::swap(*(str + start), *(str + end));
		start++;
		end--;
	}
}
char* myItoa(int num, char* str, int base)
{
	int i = 0;
	bool isNegative = false;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with  
	// base 10. Otherwise numbers are considered unsigned. 
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	// Process individual digits 
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-' 
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator 
				   // Reverse the string 
	myStrReverse(str, i);
	return str;
}

/*-----------------------------------------------------------------------------------*/
//Write code to reverse a C - Style String. (C - String means that �abcd� is represented as five characters, including the null character.)
void reverseString1(char* string)
{
	char* begin = string;
	char* end = string + strlen(string) - 1;

	while (begin < end)
	{
		char temp = *begin;
		*begin = *end;
		*end = temp;
		++begin;
		--end;
	}
}

void reverseString2(char *str) {
	std::size_t len = std::strlen(str);
	for (std::size_t index = 0; index != len / 2; ++index) {
		std::swap(str[index], str[len - index - 1]);
	}
}

void TestReverseString()
{
	char string[10] = {'n','i', 'r', 'm', 'a', 'l', 'j', 'i', 't','\0'};
	reverseString1(string);
	reverseString2(string);
}

/*-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------*/
//Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer.NOTE: One or two additional variables are fine.An extra copy of the array is not.


/*-----------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------*/
//Implement an algorithm to determine if a string has all unique characters.What if you can not use additional data structures ?
bool checkUniqueString(const char* string)
{
	// do it with onordered map
	std::unordered_set<char> uos;
	while (char c = *string++){
		if (uos.find(c) == uos.end()){
			uos.insert(c);
		}
		else{
			return false;
		}
	}
	return true;
}

bool checkUniqueString_2(const char* string)
{
	// using bool array
	std::array<bool, 256> ba = {false};
	while (int intChar = static_cast<int>(*string++)) {
		if (ba[intChar] == false) {
			ba[intChar] = true;
		}
		else {
			return false;
		}
	}
	return true;
}

void Tes_checkUniqueString()
{
	auto isUnique1 = checkUniqueString("nirmal");
	auto isUnique2 = checkUniqueString("nirmaljit");

	auto isUnique3 = checkUniqueString_2("nirmal");
	auto isUnique4 = checkUniqueString_2("nirmaljit");

}
/*-----------------------------------------------------------------------------------*/


unsigned int my_strlen1(const char* str) noexcept
{
	const char* temp = str;
	while (*temp++);
	return (temp - str - 1);
}

unsigned int my_strlen2(const char* str) noexcept
{
	// this does not return 
	return (sizeof(str) / sizeof(char));
}

unsigned int my_strlen3(const char* str) noexcept
{
	return strlen(str);
}

bool isPalindrome(const char* str)
{
	const char* first = str;
	const char* end = str+ strlen(str) - 1;
	
	while (first < end)
	{
		if (*first++ != *end--)
			return false; // not palindrome
	}
	return true;
}

void Tes_C_tUtils()
{
	constexpr char* str = "nirmaljit";
	auto len1 = my_strlen1(str);
	auto len2 = my_strlen2(str);
	auto len3 = my_strlen3(str);
	
	auto pl1 = isPalindrome("malayalam");
	auto pl2 = isPalindrome("madam");
	auto pl3 = isPalindrome("malay");
}