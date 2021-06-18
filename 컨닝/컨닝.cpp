#include <iostream>
#include <vector>

using namespace std;

bool check_bit(vector<string>& class_room, int prev_bit, int prev_index, int cur_bit, int cur_index) {
	int W = class_room.front().size(), H = class_room.size();
	for (int j = 0; j < H; j++) {
		if ((prev_bit & (1 << j)) && (cur_bit & (1 << j))) {
			return false;
		}

		if (j - 1 >= 0 && (prev_bit & (1 << (j - 1))) && (cur_bit & (1 << j))) {
			return false;
		}

		if (j + 1 < H && (prev_bit & (1 << (j + 1))) && (cur_bit & (1 << j))) {
			return false;
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int T;	cin >> T;
	while (T--) {
		int H, W;	cin >> H >> W;
		vector<string> class_room(H);
		for (int i = 0; i < H; i++) {
			cin >> class_room[i];
		}

		int answer = 0;

		vector<vector<int>> memory(W, vector<int>(1 << H));
		for (int i = 0; i < (1 << H); i++) {
			int sum = 0;
			for (int j = 0; j < H; j++) {
				if (i & (1 << j) && class_room[j][0] == '.') {
					++sum;
				}
			}
			memory[0][i] = sum;
		}

		for (int i = 1; i < W; i++) {
			for (int j = 0; j < (1 << H); j++) {
				for (int k = 0; k < (1 << H); k++) {
					if (check_bit(class_room, j, i - 1, k, i)) {
						int sum = 0;
						for (int h = 0; h < H; h++) {
							if (((1 << h) & k) && class_room[h][i] == '.') {
								++sum;
							}
						}
						memory[i][k] = max(memory[i][k], memory[i - 1][j] + sum);
					}
				}
			}
		}

		for (int i = 0; i < (1 << H); i++) {
			answer = max(memory.back()[i], answer);
		}
		cout << answer << '\n';
	}

	return 0;
}