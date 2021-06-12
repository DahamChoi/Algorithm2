#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

unordered_map<char, char> quillindrom_table = {
    {'A','A'},{'B',' '},{'C',' '},{'D',' '},{'E','3'},
    {'F',' '},{'G',' '},{'H','H'},{'I','I'},{'J',' '},
    {'K',' '},{'L',' '},{'M','M'},{'N',' '},{'O','O'},
    {'P',' '},{'Q',' '},{'R',' '},{'S','2'},{'T','T'},
    {'U','U'},{'V','V'},{'W','W'},{'X','X'},{'Y','Y'},
    {'Z','5'},{'a',' '},{'b','d'},{'c',' '},{'d','b'},
    {'e',' '},{'f',' '},{'g',' '},{'h',' '},{'i','i'},
    {'j',' '},{'k',' '},{'l','l'},{'m','m'},{'n','n'},
    {'o','o'},{'p','q'},{'q','p'},{'r','7'},{'s',' '},
    {'t',' '},{'u','u'},{'v','v'},{'w','w'},{'x','x'},
    {'y',' '},{'z',' '},{'0','0'},{'1','1'},{'2','S'},
    {'3','E'},{'4',' '},{'5','Z'},{'6',' '},{'7','r'},
    {'8','8'},{'9',' '}
};

bool is_quillindrom(const string& str, const vector<char>& memory, int last) {
    int left = 0;
    while (left <= last) {
        if (last >= int(str.length())) {
            if (memory[left] == ' ') {
                return false;
            }
        }
        else {
            if (memory[left] != str[last]) {
                if (!isalpha(str[last])) {
                    return false;
                }

                if (memory[left] != (isupper(str[last]) ? tolower(str[last]) : toupper(str[last]))) {
                    return false;
                }
            }
        }

        ++left;
        --last;
    }

    return true;
}

string solution(string str) {
    vector<char> memory(str.length());
    for (int i = 0; i < int(str.length()); i++) {
        if (quillindrom_table[str[i]] == ' ' && isalpha(str[i])) {
            memory[i] = quillindrom_table[(isupper(str[i]) ? tolower(str[i]) : toupper(str[i]))];
        }
        else {
            memory[i] = quillindrom_table[str[i]];
        }

        if (memory[i] == ' ') {
            return "";
        }
    }

    for (int last = str.length() - 1; last <= str.length() * 2; last++) {
        if (is_quillindrom(str, memory, last)) {
            for (int i = 0; i < int(memory.size()); i++) {
                if (isalpha(str[i]) && quillindrom_table[str[i]] != memory[i]) {
                    str[i] = (isupper(str[i]) ? tolower(str[i]) : toupper(str[i]));
                }
            }

            for (int i = last - str.length(); i >= 0; i--) {
                str.push_back(memory[i]);
            }

            return str;
        }
    }

    return "";
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    string str; cin >> str;

    string answer_1 = solution(str);
    reverse(str.begin(), str.end());
    string answer_2 = solution(str);
    reverse(answer_2.begin(), answer_2.end());

    if (answer_1.empty() && answer_2.empty()) {
        assert(false);
        cout << -1;
        return 0;
    }

    if (answer_1.empty()) {
        assert(false);
        cout << answer_2;
        return 0;
    }

    if (answer_2.empty()) {
        assert(false);
        cout << answer_1;
        return 0;
    }
    
    if (answer_1.length() < answer_2.length()) {
        cout << answer_1;
    }
    else {
        cout << answer_2;
    }
    
    return 0;
}