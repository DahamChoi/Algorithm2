#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>

using namespace std;

struct queue_info {
	int human_pos, alien_pos;
};

struct wormhole {
	int t, c;
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	
	int N, W, C, H, M;	cin >> N >> W >> C >> H >> M;

	set<int> solar_system, solar_system_miltery;
	vector<vector<wormhole>> graph(N);

	for (int i = 0; i < H; i++) {
		int n;	cin >> n;
		solar_system.insert(n);
	}

	for (int i = 0; i < M; i++) {
		int n;	cin >> n;
		solar_system_miltery.insert(n);
	}

	for (int i = 0; i < W; i++) {
		int r, c, t;	cin >> r >> c >> t;
		graph[r].push_back({ t, c });
	}

	vector<vector<bool>> visit(N, vector<bool>(N));
	for (int i = 0; i < N; i++) {
		if (solar_system.find(i) == solar_system.end()) {
			for (auto& it : solar_system) {
				queue<queue_info> q;
				q.push({ it, i });

				while (!q.empty()) {
					queue_info t = q.front();
					q.pop();

					auto mh_it = solar_system_miltery.find(t.human_pos);
					auto ma_it = solar_system_miltery.find(t.alien_pos);
					auto me = solar_system_miltery.end();
					if (mh_it != me && ma_it != me) {
						cout << "YES";
						return 0;
					}

					for (auto& a_it : graph[t.alien_pos]) {
						for (auto& h_it : graph[t.human_pos]) {
							if (a_it.c == h_it.c && !(a_it.t == t.alien_pos && h_it.t == t.human_pos) &&
								!visit[a_it.t][h_it.t]) {
								visit[a_it.t][h_it.t] = true;
								q.push({ h_it.t, a_it.t });
							}
						}
					}
				}
			}
		}
	}

	cout << "NO";
	return 0;
}