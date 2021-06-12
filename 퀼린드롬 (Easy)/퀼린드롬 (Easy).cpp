#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

string make_quillindrom(const string& str, int left, int right) {
    string mid;
    if (right - left == 2) {
        char c = str[right - 1];
        if (c != quillindrom_table[c]) {
            if (toupper(c) == quillindrom_table[toupper(c)]) {
                c = toupper(c);
            }
            else {
                c = tolower(c);
            }
        }
        mid += c;
    }

    string left_str, right_str;
    while (left >= 0) {
        left_str += str[left];
        right_str += right < str.length() ? str[right] : quillindrom_table[str[left]];
        if (right_str.back() == ' ' || quillindrom_table[left_str.back()] != right_str.back()) {
            char upper_left = toupper(left_str.back());
            char upper_right = quillindrom_table[toupper(left_str.back())];
            char lower_left = tolower(left_str.back());
            char lower_right = quillindrom_table[tolower(left_str.back())];

            if (quillindrom_table[upper_left] == upper_right && upper_right != ' ') {
                left_str.back() = upper_left;
                right_str.back() = upper_right;
            }
            else if (quillindrom_table[lower_left] == lower_right && lower_right != ' ') {
                left_str.back() = lower_left;
                right_str.back() = lower_right;
            }
            else {
                return "";
            }
        }

        --left; ++right;
    }

    reverse(left_str.begin(), left_str.end());
    return left_str + mid + right_str;
}

pair<string, string> make_quillindrom(const string& str, int mid) {
    int left, right;
    pair<string, string> result;
    if (str[mid] != quillindrom_table[str[mid]]) {
        if (isalpha(str[mid])) {
            if (toupper(str[mid]) == quillindrom_table[toupper(str[mid])]) {
                goto ODD;
            }
            else if (tolower(str[mid]) == quillindrom_table[tolower(str[mid])]) {
                goto ODD;
            }
        }
    }
    else {
    ODD:
        left = mid - 1;
        right = mid + 1;
        result.first = make_quillindrom(str, left, right);
    }

    left = mid;
    right = mid + 1;
    result.second = make_quillindrom(str, left, right);
    return result;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    string str;  cin >> str;

    auto func = [](const char c1, const char c2) {
        return toupper(c1) == toupper(c2);
    };

    string answer;
    for (int i = str.length() / 2 - 1; i < str.length(); i++) {
        pair<string, string> result = make_quillindrom(str, i);
        if (!result.first.empty() && (str.length() == result.first.length()) && ::equal(str.begin(), str.end(), result.first.begin(), func)) {
            answer = result.first;
        }

        if (!result.second.empty() && (str.length() == result.second.length()) && ::equal(str.begin(), str.end(), result.second.begin(), func)) {
            answer = result.second;
        }
    }

    if (answer.empty()) {
        cout << -1;
    }
    else {
        cout << answer;
    }

    return 0;
}