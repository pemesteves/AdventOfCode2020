#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    vector<int> nums(1, 0);
    int x;

    while(!f.eof()) {
        f >> x;
        nums.push_back(x);
    }

    f.close();

    sort(nums.begin(), nums.end());

    nums.push_back(nums[nums.size()-1] + 3);
    
    vector<long long> ranges(nums.size(), nums.size());
    ranges[nums.size()-1] = 1;

    for(int i = nums.size() - 2; i >= 0; i--) {
        long long options = 0;
        if (i + 1 < nums.size() && (nums[i+1] - nums[i] <= 3)) {
            options += ranges[i+1];
        } 
        if (i + 2 < nums.size() && (nums[i+2] - nums[i] <= 3)) {
            options += ranges[i+2];
        }
        if(i + 3 < nums.size() && (nums[i+3] - nums[i] <= 3)) {
            options += ranges[i+3];
        }

        ranges[i] = options;
    }

    cout << ranges[0] << endl;

    return 0;
}