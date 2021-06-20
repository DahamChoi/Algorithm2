#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

using namespace std;

struct disjointset {
    vector<int> parent, weight;

    disjointset() : parent(100001), weight(100001) {}

    void init(int n) {
        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;  weight[i] = 0;
        }
    }

    int find(int u) {
        if (u == parent[u])  return u;
        int tmp = find(parent[u]);
        weight[u] += weight[parent[u]];
        return parent[u] = tmp;
    }

    void merge(int u, int v, int w) {
        int ru = find(u), rv = find(v);
        if (u == v)  return;

        weight[rv] = weight[u] - weight[v] + w;
        parent[rv] = ru;
    }
};

int main() {
    ios::sync_with_stdio(0);    cin.tie(0);

    disjointset dj;
    while (true) {
        int N, M;   cin >> N >> M;
        if (N == 0 && M == 0) {
            break;
        }

        dj.init(N);

        for (int i = 0; i < M; i++) {
            char c; cin >> c;
            if (c == '!') {
                int a, b, w;    cin >> a >> b >> w;
                dj.merge(a, b, w);
            }
            else {
                int a, b;   cin >> a >> b;
                if (dj.find(a) == dj.find(b)) {
                    cout << (dj.weight[b] - dj.weight[a]) << '\n';
                }
                else {
                    cout << "UNKNOWN\n";
                }
            }
        }
    }

    return 0;
}