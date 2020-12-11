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
                    bool found_adj = false;
                    for(int k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--) {
                        if(seats[k][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;

                    for(int l = j - 1; l >= 0; l--) {
                        if(seats[i][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[i][l] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;
                    for(int k = i + 1, l = j - 1; k < seats.size() && l >= 0; k++, l--) {
                        if(seats[k][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;
                    for(int k = i - 1; k >= 0; k--) {
                        if(seats[k][j] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][j] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;
                    for(int k = i + 1; k < seats.size(); k++) {
                        if(seats[k][j] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][j] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;
                    for(int k = i - 1, l = j + 1; k >= 0 && l < seats[i].length(); k--, l++) {
                        if(seats[k][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    if(found_adj) continue;

                    found_adj = false;
                    for(int k = i + 1, l = j + 1; k < seats.size() && l < seats[i].length(); k++, l++) {
                        if(seats[k][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    if(found_adj) continue;
                    
                    found_adj = false;
                    for(int l = j + 1; l < seats[i].length(); l++) {
                        if(seats[i][l] == '#') {
                            found_adj = true; 
                            break;
                        } else if(seats[i][l] == 'L') break;
                    }

                    if(found_adj) continue;

                    tmp_seats[i][j] = '#';
                    changed = true;                    
                } else if(seats[i][j] == '#') {
                    int adjacent = 0;

                    for(int k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--) {
                        if(seats[k][l] == seats[i][j]) {
                            adjacent++; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    for(int l = j - 1; l >= 0; l--) {
                        if(seats[i][l] == seats[i][j]) {
                            adjacent++;
                            break;
                        } else if(seats[i][l] == 'L') break;
                    }

                    for(int k = i + 1, l = j - 1; k < seats.size() && l >= 0; k++, l--) {
                        if(seats[k][l] == seats[i][j]) {
                            adjacent++; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    for(int k = i - 1; k >= 0; k--) {
                        if(seats[k][j] == seats[i][j]) {
                            adjacent++;
                            break;
                        } else if(seats[k][j] == 'L') break;
                    }

                    for(int k = i + 1; k < seats.size(); k++) {
                        if(seats[k][j] == seats[i][j]) {
                            adjacent++;
                            break;
                        } else if(seats[k][j] == 'L') break;
                    }

                    for(int k = i - 1, l = j + 1; k >= 0 && l < seats[i].length(); k--, l++) {
                        if(seats[k][l] == seats[i][j]) {
                            adjacent++; 
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    for(int k = i + 1, l = j + 1; k < seats.size() && l < seats[i].length(); k++, l++) {
                        if(seats[k][l] == seats[i][j]) {
                            adjacent++;
                            break;
                        } else if(seats[k][l] == 'L') break;
                    }

                    for(int l = j + 1; l < seats[i].length(); l++) {
                        if(seats[i][l] == seats[i][j]) {
                            adjacent++;
                            break;
                        } else if(seats[i][l] == 'L') break;
                    }
                    
                    if(adjacent >= 5) {
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