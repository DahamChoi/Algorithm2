#include <iostream>
#include <vector>

using namespace std;

struct operation {
	char type, insert_ch;
	long long index;
};

struct compare {
	bool operator()(const operation& left, const operation& right) {
		return (left.type == right.type && left.insert_ch == right.insert_ch && left.index == right.index);
	}
};

void bubble_sort(vector<operation>& v) {
	for (int i = int(v.size()) - 1; i > 0; i--) {
		for (int j = 0; j < i && j + 1 < int(v.size()); j++) {
			operation& left = v[j], & right = v[j + 1];
			if (left.type == 'D' && right.type == 'D' && left.index <= right.index) {
				++right.index;
				swap(v[j], v[j + 1]);
			}
			else if (left.type == 'I' && right.type == 'I' && left.index >= right.index) {
				++left.index;
				swap(v[j], v[j + 1]);
			}
			else if (left.type == 'I' && right.type == 'D' && left.index == right.index) {
				v.erase(v.begin() + j);	v.erase(v.begin() + j);
			}
			else if (left.type == 'I' && right.type == 'D') {
				if (left.index < right.index) {
					--right.index;
				}
				else {
					--left.index;
				}

				swap(v[j], v[j + 1]);
			}
		}
	}
}

void input_operation(vector<operation>& v) {
	while (true) {
		char type, insert_ch = 0;
		long long index;
		cin >> type;
		if (type == 'E') {
			break;
		}

		cin >> index;
		if (type == 'I') {
			cin >> insert_ch;
		}

		v.push_back({ type, insert_ch, index });
	}
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);

	vector<operation> A, B;
	input_operation(A);
	input_operation(B);
	bubble_sort(A);
	bubble_sort(B);

	cout << (equal(A.begin(), A.end(), B.begin(), compare()) ? "0" : "1") << '\n';

	return 0;
}