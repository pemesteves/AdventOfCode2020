#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream f;
    f.open("input.txt");
    
    int result = 0;

    bool hasByr = false, hasIyr = false, hasEyr = false, hasHgt = false;
    bool hasHcl = false, hasEcl = false, hasPid = false; 

    string line;
    while(!f.eof()) {
        getline(f, line);

        size_t pos = line.find(':');
        while(pos != string::npos){
            string field = line.substr(0, pos);
            if(field == "byr")
                hasByr = true;
            else if(field == "iyr")
                hasIyr = true;
            else if(field == "eyr")
                hasEyr = true;
            else if(field == "hgt")
                hasHgt = true;
            else if(field == "hcl")
                hasHcl = true;
            else if(field == "ecl")
                hasEcl = true;
            else if(field == "pid")
                hasPid = true;

            pos = line.find(' ');
            if(pos == string::npos) 
                break;
            
            line = line.substr(pos+1);

            pos = line.find(':');
        }

        if(line.length() == 0) {
            if(hasByr && hasIyr && hasEyr && hasHgt && hasHcl && hasEcl && hasPid) {
                result++;
            }
            hasByr = false, hasIyr = false, hasEyr = false, hasHgt = false;
            hasHcl = false, hasEcl = false, hasPid = false; 
        }
    }

    f.close();

    cout << result << endl;

    return 0;
}