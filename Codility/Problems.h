#include <iostream>

auto maxPeopleEntrySlot()
{
	std::string str = "nirmal";
	for (size_t index = 0; index < str.size(); ++index)
	{
		str = rotate(str);
	}

	std::vector<int> in = { 1, 2, 9, 5, 5 };
	std::vector<int> out= { 4, 5, 12, 9, 12 };

	std::vector<int> timeRegistor(24,0);

	for (size_t i = 0 ; i < in.size(); ++i )
	{
		for (int j = in[i]; j < out[i]-1; ++j)
			timeRegistor[j]++;
	}

	auto maxSlot = std::max_element(timeRegistor.begin(), timeRegistor.end());
	std::cout << "max element at: " << std::distance(timeRegistor.begin(), maxSlot) << '\n';

	std::vector<int> result;
	for (size_t i = 0; i < timeRegistor.size(); ++i)
	{
		if (timeRegistor[i] == *maxSlot)
		{
			result.emplace_back(i);
		}
	}
	return result;
}

void permute(std::vector<std::string>& result, std::string& str, int index)
{
	if (index == str.size() - 1)
		result.push_back(str);
	else
	{
		for (size_t j = index; j < str.size(); ++j)
		{
			// Swap the character at ith index with every other value to get all the possible permutations.
			std::swap(str[index], str[j]);
			std::cout << "F " << str << " i=" << index << " j=" << j << std::endl;
			permute(result, str, index + 1);
			// second swap is just to restore the string back to start again fresh
			std::swap(str[index], str[j]); 
		}
	}
}

void permute(std::vector<std::string>& result, std::string& str, std::string prefix)
{
	if (str.empty())
	{
		result.push_back(prefix);
		std::cout << "-------------------" << std::endl;
	}
	else
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			std::string rem = str.substr(0, i) + str.substr(i+1);
			std::cout << "str=" << rem << " pre=" << prefix + str.at(i) << " i =" << i<< std::endl;
			permute(result, rem, prefix + str.at(i));
		}
	}
}

int main()
{
	try 
	{
		std::vector<std::string> results;
		std::string str = "ABC";
		//permute(results,str,0);

		std::vector<std::string> results2;
		std::string str2 = "ABC";
		permute(results2, str2, "");
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception during testing..." << std::endl;
	}
}