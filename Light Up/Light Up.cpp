#include <iostream>
#include <vector>

using namespace std;

// 0~4 숫자가 적힌 검은 사각형
// (1 << 3) 흰색 사각형
// (1 << 4) 검은색 사각형
// (1 << 5) 백열전구
// (1 << 6) light_up
// (1 << 7) 무한의 검은색 사각형

int get_black_rect_rule(vector<vector<int>>& board, int pos_x, int pos_y) {
	if (pos_x < 0 || pos_x >= board.size() || pos_y < 0 || pos_y >= board.size()) {
		return 987654321;
	}

	if (board[pos_y][pos_x] & (1 << 3)) {
		return 987654321;
	}

	if (board[pos_y][pos_x] & (1 << 7)) {
		return 987654321;
	}
	
	int cnt = (board[pos_y][pos_x] - (1 << 4));
	if (pos_x - 1 >= 0 && board[pos_y][pos_x - 1] & (1 << 5)) {
		--cnt;
	}

	if (pos_x + 1 < board.size() && board[pos_y][pos_x + 1] & (1 << 5)) {
		--cnt;
	}

	if (pos_y - 1 >= 0 && board[pos_y - 1][pos_x] & (1 << 5)) {
		--cnt;
	}

	if (pos_y + 1 < board.size() && board[pos_y + 1][pos_x] & (1 << 5)) {
		--cnt;
	}

	return cnt;
}

bool can_light_up(vector<vector<int>>& board, int pos_x, int pos_y) {
	bool left_light = (pos_x - 1 >= 0 && board[pos_y][pos_x - 1] & (1 << 5));
	bool right_light = (pos_x + 1 < board.size() && board[pos_y][pos_x + 1] & (1 << 5));
	bool up_light = (pos_y - 1 >= 0 && (board[pos_y - 1][pos_x] & (1 << 5)));
	bool down_light = (pos_y + 1 < board.size() && (board[pos_y + 1][pos_x] & (1 << 5)));
	bool overhit_light = (board[pos_y][pos_x] & (1 << 6));
	bool white_rectangle = (board[pos_y][pos_x] & (1 << 3));
	
	if (overhit_light || left_light || right_light || up_light || down_light || 
		get_black_rect_rule(board, pos_x - 1, pos_y) <= 0 ||
		get_black_rect_rule(board, pos_x + 1, pos_y) <= 0 ||
		get_black_rect_rule(board, pos_x, pos_y - 1) <= 0 ||
		get_black_rect_rule(board, pos_x, pos_y + 1) <= 0) {
		return false;
	}

	return white_rectangle;
}

void light_up(vector<vector<int>>& board, int pos_x, int pos_y) {
	board[pos_y][pos_x] |= (1 << 5);

	for (int i = pos_x; i >= 0; i--) {
		if (board[pos_y][i] & (1 << 4)) {
			break;
		}

		board[pos_y][i] |= (1 << 6);
	}

	for (int i = pos_x; i < board.size(); i++) {
		if (board[pos_y][i] & (1 << 4)) {
			break;
		}

		board[pos_y][i] |= (1 << 6);
	}

	for (int i = pos_y; i >= 0; i--) {
		if (board[i][pos_x] & (1 << 4)) {
			break;
		}

		board[i][pos_x] |= (1 << 6);
	}

	for (int i = pos_y; i < board.size(); i++) {
		if (board[i][pos_x] & (1 << 4)) {
			break;
		}

		board[i][pos_x] |= (1 << 6);
	}

	int a = 0;
}

bool is_safe(vector<vector<int>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			if ((board[i][j] & (1 << 3)) && (!(board[i][j] & (1 << 6)))) {
				return false;
			}

			if ((!(board[i][j] & (1 << 7)) && board[i][j] & (1 << 4)) && get_black_rect_rule(board, j, i) != 0) {
				return false;
			}
		}
	}

	return true;
}

bool is_back_tracking_success = false;
void back_tracking(vector<vector<int>>& board, int index) {
	if (is_back_tracking_success) {
		return;
	}

	if (is_safe(board)) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board.size(); j++) {
				if (board[i][j] & (1 << 5)) {
					cout << "1 ";
				}
				else {
					cout << "0 ";
				}
			}
			cout << '\n';
		}
		is_back_tracking_success = true;
		return;
	}

	for (int i = index; i < board.size() * board.size(); i++) {
		int pos_x = i % board.size();
		int pos_y = i / board.size();
		if (can_light_up(board, pos_x, pos_y)) {
			vector<vector<int>> before = board;
			light_up(board, pos_x, pos_y);
			back_tracking(board, i + 1);
			board = before;
		}
	}
}

int main() {
	int T;	cin >> T;
	while (T--) {
		int N;	cin >> N;
		vector<vector<int>> board(N, vector<int>(N));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] == -2) {
					board[i][j] = (1 << 3);
				}
				else {
					if (board[i][j] == -1) {
						board[i][j] = ((1 << 4) | (1 << 7));
					}
					else {
						board[i][j] |= (1 << 4);
					}
				}
			}
		}

		is_back_tracking_success = false;
		back_tracking(board, 0);
	}
	return 0;
}