#include <iostream>
#include <vector>
#include <set>

#define SUCCESS "LADICA\n"
#define FAIL	"SMECE\n"

using namespace std;

struct disjointset {
	vector<int> parent, rank, empty;
	disjointset(int n) : parent(n), rank(n, 1), empty(n, 1) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (u == parent[u])	return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u);	v = find(v);
		if (u == v)	return;
		if (rank[u] > rank[v])	swap(u, v);

		empty[v] = empty[v] + empty[u];
		parent[u] = v;
		if (rank[u] == rank[v])	++rank[v];
	}
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	int N, L;	cin >> N >> L;

	disjointset jointset(L);

	for (int i = 0; i < N; i++) {
		int A, B;	cin >> A >> B;
		--A;	--B;

		bool sucess = false;
		int parent = jointset.find(A);
		if (jointset.empty[parent] > 0) {
			sucess = true;
			--jointset.empty[parent];
		}
		else if (jointset.empty[parent = jointset.find(B)] > 0) {
			sucess = true;
			--jointset.empty[parent];
		}

		cout << (sucess ? SUCCESS : FAIL);
		jointset.merge(A, B);
	}

	return 0;
}