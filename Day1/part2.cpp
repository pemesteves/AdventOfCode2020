#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    vector<bool> v(2020, false);
    vector<int> v1;

    int n;
    while(!f.eof()) {
        f >> n;

        v[n] = true;
        v1.push_back(n);
    }

    for(size_t i = 0; i < v1.size(); i++) {
        for(size_t j = i + 1; j < v1.size(); j++) {
            if(v1[i] + v1[j] > 2020) continue;
            
            if(v[2020-v1[i]-v1[j]]) {
                cout << v1[i] * v1[j] * (2020 - v1[i] - v1[j]) << endl;
                
                f.close();
                return 0;
            }
        }
    }

    f.close();
    return 0;
}