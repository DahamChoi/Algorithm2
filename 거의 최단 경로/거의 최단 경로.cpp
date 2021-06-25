#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> path;
int N, M, S, D;

int dijkstra() {
	vector<int> dist(N, 987654321);

	dist[S] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, S });
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost)	continue;

		for (int there = 0; there < N; there++) {
			int nextDist = cost + graph[here][there];
			if (graph[here][there] != -1 && dist[there] > nextDist) {
				dist[there] = nextDist;
				path[there].clear();
				path[there].push_back(here);
				pq.push({ -nextDist, there });
			}
			else if (graph[here][there] != -1 && dist[there] == nextDist) {
				path[there].push_back(here);
			}
		}
	}

	return dist[D];
}

void erase_edge() {
	queue<int> q;
	q.push(D);
	vector<bool> visit(N);
	visit[D] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto it : path[cur]) {
			graph[it][cur] = -1;

			if (!visit[it]) {
				q.push(it);
				visit[it] = true;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	while (true) {
		cin >> N >> M;
		if (N == 0 && M == 0) {
			break;
		}

		cin >> S >> D;

		graph.assign(N, vector<int>(N, -1));
		path.assign(N, {});

		for (int i = 0; i < M; i++) {
			int U, V, P;	cin >> U >> V >> P;
			graph[U][V] = P;
		}

		dijkstra();
		erase_edge();
		int almost_min_distance = dijkstra();

		cout << (almost_min_distance == 987654321 ? -1 : almost_min_distance) << '\n';
	}
}