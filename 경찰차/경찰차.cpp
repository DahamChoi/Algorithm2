#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N, W;
vector<pair<int,int>> action;
vector<vector<int>> memory;
vector<int> choose;

int solution(int police_1, int police_2) {
	int& ref = memory[police_1][police_2];
	if (ref != -1) {
		return ref;
	}

	int last_action = max(police_1, police_2);
	if (last_action + 1 >= W + 2) {
		return 0;
	}

	return ref = min(
		solution(last_action + 1, police_2) + abs(action[police_1].first - action[last_action + 1].first) + abs(action[police_1].second - action[last_action + 1].second),
		solution(police_1, last_action + 1) + abs(action[police_2].first - action[last_action + 1].first) + abs(action[police_2].second - action[last_action + 1].second));
}

void search(int police_1, int police_2) {
	int last_action = max(police_1, police_2);
	if (last_action + 1 >= W + 2) {
		return;
	}

	int v1 = solution(last_action + 1, police_2) + abs(action[police_1].first - action[last_action + 1].first) + abs(action[police_1].second - action[last_action + 1].second);
	int v2 = solution(police_1, last_action + 1) + abs(action[police_2].first - action[last_action + 1].first) + abs(action[police_2].second - action[last_action + 1].second);
	if (v1 < v2) {
		cout << 1 << '\n';
		search(last_action + 1, police_2);
	}
	else {
		cout << 2 << '\n';
		search(police_1, last_action + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	cin >> N >> W;
	
	action.assign(W, { 0, 0 });
	action.insert(action.begin(), { N,N });
	action.insert(action.begin(), { 1,1 });
	memory.assign(W + 2, vector<int>(W + 2, -1));

	for (int i = 2; i < W + 2; i++) {
		cin >> action[i].first >> action[i].second;
	}

	cout << solution(0, 1) << '\n';
	search(0, 1);

	return 0;
}