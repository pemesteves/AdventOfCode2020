#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <bitset>

using namespace std;

vector<pair<int, int>> getMaskVec(string mask) {
    mask = mask.substr(mask.find('=') + 2);

    vector<pair<int, int>> mask_nums;

    for(int i = 0; i < mask.length(); i++) {
        if (mask[i] != 'X') {
            mask_nums.push_back(make_pair(mask.length() - i - 1, mask[i] - '0'));
        }
    }

    return mask_nums;
}

int main() {
    ifstream f;
    f.open("input.txt");

    string mask;
    getline(f, mask);

    vector<pair<int, int>> mask_nums = getMaskVec(mask);

    string line;
    unordered_map<unsigned int, unsigned long long> mem;

    while(!f.eof()) {
        getline(f, line);

        int pos = line.find('[');

        if(pos == string::npos) { // new mask
            mask = line;
            mask_nums = getMaskVec(mask);
            continue;
        }

        line = line.substr(pos + 1);
  
        unsigned int mem_pos = stoi(line.substr(0, line.find(']')));

        line = line.substr(line.find('=') + 2);
      
        unsigned long long num = stoi(line);

        string byte_num = bitset<64>(num).to_string();

        for(size_t i = 0; i < mask_nums.size(); i++) {
            byte_num[byte_num.length() - mask_nums[i].first - 1] = mask[mask.length() - 1 - mask_nums[i].first];
        }
        
        auto it = mem.find(mem_pos);
        unsigned long long byte = stoull(byte_num, 0, 2);

        if(it == mem.end()) {
            mem.insert(make_pair(mem_pos, byte));
        } else {
            (*it).second = byte;
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