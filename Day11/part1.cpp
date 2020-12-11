#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");

    vector<string> seats;
    string line;

    while(!f.eof()) {
        getline(f, line);
        seats.push_back(line);
    }

    f.close();

    bool changed;

    do {
        changed = false;

        vector<string> tmp_seats = seats;

        for(int i = 0; i < seats.size(); i++) {
            for(int j = 0; j < seats[i].length(); j++) {
                if(seats[i][j] == '.') continue;

                int adjacent = 0;

                if(seats[i][j] == 'L') {
                    if(j - 1 >= 0) {
                        if(i - 1 >= 0 && seats[i-1][j-1] == '#') continue;
                        if(seats[i][j-1] == '#') continue;
                        if(i + 1 < seats.size() && seats[i+1][j-1] == '#') continue;
                    }
                    if(j + 1 < seats.size()) {
                        if(i - 1 >= 0 && seats[i-1][j+1] == '#') continue;
                        if(seats[i][j+1] == '#') continue;
                        if(i + 1 < seats.size() && seats[i+1][j+1] == '#') continue;
                    }
                    if(i - 1 >= 0 && seats[i-1][j] == '#') continue;
                    if(i + 1 < seats.size() && seats[i+1][j] == '#') continue;
                    
                    tmp_seats[i][j] = '#';
                    changed = true;                    

                } else if(seats[i][j] == '#') {
                    if(j - 1 >= 0) {
                        if(i - 1 >= 0 && seats[i-1][j-1] == seats[i][j]) adjacent++;
                        if(seats[i][j-1] == seats[i][j]) adjacent++;
                        if(i + 1 < seats.size() && seats[i+1][j-1] == seats[i][j]) adjacent++;
                    }
                    if(j + 1 < seats.size()) {
                        if(i - 1 >= 0 && seats[i-1][j+1] == seats[i][j]) adjacent++;
                        if(seats[i][j+1] == seats[i][j]) adjacent++;
                        if(i + 1 < seats.size() && seats[i+1][j+1] == seats[i][j]) adjacent++;
                    }
                    if(i - 1 >= 0 && seats[i-1][j] == seats[i][j]) adjacent++;
                    if(i + 1 < seats.size() && seats[i+1][j] == seats[i][j]) adjacent++;

                    if(adjacent >= 4) {
                        tmp_seats[i][j] = 'L';
                        changed = true;                    
                    }
                }
            }
        }

        seats = tmp_seats;
    }while(changed);

    int num_occ = 0;
    for(size_t i = 0; i < seats.size(); i++) {
        for(int j = 0; j < seats[i].length(); j++) {
            if(seats[i][j] == '#') num_occ++;
        }
    }

    cout << num_occ << endl;

    return 0;
}