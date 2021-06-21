#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_N = 100001;

struct RMQ {
	int N;	vector<int> tree;

	RMQ(const vector<int>& arr) {
		N = arr.size();
		tree.resize(N * 4);
		init(arr, 0, N - 1, 1);
	}

	int init(const vector<int>& arr, int left, int right, int node) {
		if (left == right) {
			return tree[node] = arr[left];
		}
		int mid = (left + right) / 2;
		int left_min = init(arr, left, mid, node * 2);
		int right_min = init(arr, mid + 1, right, node * 2 + 1);
		return tree[node] = min(left_min, right_min);
	}

	int query(int left, int right, int node, int node_left, int node_right) {
		if (right < node_left || node_right < left)	return 987654321;
		if (left <= node_left && node_right <= right) {
			return tree[node];
		}

		int mid = (node_left + node_right) / 2;
		return min(
			query(left, right, node * 2, node_left, mid), 
			query(left, right, node * 2 + 1, mid + 1, node_right));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, N - 1);
	}
};

vector<int> child[MAX_N];
int number_to_serial[MAX_N], serial_to_number[MAX_N];
int loc_in_trip[MAX_N], depth[MAX_N];
int next_serial;

void traverse(int here, int d, vector<int>& trip) {
	number_to_serial[here] = next_serial;
	serial_to_number[next_serial] = here;
	++next_serial;
	depth[here] = d;
	loc_in_trip[here] = trip.size();
	trip.push_back(number_to_serial[here]);
	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		trip.push_back(number_to_serial[here]);
	}
}

RMQ* prepare_rmq() {
	next_serial = 0;
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	int N;	cin >> N;
	vector<vector<int>> graph(N);
	for (int i = 0; i < N - 1; i++) {
		int u, v;	cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}

	for (int i = 0; i < N; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	vector<bool> visit(N);
	visit[0] = true;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		for (auto& it : graph[t]) {
			if (!visit[it]) {
				visit[it] = true;
				q.push(it);
				child[t].push_back(it);
			}
		}
	}

	RMQ* rmq = prepare_rmq();
	int M;	cin >> M;
	for (int i = 0; i < M; i++) {
		int u, v;	cin >> u >> v;
		u = loc_in_trip[u - 1]; v = loc_in_trip[v - 1];
		if (u > v)	swap(u, v);
		cout << (serial_to_number[rmq->query(u, v)] + 1) << '\n';
	}

	return 0;
}