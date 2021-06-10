#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct person {
	int pos, spend_time, start_pos, index;
};

bool simuration(vector<vector<int>>& spend_time, vector<int>& distance, int s1, int s2, int s3) {
	int time = 0;
	vector<person> persons = {
		{ s1 * 2, 0, s1 * 2, 0 },
		{ s2 * 2, 0, s2 * 2, 1 },
		{ s3 * 2, 0, s3 * 2, 2 }
	};

	while (!persons.empty()) {
		for (int i = 0; i < persons.size(); i++) {
			if (persons[i].pos % 2 == 0) {
				if (++persons[i].spend_time >= spend_time[persons[i].index][persons[i].pos / 2]) {
					persons[i].spend_time = 0;
					++persons[i].pos;
				}
			}
			else {
				if (++persons[i].spend_time >= distance[persons[i].pos / 2]) {
					persons[i].spend_time = 0;
					persons[i].pos = persons[i].pos >= distance.size() * 2 - 1 ? 0 : persons[i].pos + 1;
					if (persons[i].pos == persons[i].start_pos) {
						persons.erase(persons.begin() + i);
						--i;
					}
				}
			}
		}

		for (int i = 0; i < persons.size(); i++) {
			for (int j = i + 1; j < persons.size(); j++) {
				if (persons[i].pos % 2 == 0 && persons[j].pos % 2 == 0 && persons[i].pos == persons[j].pos) {
					return false;
				}
			}
		}
	}

	return true;
}

bool simuration_2(vector<vector<int>>& spend_time, vector<int>& distance, int s1, int s2) {
	int time = 0;
	vector<person> persons = {
		{ s1 * 2, 0, s1 * 2, 0 },
		{ s2 * 2, 0, s2 * 2, 1 }
	};

	while (!persons.empty()) {
		for (int i = 0; i < persons.size(); i++) {
			if (persons[i].pos % 2 == 0) {
				if (++persons[i].spend_time >= spend_time[i][persons[i].pos / 2]) {
					persons[i].spend_time = 0;
					++persons[i].pos;
				}
			}
			else {
				if (++persons[i].spend_time >= distance[persons[i].pos / 2]) {
					persons[i].spend_time = 0;
					persons[i].pos = persons[i].pos >= distance.size() * 2 - 1 ? 0 : persons[i].pos + 1;
					if (persons[i].pos == persons[i].start_pos) {
						return true;
					}
				}
			}
		}

		if (persons[0].pos % 2 == 0 && persons[1].pos % 2 == 0 && persons[0].pos == persons[1].pos) {
			return false;
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);
	int N;	cin >> N;

	vector<int> distance(N);
	for (int i = 0; i < N; i++) {
		cin >> distance[i];
	}

	vector<vector<int>> spend_time(3, vector<int>(N));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++) {
			cin >> spend_time[i][j];
		}
	}

	vector<bool> cnd(N);
	for (int i = 0; i < 2; i++) {
		cnd[i] = true;
	}

	vector<vector<bool>> memory(N, vector<bool>(N));

	do {
		vector<int> pos;
		for (int i = 0; i < N; i++) {
			if (cnd[i]) {
				pos.push_back(i);
			}
		}

		if (simuration_2(spend_time, distance, pos[0], pos[1])) {
			memory[pos[0]][pos[1]] = true;
		}
	} while (prev_permutation(cnd.begin(), cnd.end()));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (memory[i][j]) {
				for (int k = 0; k < N; k++) {
					if (k == i || k == j) {
						continue;
					}

					if (simuration(spend_time, distance, i, j, k)) {
						cout << (i + 1) << " " << (j + 1) << " " << (k + 1);
						return 0;
					}
				}
			}
		}
	}

	cout << "impossible";

	return 0;
}