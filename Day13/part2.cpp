#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    string line;

    getline(f, line);
    getline(f, line);

    vector<pair<int, int>> buses;

    size_t pos;
    int it = 0;

    do {
        pos = line.find(',');

        string tmp = line.substr(0, pos);
        if(tmp == "x") {
            line = line.substr(pos + 1);
            it++;
            continue;
        }
        
        int n = stoi(tmp);

        buses.push_back(make_pair(n, it));

        line = line.substr(pos + 1);
        it++;
    } while (pos != string::npos);

    f.close();

    long long result = 0;

    long long inc = buses[0].first;

    for(size_t i = 1; i < buses.size(); i++) {
        while (true) {
            result += inc;
            if((result + buses[i].second) % buses[i].first == 0) {
                inc *= buses[i].first;
                break;
            }
        }
    }

    cout << result << endl;

    return 0;
}
