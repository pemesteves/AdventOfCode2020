#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    int result = 0;

    string line;
    while(!f.eof()) {
        getline(f, line);

        int row = 0, column = 0;
        int min_row = 0, max_row = 127;

        for(int i = 0; i < 7; i++) {
            if(line[i] == 'F') {
                max_row = min_row + (max_row - min_row)/2;
            } else { // line[i] == 'B'
                min_row = min_row + ((max_row - min_row) / 2) + 1;
            }
        }
        
        row = min_row;

        int min_col = 0, max_col = 7;
        for(int i = 7; i < 10; i++){
            if(line[i] == 'L') {
                max_col = min_col + (max_col - min_col)/2;
            } else { // line[i] == 'R'
                min_col = min_col + ((max_col - min_col) / 2) + 1;
            }
        }

        column = min_col;

        int tmp_res = row * 8 + column;
        
        if(tmp_res > result) result = tmp_res;
    }

    f.close();

    cout << result << endl;

    return 0;
}