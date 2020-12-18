#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

unsigned long long evaluateExpression(string exp) {
    while(exp[0] == ' ') exp = exp.substr(1);

    int numPar = 0;
    unsigned long long result = 0; 
    
    if(isdigit(exp[0])) {
        size_t pos_space = exp.find(' ');
        result = stoi(exp.substr(0, pos_space));
        exp = exp.substr(pos_space + 1);
    } else if(exp[0] == '(') {
        int i = 1;
        numPar++;
        for(; i < exp.length(); i++) {
            if(exp[i] == '(') {
                numPar++;
            } else if(exp[i] == ')') {
                numPar--;
                if(numPar == 0) break;
            }
        }
        result = evaluateExpression(exp.substr(1, i - 1));
        exp = exp.substr(i + 1);
    } else {
        cout << exp[0] << endl;
        return 0;
    }

    size_t spacePos = exp.find(' ');

    bool sum = true;

    while(spacePos != string::npos) {
        while(exp[0] == ' ') exp = exp.substr(1);

        if(exp[0] == '+') {
            sum = true;
            exp = exp.substr(1);
        } else if(exp[0] == '*') {
            sum = false;
            exp = exp.substr(1);
        } else if(isdigit(exp[0])) {
            spacePos = exp.find(' ');
            int num;
            if(spacePos == string::npos) {
                num = stoi(exp);
            } else {
                num = stoi(exp.substr(0, spacePos));
            }
            if(sum) result += num;
            else result *= num;
            
            exp = exp.substr(spacePos + 1);
        } else if(exp[0] == '(') {
            int i = 1;
            numPar++;
            for(; i < exp.length(); i++) {
                if(exp[i] == '(') {
                    numPar++;
                } else if(exp[i] == ')') {
                    numPar--;
                    if(numPar == 0) break;
                }
            }
            unsigned long long expVal = evaluateExpression(exp.substr(1, i - 1));
            exp = exp.substr(i + 1);
            if(sum) result += expVal;
            else result *= expVal;
        }

        spacePos = exp.find(' ');
    } 
    return result;
}

string getPrecedenceLevels(string exp) {
    string tmp = exp;

    size_t lastExpPos = 0;
    
    for(int i = 0; i < tmp.length();) {
        if(tmp[i] == '+') {
            int j;
            if(isdigit(tmp[i-2])) {
                j = i - 2;
                for(; j >= 0; j--) {
                    if(!isdigit(tmp[j])) break;
                }
            } else if (tmp[i - 2] == ')') {
                int numPar = 1;
                j = i - 3;
                
                for(; j >= 0; j--) {
                    if(tmp[j] == '(') {
                        numPar--;
                        if(numPar == 0) break;
                    } else if(tmp[j] == ')') {
                        numPar++;
                    }
                }
            }

            int k;
            if(isdigit(tmp[i+2])) {
                k = i + 2;
                for(; k < tmp.length(); k++) {
                    if(!isdigit(tmp[k])) break;
                }
            } else if (tmp[i + 2] == '(') {
                int numPar = 1;
                k = i + 3;
                for(; k < tmp.length(); k++) {
                    if(tmp[k] == '(') {
                        numPar++;
                    } else if(tmp[k] == ')') {
                        numPar--;
                        if(numPar == 0) break;
                    }
                }
            }

            ostringstream oss;
            
            if(j < 0) {
                oss << "(" << tmp.substr(0, i);
            } else {
                oss << tmp.substr(0, j) << "(" << tmp.substr(j, i - j);
            }

            oss << "+";

            if(k == tmp.size()) {
                oss << tmp.substr(i + 1) << ")";
            } else {
                oss << tmp.substr(i + 1, k - i - 1) << ")" << tmp.substr(k);
            }

            tmp = oss.str();

            i += 2;
        } else {
            i++;
        }
    }

    return tmp;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    unsigned long long result = 0;

    while(!f.eof()) {
        getline(f, line);
       
        string exp = getPrecedenceLevels(line);
        
        result += evaluateExpression(exp);
    }

    f.close();

    cout << result << endl;

    return 0;
}