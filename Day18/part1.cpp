#include <fstream>
#include <iostream>
#include <string>

using namespace std;

unsigned long long evaluateExpression(string exp) {
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
            int expVal = evaluateExpression(exp.substr(1, i - 1));
            exp = exp.substr(i + 1);
            if(sum) result += expVal;
            else result *= expVal;
        }

        spacePos = exp.find(' ');
    } 

    return result;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    string line;

    unsigned long long result = 0;

    while(!f.eof()) {
        getline(f, line);
       
       result += evaluateExpression(line);
    }

    f.close();

    cout << result << endl;

    return 0;
}