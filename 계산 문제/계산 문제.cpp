#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct node {
	bool is_number;
	long long number;
	char operation;
};

unordered_map<char, int> um = {
		{'(', 3}, {'+',2},{'-',2},{'*',1},{'/',1}
};

long long func(long long a, long long b, char o) {
	if (o == '+') {
		return a + b;
	}
	else if (o == '-') {
		return a - b;
	}
	else if (o == '*') {
		return a * b;
	}
	else if (o == '/') {
		return a / b;
	}

	return {};
}

bool is_safe(const string& str) {
	vector<node> stack;
	vector<node> operation;

	for (int i = 0; i < int(str.length()); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			auto it = find_if(str.begin() + i, str.end(), [](const char c) {
				return !(c >= '0' && c <= '9');
				});
			string par = str.substr(i, distance(str.begin(), it) - i);
			operation.push_back({ true, atoll(par.c_str()), ' ' });
			i += (par.size() - 1);
		}
		else {
			if (stack.empty()) {
				stack.push_back({ false, 0, str[i] });
			}
			else {
				while (!stack.empty() && um[stack.back().operation] <= um[str[i]]) {
					operation.push_back(stack.back());
					stack.pop_back();
				}
				stack.push_back({ false, 0, str[i] });
			}
		}
	}

	while (!stack.empty()) {
		operation.push_back(stack.back());
		stack.pop_back();
	}

	while (operation.size() >= 3) {
		pair<int, int> range;
		for (int i = 0; i < operation.size(); i++) {
			if (!operation[i].is_number) {
				operation[i - 2].number = func(operation[i - 2].number, operation[i - 1].number, operation[i].operation);
				range.first = i - 1;
				range.second = i + 1;
				break;
			}
		}

		operation.erase(operation.begin() + range.first, operation.begin() + range.second);
	}

	return (operation.front().number == 2000);
}

string original;
vector<string> answer;

void solution(string str, int index) {
	if (index >= original.length()) {
		if (is_safe(str)) {
			answer.push_back(str);
		}
		return;
	}

	if (str.empty() || (!(str.back() >= '0' && str.back() <= '9'))) {
		solution(str + original[index], index + 1);
	}
	else {
		auto it = find_if(str.rbegin(), str.rend(), [](const char c) {
			return !(c >= '0' && c <= '9');
			});
		int dist = -distance(str.rend(), it);
		int last_number = atoll(str.substr(dist, str.length() - dist + 1).c_str());
		if (last_number != 0) {
			solution(str + original[index], index + 1);
		}

		if (index - 1 < original.length()) {
			solution(str + '+', index);
			solution(str + '-', index);
			solution(str + '*', index);
		}
	}
}

int main() {
	cin >> original;

	solution("", 0);

	sort(answer.begin(), answer.end());
	for (auto& it : answer) {
		cout << it << '\n';
	}

	return 0;
}