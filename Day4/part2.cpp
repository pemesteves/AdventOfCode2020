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

    bool isInvalid = false;

    string line;
    while(!f.eof()) {
        getline(f, line);

        if(line.length() != 0 && isInvalid)
            continue;

        size_t pos = line.find(':');
        while(pos != string::npos){
            string field = line.substr(0, pos);

            size_t spacePos = line.find(' ');
            string value;

            if(spacePos == string::npos) {
                value = line.substr(pos + 1);
            } else {
                value = line.substr(pos + 1, spacePos - pos - 1);
            }

            if(field == "byr") {
                if(value.length() != 4) {
                    isInvalid = true;
                    break;
                }

                int byr = stoi(value);
                if(byr < 1920 || byr > 2002) {
                    isInvalid = true;
                    break;
                }

                hasByr = true;
            }
            else if(field == "iyr") {
                if(value.length() != 4) {
                    isInvalid = true;
                    break;
                }

                int iyr = stoi(value);
                if(iyr < 2010 || iyr > 2020) {
                    isInvalid = true;
                    break;
                }

                hasIyr = true;
            }
            else if(field == "eyr") {
                if(value.length() != 4) {
                    isInvalid = true;
                    break;
                }

                int eyr = stoi(value);
                if(eyr < 2020 || eyr > 2030) {
                    isInvalid = true;
                    break;
                }

                hasEyr = true;
            }
            else if(field == "hgt") {
                if(value.length() < 4 || value.length() > 5) {
                    isInvalid = true;
                    break;
                }

                string last2Chars = value.substr(value.length() - 2, 2);
                if(last2Chars == "cm") {
                    if(value.length() != 5) {
                        isInvalid = true;
                        break;
                    }
                    int hgt = stoi(value.substr(0, 3));
                    if(hgt < 150 || hgt > 193) {
                        isInvalid = true;
                        break;
                    }
                } else if (last2Chars == "in") {
                    if(value.length() != 4) {
                        isInvalid = true;
                        break;
                    }
                    int hgt = stoi(value.substr(0, 2));
                    if(hgt < 59 || hgt > 76) {
                        isInvalid = true;
                        break;
                    }
                } else {
                    isInvalid = true;
                    break;
                }

                hasHgt = true;
            }
            else if(field == "hcl") {
                if(value.length() != 7) {
                    isInvalid = true;
                    break;
                }

                if(value[0] != '#') {
                    isInvalid = true;
                    break;
                }

                for(int i = 1; i < value.length(); i++) {
                    if(!((value[i] <= '9' && value[i] >= '0')
                        || (value[i] <= 'f' && value[i] >= 'a'))) {
                        isInvalid = true;
                        break;
                    }
                }

                if(isInvalid) break;
                

                hasHcl = true;
            }
            else if(field == "ecl") {
                if(value.length() != 3) {
                    isInvalid = true;
                    break;
                }

                if(value != "amb" && value != "blu" && value != "brn" && value != "gry" 
                    && value != "grn" && value != "hzl" && value != "oth") {
                    isInvalid = true;
                    break;
                }

                hasEcl = true;
            }
            else if(field == "pid") {
                if(value.length() != 9) {
                    isInvalid = true;
                    break;
                }

                for(int i = 0; i < value.length(); i++) {
                    if(!(value[i] >= '0' && value[i] <= '9'))  {
                        isInvalid = true;
                        break;
                    }
                }

                if(isInvalid) break;

                hasPid = true;
            }

            if(spacePos == string::npos)
                break;

            line = line.substr(spacePos+1);

            pos = line.find(':');
        }
    
        if(line.length() == 0) {
            if(hasByr && hasIyr && hasEyr && hasHgt && hasHcl && hasEcl && hasPid) {
                result++;
            }
            hasByr = false, hasIyr = false, hasEyr = false, hasHgt = false;
            hasHcl = false, hasEcl = false, hasPid = false; 
            isInvalid = false;
        }
    }

    f.close();

    if(hasByr && hasIyr && hasEyr && hasHgt && hasHcl && hasEcl && hasPid) {
        result++;
    }

    cout << result << endl;

    return 0;
}