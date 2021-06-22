#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> scc_id, discovered, stack;
int scc_counter, vertex_counter;

int scc(int here) {
	int ref = discovered[here] = vertex_counter++;
	stack.push_back(here);
	for (int i = 0; i < graph[here].size(); i++) {
		int there = graph[here][i];
		if (discovered[there] == -1) {
			ref = min(ref, scc(there));
		}
		else if (scc_id[there] == -1) {
			ref = min(ref, discovered[there]);
		}
	}

	if (ref == discovered[here]) {
		while (true) {
			int t = stack.back();
			stack.pop_back();
			scc_id[t] = scc_counter;
			if (t == here)	break;
		}
		++scc_counter;
	}

	return ref;
}

vector<int> tarjan_scc() {
	scc_id = discovered = vector<int>(graph.size(), -1);
	scc_counter = vertex_counter = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (discovered[i] == -1) {
			scc(i);
		}
	}

	return scc_id;
}

vector<int> solution() {
	int n = graph.size() / 2;
	vector<int> label = tarjan_scc();

	for (int i = 0; i < 2 * n; i += 2) {
		if (label[i] == label[i + 1]) {
			return {};
		}
	}

	vector<int> value(2 * n, -1);
	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; i++) {
		order.push_back({ -label[i], i });
	}

	sort(order.begin(), order.end());
	for (int i = 0; i < 2 * n; i++) {
		int vertex = order[i].second;
		int variable = vertex / 2;
		if (value[variable] != -1)	continue;
		value[variable] = (!(vertex % 2 == 0)) ? 1 : 0;
	}

	return value;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	int N, M;	cin >> N >> M;

	graph.assign(N * 2, {});

	for (int i = 0; i < M; i++) {
		int x, y;	cin >> x >> y;
		bool is_x_not = (x < 0), is_y_not = (y < 0);
		x = abs(x);	y = abs(y);
		--x; --y;
		if (is_x_not && is_y_not) {
			graph[x * 2].push_back(y * 2 + 1);
			graph[y * 2].push_back(x * 2 + 1);
		}
		else if (!is_x_not && is_y_not) {
			graph[x * 2 + 1].push_back(y * 2 + 1);
			graph[y * 2].push_back(x * 2);
		}
		else if (is_x_not && !is_y_not) {
			graph[x * 2].push_back(y * 2);
			graph[y * 2 + 1].push_back(x * 2 + 1);
		}
		else if (!is_x_not && !is_y_not) {
			graph[x * 2 + 1].push_back(y * 2);
			graph[y * 2 + 1].push_back(x * 2);
		}
	}

	vector<int> answer = solution();
	if (answer.empty()) {
		cout << 0;
		return 0;
	}

	cout << 1 << '\n';
	for (int i = 0; i < answer.size() / 2; i++) {
		cout << answer[i] << ' ';
	}

	return 0;
}