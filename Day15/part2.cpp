#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    int n;
    int pos = 0;
    char c;

    vector<int> nums;
    unordered_map<int, int> last_pos;
    
    while(!f.eof()) {
        f >> n >> c;
        nums.push_back(n);

        last_pos.insert(make_pair(n, pos));
        
        pos++;
    }

    nums.push_back(0);
    while(nums.size() < 30000000) {
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

    f.close();

    cout << nums[nums.size() - 1] << endl;

    return 0;
}