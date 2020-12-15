#include <fstream>
#include "MemoryGame.h"

using namespace std;

void readFile(string fileName, vector<int> &nums, unordered_map<int, int> &last_pos) {
    ifstream f;
    f.open("input.txt");
    
    int n;
    int pos = 0;
    char c;

    while(!f.eof()) {
        f >> n >> c;
        nums.push_back(n);

        last_pos.insert(make_pair(n, pos));
        
        pos++;
    }
    
    f.close();
}

vector<int> getSolution(int numberSpoken, vector<int> nums, unordered_map<int, int> last_pos) {
    nums.push_back(0);
    while(nums.size() < numberSpoken) {
        int last_num = nums[nums.size() - 1];
        auto it = last_pos.find(last_num);
        if(it == last_pos.end()) {
            last_pos.insert(make_pair(last_num, nums.size() - 1));
            nums.push_back(0);
        } else {
            int diff = nums.size() - 1 - (*it).second;
            (*it).second = nums.size() - 1;
            nums.push_back(diff); 
        }
    }

    return nums;
}

int getSolution(int numberSpoken) {
    vector<int> nums;
    unordered_map<int, int> last_pos;

    readFile("input.txt", nums, last_pos);

    nums = getSolution(numberSpoken, nums, last_pos);

    return nums[nums.size() - 1];
}