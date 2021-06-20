#include <iostream>
#include <vector>

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
    ios::sync_with_stdio(0);    cin.tie(0);

    int N, M, K;    cin >> N >> M >> K;
    
    FenwickTree fenwick(N);
    vector<long long> numberic(N);
    for (int i = 0; i < N; i++) {
        cin >> numberic[i];
        fenwick.add(i, numberic[i]);
    }

    for (int i = 0; i < M + K; i++) {
        int a, b;   long long c;    cin >> a >> b >> c;
        if (a == 1) {
            fenwick.add(b - 1, c - numberic[b - 1]);
            numberic[b - 1] = c;
        }
        else {
            cout << (fenwick.sum(c - 1) - fenwick.sum(b - 2)) << '\n';
        }
    }

    return 0;
}