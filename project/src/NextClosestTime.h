#pragma once

/*

681. Next Closest Time

Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

Example 1:
Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.

Example 2:
Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.

Approach: Brute Force.

Time Complexity: O(1). We all 4^4  possible times and take the best one.

Space Complexity: O(1).

Approach: Simulation COOL

Reference: https://leetcode.com/problems/next-closest-time/solution/

Simulate the clock going forward by one minute. Each time it moves forward, 
if all the digits are allowed, then return the current time.

The natural way to represent the time is as an integer t in the range 0 <= t < 24 * 60. 
Then the hours are t / 60, the minutes are t % 60, and each digit of the hours and 
minutes can be found by hours / 10, hours % 10 etc.

Complexity Analysis

Time Complexity: O(1)O(1). We try up to 24 * 6024∗60 possible times until we find the correct time.

Space Complexity: O(1)O(1).

*/

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
private:
	int stringTimeToInt(const string& time)
	{
		int result = 0;
		result += time[3] + time[2] * 10;
		result += (time[1] + time[0] * 10) * 60;

		return result;
	}

public:
	string nextClosestTime(string time)
	{
		string time_no_space;
		time_no_space.append(time.begin(), time.begin() + 2);
		time_no_space.append(time.begin() + 3, time.end());
		//cout << time_no_space << endl;

		vector<string> times;
		string new_time;
		for (int i0 = 0; i0 < 4; i0++)
		{
			for (int i1 = 0; i1 < 4; i1++)
			{
				for (int i2 = 0; i2 < 4; i2++)
				{
					for (int i3 = 0; i3 < 4; i3 ++)
					{
						new_time.clear();
						new_time.push_back(time_no_space[i0]);
						new_time.push_back(time_no_space[i1]);
						new_time.push_back(time_no_space[i2]);
						new_time.push_back(time_no_space[i3]);
						int hours = (new_time[0] - '0') * 10 + (new_time[1] - '0');
						int mininutes = (new_time[2] - '0') * 10 + (new_time[3] - '0');
						if(hours > 23 || mininutes > 59)	// prune invalid time
							continue;
						times.push_back(new_time);
					}
				}
			}
		}

		int nearst_time_id = 0;
		int nearest_distance = INT_MAX;
		for (int i = 0; i < times.size(); i++)
		{
			int curr_distance = stringTimeToInt(times[i]) - stringTimeToInt(time_no_space);
			if (curr_distance < 0)
				curr_distance += 24 * 60;
			if (curr_distance < nearest_distance && curr_distance != 0)
			{
				nearest_distance = curr_distance;
				nearst_time_id = i;
			}
		}

		string restult = times[nearst_time_id];
		restult.insert(restult.begin() + 2, ':');
		return restult;
	}

	string nextClosestTime_v2(string time)
	{
		int curr_time = 0;
		curr_time = stoi(string(time.begin(), time.begin() + 2)) * 60 + stoi(string(time.begin() + 3, time.end()));
		//cout << "curr_time = " << curr_time << endl;
		set<int> allowed;
		for (char c : time)
		{
			if (c != ':')
				allowed.insert(c - '0');
		}
		
		while (true)
		{
			curr_time = (curr_time + 1) % (24 * 60);
			vector<int> digits { curr_time / 60 / 10, curr_time / 60 % 10, curr_time % 60 / 10, curr_time % 60 % 10 };

			int i = 0;
			for (i = 0; i < digits.size(); i++)
			{
				if(allowed.find(digits[i]) == allowed.end())
					break;
			}
			if (i == digits.size())
			{
				return string { 
					static_cast<char> (digits[0] + '0'), 
					static_cast<char> (digits[1] + '0'), 
					':', 
					static_cast<char> (digits[2] + '0'), 
					static_cast<char> (digits[3] + '0') 
				};
			}
		}
	}
};

