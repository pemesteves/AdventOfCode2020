#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

    int numTrees = 0;
    int posX = 0, posY = 0;

    posX = (posX + 3) % v[0].size();
    posY++;

    for(; posY < v.size(); posX = (posX + 3) % v[0].size(), posY++) {
        if(v[posY][posX] == '#')
            numTrees++;
    }

    cout << numTrees << endl;

    return 0;
}