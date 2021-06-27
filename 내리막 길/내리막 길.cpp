#include <iostream>
#include <vector>

using namespace std;

int M, N;
vector<vector<int>> maps, memory;

int solution(int x, int y) {
	if (y == M - 1 && x == N - 1)	return 1;
	
	int& ref = memory[y][x];
	if (ref != -1)	return ref;

	ref = 0;
	if (x - 1 >= 0 && maps[y][x] > maps[y][x - 1]) {
		ref += solution(x - 1, y);
	}
	if (x + 1 < N && maps[y][x] > maps[y][x + 1]) {
		ref += solution(x + 1, y);
	}
	if (y - 1 >= 0 && maps[y][x] > maps[y - 1][x]) {
		ref += solution(x, y - 1);
	}
	if (y + 1 < M && maps[y][x] > maps[y + 1][x]) {
		ref += solution(x, y + 1);
	}
	return ref;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	cin >> M >> N;

	maps.assign(M, vector<int>(N));
	memory.assign(M, vector<int>(N, -1));

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> maps[i][j];
		}
	}

	cout << solution(0, 0);

	return 0;
}