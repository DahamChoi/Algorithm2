#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

struct piece {
	int top, left, down, right, index;

	void rotate() {
		int tmp = top;
		top = left;
		left = down;
		down = right;
		right = tmp;
	}

	int get_zero_cnt() {
		int cnt = 0;
		if (top == 0)	++cnt;
		if (left == 0)	++cnt;
		if (down == 0)	++cnt;
		if (right == 0)	++cnt;
		return cnt;
	}
};

bool is_safe(const vector<piece*> answer, int w, int h) {
	for (int i = 0; i < int(answer.size()); i++) {
		int y = (i / w);
		int x = (i % w);

		if (x == 0 && answer[i]->left != 0) {
			return false;
		}

		if (y == 0 && answer[i]->top != 0) {
			return false;
		}

		if (x == w - 1 && answer[i]->right != 0) {
			return false;
		}

		if (y == h - 1 && answer[i]->down != 0) {
			return false;
		}

		if (x - 1 >= 0 && 
			(answer[y * w + (x - 1)]->right == 0 ||
			answer[i]->left == 0 || 
			answer[y * w + (x - 1)]->right != answer[i]->left)) {
			return false;
		}

		if (x + 1 < w && 
			(answer[y * w + (x + 1)]->left == 0 ||
			answer[i]->right == 0 || 
			answer[y * w + (x + 1)]->left != answer[i]->right)) {
			return false;
		}

		if (y - 1 >= 0 && 
			(answer[(y - 1) * w + x]->down == 0 ||
			answer[i]->top == 0 || 
			answer[(y - 1) * w + x]->down != answer[i]->top)) {
			return false;
		}

		if (y + 1 < h &&
			(answer[(y + 1) * w + x]->top == 0 ||
			answer[i]->down == 0 || 
			answer[(y + 1) * w + x]->top != answer[i]->down)) {
			return false;
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);
	int N;	cin >> N;
	vector<piece> puzzle(N);
	unordered_map<int, vector<piece*>> puzzle_table_1;
	piece* root = nullptr;

	for (int i = 0; i < N; i++) {
		cin >> puzzle[i].top >> puzzle[i].left >> puzzle[i].down >> puzzle[i].right;
		puzzle[i].index = i + 1;
		if (puzzle[i].top > 0) {
			puzzle_table_1[puzzle[i].top].push_back(&puzzle[i]);
		}
		if (puzzle[i].left > 0) {
			puzzle_table_1[puzzle[i].left].push_back(&puzzle[i]);
		}
		if (puzzle[i].down > 0) {
			puzzle_table_1[puzzle[i].down].push_back(&puzzle[i]);
		}
		if (puzzle[i].right > 0) {
			puzzle_table_1[puzzle[i].right].push_back(&puzzle[i]);
		}
	}

	for (auto& it : puzzle) {
		if (it.get_zero_cnt() >= 2 && ((it.left == 0 && it.top == 0) || (it.top == 0 && it.right == 0) ||
			(it.right == 0 && it.down == 0) || (it.down == 0 && it.left == 0))) {
			root = &it;
			while (!(it.left == 0 && it.top == 0)) {
				it.rotate();
			}
			break;
		}
	}

	if (root == nullptr) {
		for (auto& it : puzzle) {
			if (it.get_zero_cnt() >= 2 && ((it.left == 0 && it.right == 0) || (it.top == 0 && it.down == 0))) {
				root = &it;
				while (!(it.left == 0 && it.right == 0)) {
					it.rotate();
				}

				int cnt = 0;
				while (root->top != 0) {
					vector<piece*>& v = puzzle_table_1[root->top];
					piece* other = (v.front() == root) ? v.back() : v.front();
					while (root->top != other->down) {
						other->rotate();
					}
					root = other;

					if (cnt++ > N) {
						cout << "impossible";
						return 0;
					}
				}
				break;
			}
		}

		if (root == nullptr) {
			cout << "impossible";
			return 0;
		}
	}

	vector<piece*> answer;
	int w = 0, h = 0;

	piece* y_finder = root;
	while (y_finder->down != 0) {
		piece* x_finder = y_finder;
		while (x_finder->right != 0) {
			vector<piece*>& v = puzzle_table_1[x_finder->right];
			piece* other = (v.front() == x_finder) ? v.back() : v.front();
			while (x_finder->right != other->left) {
				other->rotate();
			}

			answer.push_back(x_finder);
			x_finder = other;

			if (answer.size() > N) {
				break;
			}
		}

		answer.push_back(x_finder);

		vector<piece*>& v = puzzle_table_1[y_finder->down];
		piece* other = (v.front() == y_finder) ? v.back() : v.front();
		while (y_finder->down != other->top) {
			other->rotate();
		}
		y_finder = other;

		if (answer.size() > N) {
			break;
		}
	}

	piece* x_finder = y_finder;
	while (x_finder->right != 0) {
		vector<piece*>& v = puzzle_table_1[x_finder->right];
		piece* other = (v.front() == x_finder) ? v.back() : v.front();
		while (x_finder->right != other->left) {
			other->rotate();
		}

		answer.push_back(x_finder);
		x_finder = other;
		++w;

		if (answer.size() > N) {
			break;
		}
	}
	answer.push_back(x_finder);

	h = N / (++w);

	if (answer.size() != N || !is_safe(answer, w, h)) {
		cout << "impossible";
		return 0;
	}

	cout << h << ' ' << w << '\n';
	for (int i = 0; i < int(answer.size()); i++) {
		cout << answer[i]->index << ' ';
		if ((i + 1) % w == 0) {
			cout << '\n';
		}
	}

	return 0;
}