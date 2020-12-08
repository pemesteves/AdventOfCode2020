#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getAccumulator(vector<pair<string, bool>> &code) {
    string line;
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

    return accumulator;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    vector<pair<string, bool>> code;
    while(!f.eof()) {
        getline(f, line);
        code.push_back(make_pair(line, false));
    }

    f.close();

    int accumulator = 0;

    for(size_t i = 0; i < code.size(); i++) {
        line = code[i].first;
        string op = line.substr(0, 3);

        if(op == "acc") continue;

        vector<pair<string, bool>> v = code;

        if(op == "nop") {
            v[i].first[0] = 'j';
            v[i].first[1] = 'm';
            v[i].first[2] = 'p';
        } else if(op == "jmp") {
            v[i].first[0] = 'n';
            v[i].first[1] = 'o';
            v[i].first[2] = 'p';
        }

        accumulator = getAccumulator(v);

        if(v[v.size()-1].second) break;
    }

    cout << accumulator << endl;

    return 0;
}