#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

vector<unsigned long long> getPos(string byte_num) {
    vector<string> v;
    
    if(byte_num[0] == 'X') {
        v.push_back("0");
        v.push_back("1");
    } else {
        v.push_back(string(1, byte_num[0]));
    }

    for(int i = 1; i < byte_num.length(); i++) {
        vector<string> tmp_v;
    
        for(size_t j = 0; j < v.size(); j++) {
            if(byte_num[i] == 'X') {
                tmp_v.push_back(v[j] + "0");
                tmp_v.push_back(v[j] + "1");
            } else {
                tmp_v.push_back(v[j] + byte_num[i]);
            }
        }

        v = tmp_v;
    }

    vector<unsigned long long> pos;
    for(size_t i = 0; i < v.size(); i++) {
        unsigned long long val = stoull(v[i], 0, 2); 
        pos.push_back(val);
    }
    return pos;
}

int main() {
    ifstream f;
    f.open("input.txt");

    string mask;
    getline(f, mask);
    mask = mask.substr(mask.find('=') + 2);

    string line;
    unordered_map<unsigned long long, unsigned long long> mem;

    while(!f.eof()) {
        getline(f, line);

        int pos = line.find('[');

        if(pos == string::npos) { // new mask
            mask = line.substr(line.find('=') + 2);
            continue;
        }

        line = line.substr(pos + 1);
  
        string mem_pos = line.substr(0, line.find(']'));
        
        string bit_pos = bitset<36>(stoull(mem_pos)).to_string();
        
        line = line.substr(line.find('=') + 2);
      
        unsigned long long num = stoull(line);
        
        for(int i = mask.length() - 1; i >= 0; i--) {
            if(mask[i] == '0') continue;
            else {
                bit_pos[i] = mask[i];
            }
        }

        vector<unsigned long long> memPosVec = getPos(bit_pos);

        for(size_t i = 0; i < memPosVec.size(); i++) {
            auto it = mem.find(memPosVec[i]);

            if(it == mem.end()) {
                mem.insert(make_pair(memPosVec[i], num));
            } else {
                (*it).second = num;
            }
        }
    }

    f.close();

    unsigned long long result = 0;

    for(auto it = mem.begin(); it != mem.end(); it++) { 
        result += (*it).second;
    }

    cout << result << endl;

    return 0;
}