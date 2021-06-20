#include <vector>
#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int W, A;	cin >> W >> A;
	vector<int> items(A);
	for (int i = 0; i < items.size(); i++) {
		cin >> items[i];
	}

	vector<int> memory(800000);
	vector<pair<int, int>> memory_2(800000);
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			if (i == j)	continue;
			
			memory[items[i] + items[j]] = 1;
			memory_2[items[i] + items[j]] = { i, j };
		}
	}

	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			if (i == j)	continue;

			int index = W - items[i] - items[j];
			if (index >= 0 && 
				memory[index] && memory_2[index].first != i && memory_2[index].second != i && memory_2[index].first != j && memory_2[index].second != j) {
				cout << "YES";
				return 0;
			}
		}
	}

	cout << "NO";
	return 0;
}