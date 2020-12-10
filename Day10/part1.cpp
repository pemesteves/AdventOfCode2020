#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    set<int> set_nums;
    int x;

    while(!f.eof()) {
        f >> x;
        set_nums.insert(x);
    }

    f.close();

    int jolt_1 = 0, jolt_3 = 1;

    auto it = set_nums.begin();
    if(*it == 1) jolt_1 = 1;
    else if (*it == 3) jolt_3++;

    for(; it != set_nums.end(); it++) {
        auto it1 = it; it1++;
        
        if(*it1 - *it == 1) jolt_1++;
        else if (*it1 - *it == 3) jolt_3++;
    }

    cout << jolt_1 * jolt_3 << endl;

    return 0;
}