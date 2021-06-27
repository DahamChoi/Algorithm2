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

bool solution() {
	int n = graph.size() / 2;
	vector<int> label = tarjan_scc();

	for (int i = 0; i < 2 * n; i += 2) {
		if (label[i] == label[i + 1]) {
			return false;
		}
	}

	return true;
}

struct vector2 {
	double x, y;

	bool operator!=(const vector2& other) const {
		return (x != other.x || y != other.y);
	}
};

struct line {
	vector2 v1, v2;

	bool is_collision(const line& other) const {
		vector2 p1 = v1, p2 = v2, p3 = other.v1, p4 = other.v2;

		if (max(p1.x, p2.x) < min(p3.x, p4.x)) return false;
		if (min(p1.x, p2.x) > max(p3.x, p4.x)) return false;
		if (max(p1.y, p2.y) < min(p3.y, p4.y)) return false;
		if (min(p1.y, p2.y) > max(p3.y, p4.y)) return false;

		double sign1 = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
		double sign2 = (p2.x - p1.x) * (p4.y - p1.y) - (p4.x - p1.x) * (p2.y - p1.y);
		double sign3 = (p4.x - p3.x) * (p1.y - p3.y) - (p1.x - p3.x) * (p4.y - p3.y);
		double sign4 = (p4.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p4.y - p3.y);

		if (sign1 == 0 && sign2 == 0 && sign3 == 0 && sign4 == 0) return true;

		return sign1 * sign2 <= 0 && sign3 * sign4 <= 0;
	}
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	int W, P;	cin >> W >> P;

	graph.assign(P * 2, {});

	vector<vector2> origin_point(W);
	for (int i = 0; i < W; i++) {
		cin >> origin_point[i].x >> origin_point[i].y;
	}
	
	vector<line> pipes;
	for (int i = 0; i < P; i++) {
		int point;		cin >> point;
		double x, y;	cin >> x >> y;

		pipes.push_back(
			{ origin_point[point - 1].x, origin_point[point - 1].y, x, y }
		);
	}

	for (int i = 0; i < P; i++) {
		for (int j = 0; j < P; j++) {
			if (i == j)	continue;
			if (pipes[i].is_collision(pipes[j]) && pipes[i].v1 != pipes[j].v1) {
				graph[i * 2].push_back(j * 2 + 1);
				graph[j * 2 + 1].push_back(i * 2);
			}
		}
	}

	cout << (solution() ? "possible" : "impossible");

	return 0;
}