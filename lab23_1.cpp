#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

char score2grade(int score) {
    if (score >= 80) return 'A';
    if (score >= 70) return 'B';
    if (score >= 60) return 'C';
    if (score >= 50) return 'D';
    return 'F';
}

string toUpperStr(string x) {
    for (char &c : x) c = toupper(c);
    return x;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file.\n";
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, temp;
        int score1, score2, score3;

        getline(ss, name, ':'); 
        ss >> score1 >> score2 >> score3; 
        
        int totalScore = score1 + score2 + score3;
        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }

    file.close();
}

void getCommand(string &command, string &key) {
    cout << "Please input your command: " << endl;
    cin >> command;
    getline(cin, key);
    
    if (!key.empty() && key[0] == ' ') {
        key = key.substr(1);
    } else {
        key = "";
    }
}


void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == toUpperStr(key)) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    cout << "---------------------------------\n";
    for (size_t i = 0; i < names.size(); i++) {
        if (grades[i] == toupper(key[0])) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main() {
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    while (true) {
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        
        if (command == "EXIT") break;
        else if (command == "GRADE") searchGrade(names, scores, grades, key);
        else if (command == "NAME") searchName(names, scores, grades, key);
        else {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }

    return 0;
}
