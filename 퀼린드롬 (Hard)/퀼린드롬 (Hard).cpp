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

vector<int> getPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0);

    int begin = 1, matched = 0;
    while (begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0) {
                ++begin;
            }
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return pi;
}

vector<int> getprefixMatch(const string& s) {
    vector<int> ret, pi = getPartialMatch(s);
    int k = s.size();
    while (k > 0) {
        ret.push_back(k);
        k = pi[k - 1];
    }
    return ret;
}

int solution(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while (begin < n) {
        if (matched < m && a[begin + matched] == b[matched]) {
            ++matched;
            if (begin + matched == n) {
                return matched;
            }
        }
        else {
            if (matched == 0) {
                ++begin;
            }
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return 0;
}

int main() {
    auto func = [&](const char c) {
        if (quillindrom_table[c] == ' ') {
            return isupper(c) ? quillindrom_table[tolower(c)] : quillindrom_table[toupper(c)];
        }
        return quillindrom_table[c];
    };

    string str; cin >> str;

    string sub_str_1(str.rbegin(), str.rend());
    transform(sub_str_1.begin(), sub_str_1.end(), sub_str_1.begin(), func);
    string fix_str_1 = str;
    for (int i = 0; i < int(fix_str_1.length()); i++) {
        if (quillindrom_table[fix_str_1[i]] == ' ') {
            fix_str_1[i] = isupper(fix_str_1[i]) ? tolower(fix_str_1[i]) : toupper(fix_str_1[i]);
            if (quillindrom_table[fix_str_1[i]] == ' ') {
                cout << -1;
                return 0;
            }
        }
    }

    int answer_length_1 = str.length() - (solution(fix_str_1, sub_str_1));

    string fix_str_2 = fix_str_1;
    reverse(fix_str_2.begin(), fix_str_2.end());

    string sub_str_2(fix_str_2.rbegin(), fix_str_2.rend());
    transform(sub_str_2.begin(), sub_str_2.end(), sub_str_2.begin(), func);

    int answer_length_2 = str.length() - (solution(fix_str_2, sub_str_2));

    if (answer_length_1 < answer_length_2) {
        cout << fix_str_1;
        cout << sub_str_1.substr(str.length() - answer_length_1, answer_length_1);
    }
    else {
        cout << sub_str_1.substr(0, answer_length_2);
        cout << fix_str_1;
    }

    return 0;
}