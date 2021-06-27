#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N;
vector<long long> numberic;
vector<vector<long long>> memory;

long long solution(long long hardness, int last_left, int last_right, int item) {
	if (item >= N)	return 0L;

	long long& ref = memory[last_left + 1][last_right + 1];
	if (ref != -1)	return ref;

	ref = LLONG_MAX;
	long long hard = abs(numberic[last_left == -1 ? item : last_left] - numberic[item]);
	ref = min(
		ref, solution(
			hardness + hard,
			item,
			last_right,
			item + 1) + hard);
	hard = abs(numberic[last_right == -1 ? item : last_right] - numberic[item]);
	ref = min(
		ref, solution(
			hardness + hard,
			last_left,
			item,
			item + 1) + hard);
	return ref;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	
	cin >> N;
	numberic.assign(N, 0);
	memory.assign(N + 1, vector<long long>(N + 1, -1));

	for (int i = 0; i < N; i++) {
		cin >> numberic[i];
	}

	cout << solution(0, -1, -1, 0);

	return 0;
}