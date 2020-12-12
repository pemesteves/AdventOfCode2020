#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

pair<int, int> newDir(pair<int, int> waypoint, int val, bool right) {
    val %= 360;

    if(right) {
        if(val == 90)
            return make_pair(waypoint.second, - waypoint.first);
        else if(val == 180) 
            return make_pair(- waypoint.first, - waypoint.second);
        else if(val == 270) 
            return make_pair(- waypoint.second, waypoint.first);
    } else {
        if(val == 90)
            return make_pair(- waypoint.second, waypoint.first);
        else if(val == 180) 
            return make_pair(- waypoint.first, - waypoint.second);
        else if(val == 270) 
            return make_pair(waypoint.second, - waypoint.first);
    }
    return waypoint;
}

int main() {
    ifstream f;
    f.open("input.txt");

    string line;

    pair<int, int> pos = make_pair(0, 0);
    pair<int, int> waypoint = make_pair(10, 1);

    while(!f.eof()) {
        getline(f, line);
        char actionDir = line[0];
        int value = stoi(line.substr(1));
        
        if(actionDir == 'F'){
            pos = make_pair(
                pos.first + waypoint.first * value, 
                pos.second + waypoint.second * value
            );  
        } else if(actionDir == 'N') {
            waypoint.second += value;
        } else if(actionDir == 'S') {
            waypoint.second -= value;
        } else if(actionDir == 'E') {
            waypoint.first += value;
        } else if(actionDir == 'W') {
            waypoint.first -= value;
        } else if(actionDir == 'R' || actionDir == 'L') {
            waypoint = newDir(waypoint, value, actionDir == 'R');
        }
    }

    f.close();

    cout << abs(pos.first) + abs(pos.second) << endl;

    return 0;
}