#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

char newDir(char c, int val, bool right) {
    val %= 360;
    if(right) {
        switch(c) {
            case 'N':
                if(val == 90) return 'E';
                if(val == 180) return 'S';
                if(val == 270) return 'W';
            case 'E':
                if(val == 90) return 'S';
                if(val == 180) return 'W';
                if(val == 270) return 'N';
            case 'S':
                if(val == 90) return 'W';
                if(val == 180) return 'N';
                if(val == 270) return 'E';
            case 'W':
                if(val == 90) return 'N';
                if(val == 180) return 'E';
                if(val == 270) return 'S';
        }
    } else {
        switch(c) {
            case 'N':
                if(val == 90) return 'W';
                if(val == 180) return 'S';
                if(val == 270) return 'E';
            case 'E':
                if(val == 90) return 'N';
                if(val == 180) return 'W';
                if(val == 270) return 'S';
            case 'S':
                if(val == 90) return 'E';
                if(val == 180) return 'N';
                if(val == 270) return 'W';
            case 'W':
                if(val == 90) return 'S';
                if(val == 180) return 'E';
                if(val == 270) return 'N';
        }
    }

    return c;
}

int main() {
    ifstream f;
    f.open("input.txt");

    string line;

    pair<int, int> pos = make_pair(0, 0);
    char dir = 'E';

    while(!f.eof()) {
        getline(f, line);
        char actionDir = line[0];
        int value = stoi(line.substr(1));
        
        if(actionDir == 'F') actionDir = dir;

        if(actionDir == 'N') {
            pos.second += value;
        } else if(actionDir == 'S') {
            pos.second -= value;
        } else if(actionDir == 'E') {
            pos.first += value;
        } else if(actionDir == 'W') {
            pos.first -= value;
        } else if(actionDir == 'R' || actionDir == 'L') {
            dir = newDir(dir, value, actionDir == 'R');
        }
    }

    f.close();

    cout << abs(pos.first) + abs(pos.second) << endl;

    return 0;
}