#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct node_info {
	int target, weight, index;
};

typedef vector<vector<node_info>> graph_type;

struct burn_state {
	int source_node, target_node, index;
	double speed, cur_burn, target_burn;
};

double solution(const graph_type& graph, int burn_node, int M) {
	vector<bool> is_burn(M);

	vector<burn_state> burn_graph;
	for (auto& it : graph[burn_node]) {
		burn_graph.push_back({ burn_node, it.target, it.index, 0.5, 0.0, static_cast<double>(it.weight) });
	}

	double time = 0.0;
	while (!burn_graph.empty()) {
		vector<burn_state> add_graph;
		unordered_map<int, double> new_burn;
		for (auto it = burn_graph.begin(); it != burn_graph.end(); ) {
			if ((it->cur_burn += it->speed) >= it->target_burn) {
				is_burn[it->index] = true;
				new_burn[it->target_node] += 0.5;
				it = burn_graph.erase(it);
			}
			else {
				it++;
			}
		}

		vector<int> change_node;
		for (auto& it : new_burn) {
			for (auto& vit : graph[it.first]) {
				if (!is_burn[vit.index]) {
					auto fit = find_if(burn_graph.begin(), burn_graph.end(), [&](const burn_state& bs) {
						return vit.index == bs.index;
						});

					if (fit != burn_graph.end()) {
						fit->speed = 1.0;
					}
					else {
						auto ait = find_if(add_graph.begin(), add_graph.end(), [&](const burn_state& bs) {
							return vit.index == bs.index;
							});

						if (ait != add_graph.end()) {
							ait->speed = 1.0;
						}
						else {
							add_graph.push_back({ it.first, vit.target, vit.index, min(1.0, it.second), 0.0, static_cast<double>(vit.weight) });
						}
					}
				}
			}
		}

		burn_graph.insert(burn_graph.end(), add_graph.begin(), add_graph.end());
		time += 0.5;
	}

	return time;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int N, M;	cin >> N >> M;
	graph_type graph(N + 1);
	for (int i = 0; i < M; i++) {
		int S, E, L;	cin >> S >> E >> L;
		graph[S].push_back({ E, L, i });
		graph[E].push_back({ S, L, i });
	}

	double min_value = 987654321.0;
	for (int i = 1; i <= N; i++) {
		min_value = min(min_value, solution(graph, i, M));
	}

	cout << ::fixed;
	cout.precision(1);
	cout << min_value;

	return 0;
}