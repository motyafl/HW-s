#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
class Solution {
	public:
	std::vector<int> twoSum(std::vector<int> &nums, int target) {
		std::vector<int> result;
		for(int i = 0; i < nums.size()-1; i++) {
			for (int n = i+1; n < nums.size(); n++) {
				if (nums[i] + nums[n] == target) {
					result = {i, n};
				}
			}
		}
		return result;
	}
};

int main()
{
	Solution mySolution;
	std::vector<int> numbers = {0, 3, 10, 5};
	int target {15};
	for (int i : mySolution.twoSum(numbers, target)) {
		std::cout << i << std::endl;
	}
}
