#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int checkNumTrees(int incX, int incY, vector<string> &v) {
    int numTrees = 0;
    int posX = incX % v[0].size(), posY = incY;

    for(; posY < v.size(); posX = (posX + incX) % v[0].size(), posY += incY) {
        if(v[posY][posX] == '#')
            numTrees++;
    }

    return numTrees;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    vector<string> v;

    string line;
    while(!f.eof()) {
        getline(f, line);
        v.push_back(line);
    }

    f.close();

    long long result = 276; // Result from the part 1
    
    result *= checkNumTrees(1, 1, v);
    result *= checkNumTrees(5, 1, v);
    result *= checkNumTrees(7, 1, v);
    result *= checkNumTrees(1, 2, v);

    cout << result << endl;

    return 0;
}