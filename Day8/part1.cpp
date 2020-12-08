#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    vector<pair<string, bool>> code;
    while(!f.eof()) {
        getline(f, line);
        code.push_back(make_pair(line, false));
    }

    int accumulator = 0;

    for(size_t i = 0; i >= 0 && i < code.size();) {
        if(code[i].second) break;
        
        code[i].second = true;
        
        line = code[i].first;
        string op = line.substr(0, 3);
        int n = stoi(line.substr(4));
        
        if(op == "nop") {
            i++;
            continue;
        }

        if(op == "acc") {
            accumulator += n;
            i++;
            continue;
        }

        if(op == "jmp") {
            i += n;
        }
    }

    f.close();

    cout << accumulator << endl;

    return 0;
}