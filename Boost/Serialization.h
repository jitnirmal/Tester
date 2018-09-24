#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <filesystem>

namespace fs = std::experimental::filesystem;

class csvReader {
private:
	std::string _fileName;
	const char _delim;
public:
	csvReader(const std::string& fileName, const char delim = ',') :
		_fileName(fileName),
		_delim(delim){}
	std::vector<std::vector<std::string>> getData();
};

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(std::move(item)); 
	}
	return elems;
}

std::vector<std::vector<std::string>> csvReader::getData() {
	std::ifstream file(_fileName);
	std::vector<std::vector<std::string> > dataList;

	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		dataList.push_back(::split(line,_delim));
	}
	// Close the File
	file.close();
	return dataList;
}

void TestCSVReader() 

{
	auto file = std::string{ "F:\\2018\\Coding\\Tester\\Files\\" };
	file = file.append("EQ010618.csv");
	const auto delim = ',';
	auto reader = std::make_unique<csvReader>(file,delim);
	auto data = reader->getData();

}

void read_data_vec(char const * const filename,
	std::vector<unsigned char>& data)
{
	std::ifstream ifile("sample.bin", std::ios::binary);
	if (ifile.is_open())
	{
		data = std::vector<unsigned char>(
			std::istreambuf_iterator<char>(ifile),
			std::istreambuf_iterator<char>());
		ifile.close();
	}
}

void write_data_vec1(char const * const filename, 
	std::vector<unsigned char>& data)
{
	std::ifstream ifile(filename, std::ios::binary);
	if (ifile.is_open())
	{
		ifile.seekg(0, std::ios_base::end);
		auto length = ifile.tellg();
		ifile.seekg(0, std::ios_base::beg);
		data.reserve(static_cast<size_t>(length));
		std::copy(std::istreambuf_iterator<char>(ifile),
			std::istreambuf_iterator<char>(),
			std::back_inserter(data));
		ifile.close();
	}
}

bool write_data(char const * const filename,
	char const * const data,
	size_t const size)
{
	auto success = false;
	std::ofstream ofile(filename, std::ios::binary);
	if (ofile.is_open())
	{
		try
		{
			ofile.write(data, size);
			success = true;
		}
		catch (std::ios_base::failure &)
		{
			// handle the error
		}
		ofile.close();
	}
	return success;
}

size_t read_data(char const * const filename,
	std::function<char*(size_t const)> allocator)
{
	size_t readbytes = 0;
	std::ifstream ifile(filename, std::ios::ate | std::ios::binary);
	if (ifile.is_open())
	{
		auto length = static_cast<size_t>(ifile.tellg());
		ifile.seekg(0, std::ios_base::beg);
		auto buffer = allocator(length);
		try
		{
			ifile.read(buffer, length);
			readbytes = static_cast<size_t>(ifile.gcount());
		}
		catch (std::ios_base::failure &)
		{
			// handle the error
		}
		ifile.close();
	}
	return readbytes;
}



void Test()
{
	std::vector<unsigned char> output;
	for (int i = 0; i < 10000; ++i)
	{
		output.push_back(i);
	}
	const auto filename = "F:\\2018\\Coding\\Tester\\vsbuild\\IO\\sample.bin";
	if (write_data(filename,
		reinterpret_cast<char*>(output.data()),
		output.size()))
	{
		std::cout << "Successfully written to file" << std::endl;
	}

	
	unsigned char* input = nullptr;
	size_t readb = 0;

	auto inputData = [&input](size_t const length) {
		input = new unsigned char[length];
		return reinterpret_cast<char*>(input); 
	};

	if ((readb = read_data(filename,inputData)) > 0)
	{
		auto cmp = memcmp(output.data(), input, output.size());
		std::cout << (cmp == 0 ? "equal" : "not equal")
			<< std::endl;
	}
	delete[] input;
}

void testManipulators()
{
	std::cout << std::boolalpha << true << std::endl; // true
	std::cout << false << std::endl; // false
	std::cout << std::noboolalpha << false << std::endl; // 0

	std::cout << std::right << std::setw(10) << "right"
		<< std::endl;
	std::cout << std::setw(10) << "text" << std::endl;
	std::cout << std::left << std::setw(10) << "left" << std::endl;

	std::cout << std::right
		<< std::setfill('.') << std::setw(10)
		<< "right" << std::endl;

}

void testTimeManipulators()
{
	auto now = std::chrono::system_clock::now();
	auto stime = std::chrono::system_clock::to_time_t(now);
	auto ltime = std::localtime(&stime);
	
	
	std::cout << " stime time is : " << stime << std::endl;
	std::cout << " ltime time is : " << ltime << std::endl;
	
	std::cout << std::put_time(ltime, "%c") << std::endl;
	std::cout << std::put_time(ltime, "%F") << std::endl;
	// 2016-12-04
	std::cout << std::put_time(ltime, "%T") << std::endl;
	// 05:26:47
	std::cout << std::put_time(ltime, "%FT%T%z") << std::endl;
	// 2016-12-04T05:26:47+0900
	std::cout << std::put_time(ltime, "%Y-W%V") << std::endl;
	// 2016-W48
	std::cout << std::put_time(ltime, "%Y-W%V-%u") << std::endl;
	// 2016-W48-7
	std::cout << std::put_time(ltime, "%Y-%j") << std::endl;
	// 2016-339
	
}

int main(int argc, char *argv[])
{

	std::cout<<"testing Containers "<<std::endl;
	//Test();
	//testManipulators();
	//testTimeManipulators();
	TestCSVReader();
}
