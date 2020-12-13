#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    string line;

    int timestamp;
    int result = INT_MAX;
    int ID = 0;

    getline(f, line);
    timestamp = stoi(line);

    getline(f, line);

    size_t pos;

    do {
        pos = line.find(',');

        string tmp = line.substr(0, pos);
        if(tmp == "x") {
            line = line.substr(pos + 1);
            continue;
        }

        int n = stoi(tmp);

        for(int i = timestamp; i < result; i++) {
            if (i % n == 0) {
                result = i;
                ID = n;
                break;
            }
        }

        line = line.substr(pos + 1);
    } while (pos != string::npos);

    f.close();

    cout << (result - timestamp) * ID << endl;

    return 0;
}