#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    unordered_map<string, vector<string>> bags;

    string line;

    while(!f.eof()) {
        getline(f, line);
    
        size_t pos = line.find("bags");
        string color = line.substr(0, pos - 1);

        line = line.substr(line.find("contain"));
        line = line.substr(line.find(" ")+1);

        if(line[0] == 'n') continue;

        do{
            pos = line.find(" ");
            int n = stoi(line.substr(0, pos));
            line = line.substr(pos+1);

            pos = line.find(" bag");
            string new_color = line.substr(0, pos);

            auto it = bags.find(new_color);
            if(it == bags.end()){
                bags.insert(make_pair(new_color, vector<string>(1, color)));
            } else {
                (*it).second.push_back(color);
            }

            pos = line.find(",");
            if(pos == string::npos) {
                break;
            }
            line = line.substr(pos + 2);
        }while(true);
    }

    f.close();

    queue<string> q({"shiny gold"});
    unordered_set<string> str({"shiny gold"});

    while(!q.empty()) {
        string s = q.front();
        q.pop();

        auto it = bags.find(s);
        if(it == bags.end()) {
            continue;
        }
        vector<string> v = (*it).second;
        
        for(size_t i = 0; i < v.size(); i++) {
            if(str.find(v[i]) == str.end()) {
                str.insert(v[i]);
                q.push(v[i]);
            }
        }
    }

    cout << str.size() - 1 << endl;

    return 0;
}