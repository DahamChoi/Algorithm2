#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dx[8] = { 0,1,0,-1,1,1,-1,-1 };
int dy[8] = { 1,0,-1,0,-1,1,-1,1 };

void game(vector<vector<int>>& board, bool is_black, int r, int c) {
	board[r][c] = (is_black ? 2 : 1);

	for (int i = 0; i < 8; i++) {
		int nx = c + dx[i], ny = r + dy[i];
		while (ny >= 0 && ny < 6 && nx >= 0 && nx < 6 &&
			(board[ny][nx] == (is_black ? 1 : 2))) {
			nx += dx[i];	ny += dy[i];
		}

		if (ny >= 0 && ny < 6 && nx >= 0 && nx < 6 && board[ny][nx] == (is_black ? 2 : 1)) {
			nx = c + dx[i];	ny = r + dy[i];
			while (ny >= 0 && ny < 6 && nx >= 0 && nx < 6 &&
				(board[ny][nx] == (is_black ? 1 : 2))) {
				board[ny][nx] = (is_black ? 2 : 1);
				nx += dx[i];	ny += dy[i];
			}
		}
	}
}

int main() {
	int N;	cin >> N;
	vector<vector<int>> board(6, vector<int>(6));
	board[2][2] = board[3][3] = 1;
	board[2][3] = board[3][2] = 2;
	
	for (int i = 0; i < N; i++) {
		int R, C;	cin >> R >> C;
		game(board, i % 2 == 0, R - 1, C - 1);
	}

	int black_cnt = 0, white_cnt = 0;
	for (auto& it : board) {
		white_cnt += count(it.begin(), it.end(), 1);
		black_cnt += count(it.begin(), it.end(), 2);
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (board[i][j] == 2) {
				cout << 'B';
			}
			else if (board[i][j] == 1) {
				cout << 'W';
			}
			else {
				cout << '.';
			}
		}
		cout << '\n';
	}

	cout << (white_cnt > black_cnt ? "White" : "Black");

	return 0;
}