#include <iostream>
#include <vector>
#include <map>
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

void tarjan_scc() {
	scc_id = discovered = vector<int>(graph.size(), -1);
	scc_counter = vertex_counter = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (discovered[i] == -1) {
			scc(i);
		}
	}
}

struct compare {
	bool operator()(const pair<int, vector<int>>& left, const pair<int, vector<int>>& right) {
		return left.second.front() < right.second.front();
	}
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int V, E;	cin >> V >> E;
	graph.assign(V, {});
	for (int i = 0; i < E; i++) {
		int u, v;	cin >> u >> v;
		graph[u - 1].push_back(v - 1);
	}

	tarjan_scc();

	map<int, vector<int>> solution;
	for (int i = 0; i < scc_id.size(); i++) {
		solution[scc_id[i]].push_back(i + 1);
	}

	vector<pair<int, vector<int>>> v_solution(solution.begin(), solution.end());
	sort(v_solution.begin(), v_solution.end(), compare());

	cout << scc_counter << '\n';
	for (auto& it : v_solution) {
		for (auto& vit : it.second) {
			cout << vit << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}