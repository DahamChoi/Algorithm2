#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
	cin.sync_with_stdio(0);	cin.tie(0);

	int N;	cin >> N;

	vector<int> answer(10);
	map<int, int> um;

	string str = to_string(N);
	for (int i = 0; i < str.length(); i++) {
		for (int k = 0; k < 10; k++) {
			if (str[i] >= k + '0') {

			}
		}
	}

	for (int i = 1; i <= N; i++) {
		int ii = i;
		while (ii > 0) {
			++um[ii % 10];
			ii /= 10;
		}
	}

	return 0;
}