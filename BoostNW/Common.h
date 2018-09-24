#pragma once
#include <string>
#include <mutex>


std::mutex printMutex;

auto printer = [](const std::string& message)
{
	std::unique_lock<std::mutex> lg(printMutex);
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << this_id<< " : " << message << std::endl;
};