#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

unordered_map<string, int> num_bags;

int countBags(
    const unordered_map<string, vector<pair<int, string>>> &bags,
    const string &bag
) {
    auto it_n = num_bags.find(bag);
    if(it_n != num_bags.end()) return (*it_n).second;

    auto it = bags.find(bag);
    if(it == bags.end()) return 0;

    int n = 1;
    for(size_t i = 0; i < (*it).second.size(); i++) {
        n += countBags(bags, (*it).second[i].second) * (*it).second[i].first;
    }
    
    num_bags.insert(make_pair(bag, n));
    return n;
}

int main() {
    ifstream f;
    f.open("input.txt");

    unordered_map<string, vector<pair<int, string>>> bags;

    string line;

    while(!f.eof()) {
        getline(f, line);
    
        size_t pos = line.find("bags");
        string color = line.substr(0, pos - 1);

        line = line.substr(line.find("contain"));
        line = line.substr(line.find(" ")+1);

        if(line[0] == 'n') {
            bags.insert(make_pair(color, vector<pair<int, string>>()));
            continue;
        }

        do{
            pos = line.find(" ");
            int n = stoi(line.substr(0, pos));
            line = line.substr(pos+1);

            pos = line.find(" bag");
            string new_color = line.substr(0, pos);

            auto it = bags.find(color);
            if(it == bags.end()){
                bags.insert(make_pair(color, vector<pair<int, string>>(1, make_pair(n, new_color))));
            } else {
                (*it).second.push_back(make_pair(n, new_color));
            }

            pos = line.find(",");
            if(pos == string::npos) {
                break;
            }
            line = line.substr(pos + 2);
        }while(true);
    }

    f.close();

    string s = "shiny gold";
    
    cout << countBags(bags, s) - 1 << endl;

    return 0;
}