#include <fstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    set<int> nums;

    while(!f.eof()) {
        getline(f, line);
        
        if(line.size() == 0) continue;

        if(line == "your ticket:") {
            getline(f, line); //my ticket 
            continue;
        }

        if(line == "nearby tickets:") break;

        line = line.substr(line.find(':') + 2);

        size_t pos = line.find('-');
        int min = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(' ');
        int max = stoi(line.substr(0, pos));

        for(int i = min; i <= max; i++) {
            nums.insert(i);
        }

        line = line.substr(pos+4);
        
        pos = line.find('-');
        min = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        max = stoi(line);

        for(int i = min; i <= max; i++) {
            nums.insert(i);
        }
    }
    

    int result = 0; 
    int num;
    while(!f.eof()) {
        getline(f, line);

        size_t pos;
        
        do {
            pos = line.find(',');
            num = stoi(line.substr(0, pos));

            if(nums.find(num) == nums.end()) {
                result += num;
            } 

            line = line.substr(pos + 1);

        } while (pos != string::npos);

    }

    f.close();

    cout << result << endl;

    return 0;
}