#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int n, m;

#define endl '\n' 
typedef long long ll; typedef pair<int, int> pii; string field[15]; int dp[15][1025];  
bool seat_check(string& seats, int bit) { for (size_t i = 0; i < seats.length(); i++) { if (seats[i] == 'x' && (bit & (1 << i))) return false; } return true; } 
bool adj_check(int bit, int width) { for (int i = 0; i < width - 1; i++) { int val = (3 << i); if ((bit & val) == val) return false; } return true; } 
bool bits_check(int bit, int fbit, int width) { for (int i = 0; i < width; i++) { if ((1 << i) & fbit) { if (i > 0 && ((1 << (i - 1)) & bit)) return false; if ((1 << (i + 1) & bit)) return false; } } return true; } 
void solve() { int ans = 0; memset(dp, 0, sizeof(dp)); vector<pii> bits_set; for (int bit = 0; bit < (1 << m); bit++) { if (adj_check(bit, m)) {
	int cnt = 0; for (int i = 0; i < m; i++) { if ((1 << i) & bit) cnt++; } bits_set.push_back(make_pair(bit, cnt)); } } for (int i = 1; i <= n; i++) {
		for (pii bit : bits_set) { if (!seat_check(field[i], bit.first)) continue; 
		for (pii fbit : bits_set) { 
			if (bits_check(bit.first, fbit.first, m)) { dp[i][bit.first] = max(dp[i][bit.first], dp[i - 1][fbit.first] + bit.second); ans = max(ans, dp[i][bit.first]); } } } } cout << ans << endl; return; }

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
	srand(time(0));
	int T;	cin >> T;
	while (T--) {
//		int H, W;	cin >> H >> W;
		int H = rand()%10 +1, W = rand()%10+1;
		n = H, m = W;
		vector<string> class_room(H);
		for (int i = 0; i < H; i++) {
			field[i + 1].clear();
			for (int j = 0; j < W; j++) {
				int c = rand() % 2 == 0 ? '.' : 'x';
				class_room[i].push_back(c);
				field[i + 1].push_back(c);
			}
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

		cout << "------------------------------------\n";
		for (auto& it : class_room) {
			cout << it << '\n';
		}
		cout << answer << '\n';
		solve();
	}

	return 0;
}