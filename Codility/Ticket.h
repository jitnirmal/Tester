#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
//https://stackoverflow.com/questions/40559246/find-minimum-cost-of-tickets

int calculateMinCost(std::vector<int>& arr) {
	//std::map<int, int> DayAndTicket;

	bool isDayWithTrip[31] = { false };
	for (auto& dayWithTrip : arr) {
		isDayWithTrip[dayWithTrip] = true;
	}

	int minCostUpThroughDay[31] = { 0 };
	minCostUpThroughDay[0] = 0;
	//If there's no trip on day d, then MC(d) = MC(d − 1).
	for (int d = 1; d <= 30; ++d) {
		if (isDayWithTrip[d] == false) {
			minCostUpThroughDay[d] = minCostUpThroughDay[d - 1];
			continue;
		}

		int minCost;
		// Possibility #1: one-day pass on day d:
		minCost = minCostUpThroughDay[d - 1] + 2;
		//std::cout << "d=" << d << " || -----------------" << std::endl;

		// Possibility #2: seven-day pass ending on or after day d:
		// here we check current cost vs ( going 7 days in past, check the price that day + 7 day pass cost)
		int prevD = std::max(0, d - 7);
		minCost = std::min(minCost, minCostUpThroughDay[prevD] + 7);

		/*
		for (int prevD = std::max(0, d - 7); prevD <= d - 4; ++prevD) {
		minCost = std::min(minCost, minCostUpThroughDay[prevD] + 7);
		std::cout << "minCost=" << minCost << " ,minCostUpThroughDay[prevD]+7 =" << minCostUpThroughDay[prevD] + 7 << std::endl;
		}
		*/

		// Possibility #3: 30-day pass for the whole period:
		minCost = std::min(minCost, 25);
		minCostUpThroughDay[d] = minCost;
	}
	return minCostUpThroughDay[30];
}

void  TestCalculateMinCost()
{
	bool mismatch(false);
	//	std::vector<int> days = { 1,2,3,4,6,7,8,9,10,11,12,18,28,30 };
	//	std::vector<int> days = { 1};
	//	std::vector<int> days = { 1,2,3,4,5,6,7,8,9};
	std::vector<int> days = { 1,2,3,4,5,6,7,8,9 };
	int value = calculateMinCost(days);

}