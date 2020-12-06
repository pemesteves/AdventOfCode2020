#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getNumAnswers(vector<int> v, int num_ans) {
    int result = 0;
    for(size_t i = 0; i < v.size(); i++){
        if(v[i] == num_ans) result++;
    }
    return result;
}

int main() {
    ifstream f;
    f.open("input.txt");
    
    int result = 0;

    string line;

    vector<int> answers = vector<int>(26, 0);
    int group_size = 0;
    while(!f.eof()) {
        getline(f, line);

        if(line.size() == 0) {
            result += getNumAnswers(answers, group_size);

            group_size = 0;
            answers = vector<int>(26, 0);
            continue;
        }

        group_size++;
        for(int i = 0; i < line.length(); i++) {
            answers[line[i] - 'a']++;
        }
    }

    f.close();

    result += getNumAnswers(answers, group_size);

    cout << result << endl;

    return 0;
}