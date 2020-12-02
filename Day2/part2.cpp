#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    char c, tmp;
    int m1, m2;
    string s;
    
    int validPasswords = 0;

    while(!f.eof()) {
        f >> m1 >> tmp >> m2 >> c >> tmp >> s;
        
        if(m1 > s.length()) {
            continue;
        }
        
        int occ = s[m1-1] == c ? 1 : 0;

        if(m2 <= s.length() && s[m2-1] == c) {
            occ++;
        }


        if(occ == 1) {
            validPasswords++;
        }
    }

    cout << validPasswords << endl;

    f.close();
    return 0;
}