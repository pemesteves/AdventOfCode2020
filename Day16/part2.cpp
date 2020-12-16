#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    unordered_map<int, set<string>> nums;

    while(!f.eof()) {
        getline(f, line);
        
        if(line.size() == 0) continue;

        if(line == "your ticket:") {
            break;
        }

        string property;

        size_t pos = line.find(':');

        property = line.substr(0, pos);
        line = line.substr(pos + 2);

        pos = line.find('-');
        int min = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(' ');
        int max = stoi(line.substr(0, pos));

        for(int i = min; i <= max; i++) {
            auto it = nums.find(i);
            if(it == nums.end()) {
                nums.insert(make_pair(i, set<string>({property})));
            } else {
                (*it).second.insert(property);
            }
        }

        line = line.substr(pos+4);
        
        pos = line.find('-');
        min = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        max = stoi(line);

        for(int i = min; i <= max; i++) {
            auto it = nums.find(i);
            if(it == nums.end()) {
                nums.insert(make_pair(i, set<string>({property})));
            } else {
                (*it).second.insert(property);
            }
        }
    }
    
    getline(f, line); //my ticket 

    vector<int> my_ticket;
    size_t pos;
    int num;

    do {
        pos = line.find(',');
        num = stoi(line.substr(0, pos));

        my_ticket.push_back(num);

        line = line.substr(pos + 1);

    } while (pos != string::npos);

    getline(f, line); // empty line
    getline(f, line); // nearby tickets

    vector<vector<int>> tickets;

    while(!f.eof()) {
        getline(f, line);

        vector<int> ticket;        
        bool validTicket = true;

        do {
            pos = line.find(',');
            num = stoi(line.substr(0, pos));

            ticket.push_back(num);
            
            if(nums.find(num) == nums.end()) {
                validTicket = false;
                break;
            } 

            line = line.substr(pos + 1);

        } while (pos != string::npos);

        if(validTicket) tickets.push_back(ticket);
    }

    f.close();

    vector<set<string>> fields;
    set<string> used;
    bool single_values = true;
    for(size_t i = 0; i < my_ticket.size(); i++) {
        set<string> names = (*nums.find(my_ticket[i])).second;
        if(names.size() == 1) {
            fields.push_back(names);
            used.insert(*names.begin());
            continue;
        }
        
        for(size_t j = 0; j < tickets.size(); j++) {
            auto it = nums.find(tickets[j][i]);

            set<string> ticket_names((*it).second);
            
            set<string> tmp;
            for(auto it = ticket_names.begin(); it != ticket_names.end(); it++) {
                if(used.find(*it) != used.end()) continue;

                if(names.find(*it) != names.end()) {
                    tmp.insert(*it);
                }
            }

            names = tmp;
            if(names.size() == 1) {
                break;
            }
        }

        
        if(names.size() == 1) {
            fields.push_back(names);
            used.insert(*names.begin());
        } else {
            fields.push_back(names);
            single_values = false;
        }
    }

    while(!single_values) {
        single_values = true;

        for(size_t i = 0; i < fields.size(); i++){
            if(fields[i].size() == 1) continue;

            set<string> tmp;
            for(auto it = fields[i].begin(); it != fields[i].end(); it++) {
                if(used.find(*it) != used.end()) continue;

                tmp.insert(*it);
            }
            fields[i] = tmp;

            if(fields[i].size() == 1) used.insert(*fields[i].begin());
            else single_values = false;
        }
    }

    unsigned long long result = 1;

    for(size_t i = 0; i < fields.size(); i++) {
        string val = *fields[i].begin();

        if(val.find("departure") != string::npos) {
            result *= my_ticket[i];
        }
    }

    cout << result << endl;

    return 0;
}