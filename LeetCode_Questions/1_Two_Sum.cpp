#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{
    vector<int> returnVector(2);
    int size=nums.size();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                returnVector.at(0) = i;
                returnVector.at(1) = j;
                return returnVector;
            }
        }
    }
    return returnVector;
}

int main()
{
    vector<int> nums = {3, 2, 4};
    int target = 6;

    vector<int> print = twoSum(nums, target);

    cout << endl;
    for (int i = 0; i < print.size(); i++)
    {
        cout << print.at(i);
    }
    cout << endl;
}