#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N, K, D;

struct student {
	vector<int> algorithm_kind;
	long long algorithm_skill;
};

vector<student> students;

void add_vector(vector<int>& left, vector<int>& right) {
	for (int i = 0; i < left.size(); i++) {
		left[i] += right[i];
	}
}

void minus_vector(vector<int>& left, vector<int>& right) {
	for (int i = 0; i < left.size(); i++) {
		left[i] -= right[i];
	}
}

pair<int,int> get_a_and_b(vector<int>& v, int cnt) {
	pair<int, int> result;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == cnt) {
			++result.second;
		}

		if (v[i] > 0) {
			++result.first;
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	cin >> N >> K >> D;
	students.assign(N, { vector<int>(K), 0 });
	for (int i = 0; i < N; i++) {
		int m, d;	cin >> m >> d;
		students[i].algorithm_skill = d;
		for (int j = 0; j < m; j++) {
			int A;	cin >> A;
			students[i].algorithm_kind[A - 1] = 1;
		}
	}

	sort(students.begin(), students.end(), [](const student& left, const student& right) {
		return left.algorithm_skill > right.algorithm_skill;
		});

	vector<int> v(K);
	add_vector(v, students.front().algorithm_kind);
	pair<int,int> result = get_a_and_b(v, 1);
	int a = result.first, b = result.second;
	int left = 0, right = 0, answer = 0;
	while (left < N) {
		answer = max(answer, (a - b) * (right - left + 1));

		if (right + 1 >= N) {
			minus_vector(v, students[left].algorithm_kind);
			++left;
			pair<int, int> result = get_a_and_b(v, right - left + 1);
			a = result.first, b = result.second;
		}
		else if (students[left].algorithm_skill - students[right + 1].algorithm_skill <= D) {
			++right;
			add_vector(v, students[right].algorithm_kind);
			pair<int,int> result = get_a_and_b(v, right - left + 1);
			a = result.first, b = result.second;
		}
		else {
			minus_vector(v, students[left].algorithm_kind);
			++left;
			pair<int, int> result = get_a_and_b(v, right - left + 1);
			a = result.first, b = result.second;
		}
	}

	cout << answer;

	return 0;
}