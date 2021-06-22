#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;

vector<int> discovered;
int counter = 0;

vector<bool> is_cut_vertex;

int find_cut_vertex(int here, bool is_root) {
	discovered[here] = counter++;
	int ref = discovered[here];

	int children = 0;
	for (int i = 0; i < graph[here].size(); i++) {
		int there = graph[here][i];

		if (discovered[there] == -1) {
			++children;
			int sub_tree = find_cut_vertex(there, false);
			if (!is_root && sub_tree >= discovered[here]) {
				is_cut_vertex[here] = true;
			}
			ref = min(ref, sub_tree);
		}
		else {
			ref = min(ref, discovered[there]);
		}
	}

	if (is_root) {
		is_cut_vertex[here] = (children >= 2);
	}

	return ref;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	int V, E;	cin >> V >> E;

	graph.assign(V, vector<int>());
	for (int i = 0; i < E; i++) {
		int u, v;	cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}

	discovered.assign(V, -1);
	is_cut_vertex.assign(V, false);

	int cur_parent = -1;
	for (int i = 0; i < V; i++) {
		if (discovered[i] == -1) {
			find_cut_vertex(i, true);
		}
	}

	vector<int> answer;
	for (int i = 0; i < is_cut_vertex.size(); i++) {
		if (is_cut_vertex[i]) {
			answer.push_back(i + 1);
		}
	}

	cout << answer.size() << '\n';
	for (auto& it : answer) {
		cout << it << ' ';
	}

	return 0;
}