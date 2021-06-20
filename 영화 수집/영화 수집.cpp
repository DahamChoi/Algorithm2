#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct FenwickTree {
    vector<long long> tree;
    FenwickTree(int n) : tree(n + 1) {}

    long long sum(int pos) {
        ++pos;
        long long ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }

    void add(int pos, long long val) {
        ++pos;
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int T;	cin >> T;
    while (T--) {
        int N, M;   cin >> N >> M;
        FenwickTree fenwick(200001);
        map<int, int> dvd_pos;

        for (int i = 1; i <= N; i++) {
            fenwick.add(N - i, 1);
            dvd_pos[i] = (N - i);
        }

        int last_index = N;
        for (int i = 0; i < M; i++) {
            int dvd;    cin >> dvd;
            cout << (fenwick.sum(200000) - fenwick.sum(dvd_pos[dvd])) << ' ';
            fenwick.add(dvd_pos[dvd], -1);
            dvd_pos[dvd] = last_index++;
            fenwick.add(dvd_pos[dvd], 1);
        }

        cout << '\n';
    }

	return 0;
}