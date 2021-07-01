#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> processString(string s) {
    size_t pos = s.find(' ');
    vector<string> v;
    string s1 = "";

    while(pos != string::npos) {
        string tmp = s.substr(0, pos);

        if(tmp[0] == '"') {
            s1 += string(1, tmp[1]) + " ";
        } else if(tmp[0] == '|') {
            v.push_back(s1);
            s1 = "";
        } else {
            s1 += tmp + " ";
        }

        s = s.substr(pos + 1);
        pos = s.find(' ');
    }

    if(s[0] == '"') {
        s1 += string(1, s[1]);
    } else {
        s1 += s;
    }

    v.push_back(s1);
    
    return v;
}

bool hasNum(string s) {
    size_t pos = s.find(' ');
    while(pos != string::npos) {
        string s1 = s.substr(0, pos);
        s = s.substr(pos + 1);

        if(isdigit(s1[0])) return true;

        pos = s.find(' ');
    }
    
    if(isdigit(s[0])) return true;

    return false;
}

bool hasNum(vector<string> r) {
    for(size_t i = 0; i < r.size(); i++) {
        if(hasNum(r[i])) return true;
    }

    return false;
}

bool matchRule(const unordered_map<int, vector<string>> &rules, const int ruleNum, string &s) {
    vector<string> rule = rules.find(ruleNum)->second;

    for(size_t i = 0; i < rule.size(); i++) {
        string tmp = s;
        bool matched = true;

        for(int j = 0; j < rule[i].length(); j++) {

            if(isdigit(rule[i][j])) {
                size_t pos = rule[i].find(' ', j);
                int newRuleNum;

                if(pos == string::npos) {
                    newRuleNum = stoi(rule[i].substr(j));
                } else {
                    newRuleNum = stoi(rule[i].substr(j, pos - j));
                }
                
                if(!matchRule(rules, newRuleNum, tmp)) { 
                    matched = false;
                    break;
                }

                if(pos == string::npos) break;

                j = pos;
            } else if(isalpha(rule[i][j])) {
                if(tmp[0] != rule[i][j]) { 
                    matched = false;
                    break;
                }

                tmp = tmp.substr(1);
            }
        }
        
        if(matched) {
            s = tmp;
            return true;
        }
    }

    return false;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    unordered_map<int, vector<string>> rules;

    while(!f.eof()) {
        getline(f, line);
        if(line.length() == 0) break;

        size_t pos = line.find(':');
        int ruleNum = stoi(line.substr(0, pos));

        line = line.substr(pos + 2);
        vector<string> vec = processString(line);

        rules.insert(make_pair(ruleNum, vec));
    }

    rules.find(8)->second.push_back("42 8");
    rules.find(11)->second.push_back("42 11 31");

    unsigned int result = 0;

    while(!f.eof()) {
        getline(f, line); 

        if(matchRule(rules, 0, line)) {
            result++;
        }
    }
    
    f.close();

    cout << result << endl;

    return 0;
}