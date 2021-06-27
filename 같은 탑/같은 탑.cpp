#include <iostream>
#include <vector>

using namespace std;

vector<int> items;
vector<vector<int>> memory;

int N;
int pack(int left_tower, int right_tower, int item) {
	if (left_tower > 250000 || right_tower > 250000)	return -1;

	int t = left_tower - right_tower + 250000;
	if (item > N) {
		return -1;
	}

	int& ref = memory[t][item];
	if (ref != -2)	return ref;

	memory[t][item] = -1;
	if (t == 250000 && left_tower != 0)	memory[t][item] = 0;

	int result = pack(left_tower + items[item], right_tower, item + 1);
	if (result != -1) {
		ref = max(ref, result + items[item]);
	}
	result = pack(left_tower, right_tower + items[item], item + 1);
	if (result != -1) {
		ref = max(ref, result);
	}
	result = pack(left_tower, right_tower, item + 1);
	if (result != -1) {
		ref = max(ref, result);
	}
	return ref;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	cin >> N;
	items.assign(N + 1, 0);
	for (int i = 0; i < N; i++) {
		cin >> items[i];
	}

	memory.assign(500001, vector<int>(N + 1, -2));

	cout << pack(0, 0, 0);

	return 0;
}