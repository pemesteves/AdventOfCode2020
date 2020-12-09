#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    unordered_set<int> set_nums;
    list<int> nums;
    int x;

    while(!f.eof()) {
        f >> x;
        if(nums.size() < 4) {
            nums.push_back(x);
            set_nums.insert(x);
        } else {
            bool found_value = false;
            for(auto it = nums.begin(); it != nums.end(); it++) {
                if(set_nums.find(x-(*it)) != set_nums.end()) {
                    found_value = true;
                    break;
                }
            }
            if(!found_value) {
                cout << x << endl;
                return 0;
            }
            set_nums.erase(nums.front());
            nums.pop_front();
            nums.push_back(x);
            set_nums.insert(x);
        }
    }

    f.close();

    return 0;
}