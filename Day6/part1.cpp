#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getNumAnswers(vector<bool> v) {
    int result = 0;
    for(size_t i = 0; i < v.size(); i++){
        if(v[i]) result++;
    }
    return result;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    int result = 0;

    string line;

    vector<bool> answers = vector<bool>(26, false);
    while(!f.eof()) {
        getline(f, line);

        if(line.size() == 0) {
            result += getNumAnswers(answers);

            answers = vector<bool>(26, false);
            continue;
        }

        for(int i = 0; i < line.length(); i++) {
            answers[line[i] - 'a'] = true;
        }

    }

    f.close();

    result += getNumAnswers(answers);

    cout << result << endl;

    return 0;
}