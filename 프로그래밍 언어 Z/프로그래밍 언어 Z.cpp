#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<string, int> variable_table;

bool is_number(const string& str) {
	for (auto& it : str) {
		if (!(it >= '0' && it <= '9')) {
			return false;
		}
	}

	return true;
}

long long func(long long a, long long b, const string& op) {
	if (op == "+") {
		return (a + b);
	}
	else if(op == "-") {
		return (a - b);
	}
	else {
		return (a * b);
	}
}

struct operation {
	virtual void task() = 0;
};

struct print : public operation {
	string key;

	virtual void task() {
		cout << key << " = " << variable_table[key] << '\n';
	}
};

struct assign : public operation {
	string key;
	vector<string> variable, value, sub_operation;

	void pre_task() {
		for (int i = 0; i < int(variable.size()); i++) {
			if (variable[i] == "+" || variable[i] == "-") {
				sub_operation.push_back(variable[i]);
			}
			else {
				if (is_number(variable[i])) {
					variable_table[variable[i]] = atoi(variable[i].c_str());
					value.push_back(variable[i]);
				}
				else if (variable[i].front() >= '0' && variable[i].front() <= '9') {
					int k = 0;
					while (variable[i][k] >= '0' && variable[i][k] <= '9') {
						++k;
					}

					string number = variable[i].substr(0, k).c_str();
					variable_table[number] = atoi(number.c_str());
					value.push_back(number);
					sub_operation.push_back("*");
					value.push_back(variable[i].substr(k, 1));
				}
				else {
					value.push_back(variable[i]);
				}
			}
		}
	}

	virtual void task() {
		vector<long long> result(value.size());
		for (int i = 0; i < (int)value.size(); i++) {
			result[i] = variable_table[value[i]];
		}

		for (int i = 0; i < int(sub_operation.size()); i++) {
			if (sub_operation[i] == "*") {
				result[i] = func(variable_table[value[i]], variable_table[value[i + 1]], "*");
			}
		}

		for (int i = 0; i < int(sub_operation.size()); i++) {
			if (sub_operation[i] != "*") {
				result[i + 1] = func(result[i], result[i + 1], sub_operation[i]);
			}
			else {
				result[i + 1] = result[i];
			}
		}

		variable_table[key] = ((result.back() % 10000 + 10000) % 10000);
	}
};

struct repeat : public operation {
	vector<operation*> operation_vector;
	int repeat_cnt;

	virtual void task() {
		for (int i = 0; i < repeat_cnt; i++) {
			for (auto& it : operation_vector) {
				it->task();
			}
		}
	}
};

string make_assign_operator(assign* op) {
	string str;	cin >> str;	cin >> str;
	string before;

	while ((str.front() >= 'a' && str.front() <= 'z') ||
		(str.front() >= '0' && str.front() <= '9') ||
		str.front() == '+' || str.front() == '-') {
		op->variable.push_back(str);
		before = str;
		cin >> str;
		if (((str.front() >= 'a' && str.front() <= 'z') ||
			(str.front() >= '0' && str.front() <= '9')) &&
			((before.front() >= 'a' && before.front() <= 'z') ||
				(before.front() >= '0' && before.front() <= '9'))) {
			break;
		}
	}

	op->pre_task();
	return str;
}

vector<operation*> parse() {
	vector<operation*> program;
	string str;

	while (str != "STOP") {
		cin >> str;
	XX:
		if (str.size() == 1 && str.front() >= 'a' && str.front() <= 'z') {
			assign* a = new assign();	a->key = str;
			str = make_assign_operator(a);
			program.push_back(a);
			goto XX;
		}
		else if (str == "REPEAT") {
			repeat* r = new repeat();	cin >> str;
			r->repeat_cnt = atoi(str.c_str());
			r->operation_vector = parse();
			program.push_back(r);
		}
		else if (str == "PRINT") {
			cin >> str;
			print* p = new print();	p->key = str;
			program.push_back(p);
		}
		else if (str == "STOP") {
			break;
		}
	}

	return program;
}

int main() {
	vector<operation*> program = parse();

	for (auto& it : program) {
		it->task();
	}

	return 0;
}