#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>

#define SOLUTION 248131121

using namespace std;

long long findSumMinMax(list<long long> &nums, list<long long>::iterator it1, list<long long>::iterator it2) {
    long long min = *it1;
    it1++;
    long long max = *it1;
    if(max < min) {
        long long tmp = max;
        max = min;
        min = tmp;
    }
    it1++;
    if(!(it1 != it2)) return min + max;

    for(; it1 != it2; it1++) {
        if(*it1 < min) {
            min = *it1;
        } else if(*it1 > max) {
            max = *it1;
        }
    }

    if(*it1 < min) {
        min = *it1;
    } else if (*it1 > max) {
        max = *it1;
    }

    return min + max;
}

int main() {
    ifstream f;
    f.open("input.txt");

    list<long long> nums;
    long long x;

    while(!f.eof()) {
        f >> x;
        nums.push_back(x);
    }

    f.close();

    for(auto it = nums.begin(); it != nums.end(); it++) {
        long long sum = *it;
        
        auto it1 = it; it1++;
        for(; it1 != nums.end(); it1++) {
            sum += *it1;
            if(sum == SOLUTION) {
                cout << findSumMinMax(nums, it, it1) << endl;
                return 0;
            } else if (sum > SOLUTION) {
                break;
            }
        }
    }

    return 0;
}