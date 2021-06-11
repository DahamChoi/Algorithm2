#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

static const int A = (1 << 7);
static const int B = (1 << 6);
static const int C = (1 << 5);
static const int D = (1 << 4);
static const int a = (1 << 3);
static const int b = (1 << 2);
static const int c = (1 << 1);
static const int d = (1 << 0);
static const int TEAM_A = A + B + C + D;
static const int TEAM_B = a + b + c + d;

unordered_map<string, tuple<int, int, int>> um = {
		{"A", {6,5,3}},{"B", {6,5,3}},{"C", {6,5,3}},{"D", {6,5,3}},
		{"a", {6,5,3}},{"b", {6,5,3}},{"c", {6,5,3}},{"d", {6,5,3}},
};

int get_yut_cnt(const string& yut) {
	int cnt = 0;
	for (auto& it : yut) {
		if (it == 'F') {
			++cnt;
		}
	}

	return (cnt == 0 ? 5 : cnt);
}

void splash_board(int& pos, int pos_x, int pos_y, int before) {
	if (before & TEAM_A) {
		if (pos & a) {
			um["a"] = {6,5,3};
		}
		if (pos & b) {
			um["b"] = {6,5,3};
		}
		if (pos & c) {
			um["c"] = {6,5,3};
		}
		if (pos & d) {
			um["d"] = {6,5,3};
		}

		pos &= TEAM_A;
		pos |= before;
	}
	else if (before & TEAM_B) {
		if (pos & A) {
			um["A"] = {6,5,3};
		}
		if (pos & B) {
			um["B"] = {6,5,3};
		}
		if (pos & C) {
			um["C"] = {6,5,3};
		}
		if (pos & D) {
			um["D"] = {6,5,3};
		}

		pos &= TEAM_B;
		pos |= before;
	}
}

void move_by_rule(vector<vector<int>>& board, int pos_x, int pos_y, int movement, int rule_type, string piece) {
	static vector<vector<pair<int, int>>> slice = {
		{{6,5},{6,4},{6,3},{6,2},{6,1},{6,0},{5,1},{4,2},{3,3},{4,4},{5,5},{6,6}},
		{{6,5},{6,4},{6,3},{6,2},{6,1},{6,0},{4,0},{3,0},{2,0},{1,0},{0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}},
		{{6,5},{6,4},{6,3},{6,2},{6,1},{6,0},{5,1},{4,2},{3,3},{2,4},{1,5},{0,6},{1,6},{2,6},{3,6},{4,6},{6,6}},
		{{6,5},{6,4},{6,3},{6,2},{6,1},{6,0},{4,0},{3,0},{2,0},{1,0},{0,0},{0,1},{0,2},{0,3},{0,4},{0,6},{1,6},{2,6},{3,6},{4,6},{6,6}}
	};

	static map<string, int> p = {
		{"A", A},{"B", B},{"C", C},{"D",D},
		{"a",a},{"b",b},{"c",c},{"d",d}
	};

	auto it = find(slice[rule_type].begin(), slice[rule_type].end(), make_pair(pos_x, pos_y));
	tuple<int, int, int> new_pos = { -1, -1, rule_type };
	int prev = board[pos_y][pos_x];
	if (distance(slice[rule_type].begin(), it) + movement < slice[rule_type].size()) {
		it += movement;
		new_pos = { it->first, it->second, rule_type };
		splash_board(board[it->second][it->first], it->second, it->first, board[pos_y][pos_x] == 0 ? p[piece] : board[pos_y][pos_x]);
	}
	board[pos_y][pos_x] = 0;

	if (prev == 0) {
		um[piece] = new_pos;
	}

	if (prev & A) {
		um["A"] = new_pos;
	}
	if (prev & B) {
		um["B"] = new_pos;
	}
	if (prev & C) {
		um["C"] = new_pos;
	}
	if (prev & D) {
		um["D"] = new_pos;
	}

	if (prev & a) {
		um["a"] = new_pos;
	}
	if (prev & b) {
		um["b"] = new_pos;
	}
	if (prev & c) {
		um["c"] = new_pos;
	}
	if (prev & d) {
		um["d"] = new_pos;
	}
}

void print_board(const vector<vector<int>>& board) {
	vector<string> origin = {
		"..----..----..----..----..----..",
		"..    ..    ..    ..    ..    ..",
		"| \\                          / |",
		"|  \\                        /  |",
		"|   \\                      /   |",
		"|    ..                  ..    |",
		"..   ..                  ..   ..",
		"..     \\                /     ..",
		"|       \\              /       |",
		"|        \\            /        |",
		"|         ..        ..         |",
		"|         ..        ..         |",
		"..          \\      /          ..",
		"..           \\    /           ..",
		"|             \\  /             |",
		"|              ..              |",
		"|              ..              |",
		"|             /  \\             |",
		"..           /    \\           ..",
		"..          /      \\          ..",
		"|         ..        ..         |",
		"|         ..        ..         |",
		"|        /            \\        |",
		"|       /              \\       |",
		"..     /                \\     ..",
		"..   ..                  ..   ..",
		"|    ..                  ..    |",
		"|   /                      \\   |",
		"|  /                        \\  |",
		"| /                          \\ |",
		"..    ..    ..    ..    ..    ..",
		"..----..----..----..----..----.."
	};

	vector<pair<int, int>> position;
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (origin[i][j] == '.') {
				bool b = true;
				if (i - 1 >= 0 && origin[i - 1][j] == '.') {
					b = false;
				}

				if (j - 1 >= 0 && origin[i][j - 1] == '.') {
					b = false;
				}

				if (b) {
					position.push_back({ j,i });
				}
			}
		}
	}

	map<pair<int, int>, int> m;
	for (auto& it : position) {
		int y = it.second, x = it.first;
		if (board[y / 5][x / 5] & a) {
			origin[y][x] = 'a';
		}
		if (board[y / 5][x / 5] & b) {
			origin[y][x + 1] = 'b';
		}
		if (board[y / 5][x / 5] & c) {
			origin[y + 1][x] = 'c';
		}
		if (board[y / 5][x / 5] & d) {
			origin[y + 1][x + 1] = 'd';
		}

		if (board[y / 5][x / 5] & A) {
			origin[y][x] = 'A';
		}
		if (board[y / 5][x / 5] & B) {
			origin[y][x + 1] = 'B';
		}
		if (board[y / 5][x / 5] & C) {
			origin[y + 1][x] = 'C';
		}
		if (board[y / 5][x / 5] & D) {
			origin[y + 1][x + 1] = 'D';
		}
	}

	for (auto& it : origin) {
		cout << it << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);

	vector<vector<int>> board(7, vector<int>(7));

	int N;	cin >> N;
	while (N--) {
		string piece, yut;	cin >> piece >> yut;
		int pos_x = get<0>(um[piece]), pos_y = get<1>(um[piece]), slice_rule = get<2>(um[piece]);
		if (pos_x == 6 && pos_y == 0) {
			slice_rule = 2;
		}
		else if (pos_x == 3 && pos_y == 3) {
			slice_rule = 0;
		}
		else if (pos_x == 0 && pos_y == 0) {
			slice_rule = 1;
		}

		move_by_rule(board, pos_x, pos_y, get_yut_cnt(yut), slice_rule, piece);
	}

	print_board(board);

	return 0;
}