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
        
        bool isValid = true;
        int occ = 0;
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == c) {
                occ++;
                
                if(occ > m2) {
                    isValid = false;
                    break;
                }
            }
        }

        if(isValid && m1 <= occ && occ <= m2) {
            validPasswords++;
        }
    }

    cout << validPasswords << endl;

    f.close();
    return 0;
}