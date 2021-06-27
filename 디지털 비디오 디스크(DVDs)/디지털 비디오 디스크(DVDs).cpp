#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct RMQ {
	int n;
	vector<int> rangeMin;
    bool is_min;

	RMQ(const vector<int>& array, bool _is_min) {
		n = array.size();
        is_min = _is_min;
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right) {
			return rangeMin[node] = array[left];
		}
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = (is_min ? min(leftMin, rightMin) : max(leftMin, rightMin));
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left)	return (is_min ? INT_MAX : -INT_MAX);
		if (left <= nodeLeft && nodeRight <= right)	return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return (is_min ? 
            min(
			    query(left, right, node * 2, nodeLeft, mid),
			    query(left, right, node * 2 + 1, mid + 1, nodeRight)) :
            max(
                query(left, right, node * 2, nodeLeft, mid),
                query(left, right, node * 2 + 1, mid + 1, nodeRight)));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int update(int index, int new_value, int node, int node_left, int node_right) {
		if (index < node_left || node_right < index) {
			return rangeMin[node];
		}
		if (node_left == node_right)	return rangeMin[node] = new_value;
		int mid = (node_left + node_right) / 2;
		return rangeMin[node] = (is_min ?
			min(
				update(index, new_value, node * 2, node_left, mid),
				update(index, new_value, node * 2 + 1, mid + 1, node_right)) :
			max(
				update(index, new_value, node * 2, node_left, mid),
				update(index, new_value, node * 2 + 1, mid + 1, node_right)));
	}

	int update(int index, int new_value) {
		return update(index, new_value, 1, 0, n - 1);
	}
};

int main() {
    ios::sync_with_stdio(0);    cin.tie(0);

    int T;  cin >> T;
    while (T--) {
        int N, K;   cin >> N >> K;

        vector<int> dvds(N);
        for (int i = 0; i < N; i++) {
            dvds[i] = i;
        }

        RMQ rmq_min(dvds, true), rmq_max(dvds, false);

        for (int i = 0; i < K; i++) {
            int Q, A, B;    cin >> Q >> A >> B;
            if (Q == 0) {
				rmq_min.update(A, dvds[B]);
				rmq_min.update(B, dvds[A]);
				rmq_max.update(A, dvds[B]);
				rmq_max.update(B, dvds[A]);
				swap(dvds[A], dvds[B]);
            }
            else {
				int min_value = rmq_min.query(A, B);
				int max_value = rmq_max.query(A, B);
				if (min_value == A && max_value == B) {
					cout << "YES\n";
				}
				else {
					cout << "NO\n";
				}
            }
        }
    }

    return 0;
}