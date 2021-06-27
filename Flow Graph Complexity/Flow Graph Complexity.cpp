#include <iostream>
#include <vector>
#include <istream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

int solution(int ef, int eb, int v, int w) {
	return ef + w * eb - v + 2;
}

bool is_vaild(const string& str) {
	// (1) the parentheses and the brackets are unmatched
	vector<char> stack;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			stack.push_back('(');
		}
		else if (str[i] == '[') {
			stack.push_back('[');
		}
		else if (str[i] == ')') {
			if (!stack.empty() && stack.back() == '(') {
				stack.pop_back();
			}
			else {
				return false;
			}
		}
		else if (str[i] == ']') {
			if (!stack.empty() && stack.back() == '[') {
				stack.pop_back();
			}
			else {
				return false;
			}
		}
	}

	if (!stack.empty()) {
		return false;
	}

	// (2) the parentheses and the brackets are unmatched, (4) it contains unknown types of node other than S, L, or B.
	auto it = find_if(str.begin(), str.end(), [](const char c) {
		return (c != '(' && c != ')' && c != '[' && c != ']' && c != ',' && c != 'S' && c != 'L' && c != 'B');
		});
	if (it != str.end()) {
		return false;
	}

	// (3) the punctuation symbols are added or omitted wrongly such as S, , S, SS, or B, (S),
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[') {
			if (i - 1 >= 0 && !(str[i - 1] == 'L' || str[i - 1] == 'B')) {
				return false;
			}

			if (i + 1 < str.length() && !isalpha(str[i + 1])) {
				return false;
			}

			if (i == str.length() - 1 || i == 0) {
				return false;
			}
		}

		if (str[i] == ')' || str[i] == ']') {
			if (i - 1 >= 0 && !(str[i - 1] == 'S' || str[i - 1] == ')' || str[i - 1] == ']')) {
				return false;
			}
			if (i + 1 < str.length() && !(str[i + 1] == ',' || str[i + 1] == ']' || str[i + 1] == ')')) {
				return false;
			}
		}

		if (str[i] == ',') {
			if (i - 1 >= 0 && !(str[i - 1] == 'S' || str[i - 1] == ')' || str[i - 1] == ']')) {
				return false;
			}
			if (i + 1 < str.length() && !isalpha(str[i + 1])) {
				return false;
			}

			if (i == str.length() - 1 || i == 0) {
				return false;
			}
		}

		if (str[i] == 'L' || str[i] == 'B') {
			if (i - 1 >= 0 && !(str[i - 1] == ',' || str[i - 1] == '[' || str[i - 1] == '(')) {
				return false;
			}
			if (i + 1 < str.length() && !(str[i + 1] == '(' || str[i + 1] == '[')) {
				return false;
			}
		}

		if (str[i] == 'S') {
			if (i - 1 >= 0 && !(str[i - 1] == ',' || str[i - 1] == '[' || str[i - 1] == '(')) {
				return false;
			}
			if (i + 1 < str.length() && !(str[i + 1] == ',' || str[i + 1] == ']' || str[i + 1] == ')')) {
				return false;
			}
		}
	}

	return true;
}

void get_value(const string& str, int& ef, int& eb, int& v) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			++ef;
		}
		else if (str[i] == 'L') {
			ef += 2;
			++eb;
			v += 2;
		}
		else if (str[i] == 'B') {
			ef += 2;
			++v;
		}
		else if (str[i] == 'S') {
			++v;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	string str;
	getline(cin, str);
	int W = atoi(str.c_str());
	getline(cin, str);

	for (auto it = str.begin(); it != str.end(); ) {
		if (*it == ' ') {
			it = str.erase(it);
		}
		else {
			it++;
		}
	}

	if (str.empty()) {
		cout << -1;
		return 0;
	}

	int EF = 0, EB = 0, V = 0;
	if (!is_vaild(str)) {
		cout << -1;
		return 0;
	}

	get_value(str, EF, EB, V);
	cout << solution(EF, EB, V, W);
	return 0;
}