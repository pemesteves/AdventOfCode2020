#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    vector<bool> v(2020, false);

    int n;
    while(!f.eof()) {
        f >> n;

        if(v[2020-n]) {
            cout << n * (2020 - n) << endl;
            break;
        }
        v[n] = true;
    }

    f.close();
    return 0;
}