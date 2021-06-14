#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

using namespace std;

struct monster {
	string name;
	int attack, shiled, max_hp, cur_hp, exp;
};

struct item_box {
	char type;
	string status;
};

map<string, int> accessory_table = {
			{"HR", 0}, {"RE", 1}, {"CO", 2},
			{"EX", 3}, {"DX", 4}, {"HU", 5}, {"CU", 6}
};
map<pair<int, int>, monster> monster_table;
map<pair<int, int>, item_box> item_box_table;

struct player {
	int pos_x, pos_y;
	int max_hp, cur_hp, attack, shiled, cur_exp, max_exp, level;
	int first_pos_x, first_pos_y;
	int weapon_status, armor_status;
	vector<int> accessory;

	// true, win - false, lose
	int battle(monster* m, bool is_boss) {
		if (is_boss && accessory[accessory_table["HU"]]) {
			cur_hp = max_hp;
		}

		int result = -1;
		int battle_attack = attack + weapon_status, battle_armor = shiled + armor_status;
		int first_attack = (accessory[accessory_table["CO"]] && accessory[accessory_table["DX"]]) ?
			battle_attack * 3 : (accessory[accessory_table["CO"]] ? battle_attack * 2 : battle_attack);
		int boss_first_attack = (accessory[accessory_table["HU"]] ? 0 : max(1, m->attack - battle_armor));
		
		while (true) {
			m->cur_hp = m->cur_hp - 
				max(1, (result == -1 ? first_attack : battle_attack) - m->shiled);

			if (m->cur_hp <= 0) {
				win_battle(m);
				return 1;
			}

			cur_hp = cur_hp - (result == -1 && is_boss ? boss_first_attack : max(1, m->attack - battle_armor));
			if (cur_hp <= 0) {
				return lose_battle(m);
			}

			result = 0;
		}

		return -1;
	}

	void win_battle(monster* m) {
		cur_hp = accessory[accessory_table["HR"]] ? min(cur_hp + 3, max_hp) : cur_hp;

		int exp = accessory[accessory_table["EX"]] ? m->exp * 1.2 : m->exp;
		cur_exp = min(cur_exp + exp, max_exp);
		if (cur_exp >= max_exp) {
			++level;	cur_exp = 0;	max_exp = level * 5;
			attack += 2;	shiled += 2;	
			max_hp += 5;	cur_hp = max_hp;
		}
	}

	int lose_battle(monster* m) {
		if (accessory[accessory_table["RE"]]) {
			accessory[accessory_table["RE"]] = 0;
			pos_x = first_pos_x;	pos_y = first_pos_y;
			cur_hp = max_hp;

			if (m) {
				m->cur_hp = m->max_hp;
			}
			return 2;
		}

		return 0;
	}

	void get_item_box(item_box* ib) {
		if (ib->type == 'W') {
			weapon_status = atoi(ib->status.c_str());
		}
		else if (ib->type == 'A') {
			armor_status = atoi(ib->status.c_str());
		}
		else if (accumulate(accessory.begin(), accessory.end(), 0) < 4) {
			accessory[accessory_table[ib->status]] = 1;
		}
	}

	int trap() {
		int trap_damage = (accessory[accessory_table["DX"]] ? 1 : 5);
		cur_hp = max(0, cur_hp - trap_damage);
		if (cur_hp <= 0) {
			return lose_battle(nullptr);
		}
		return 1;
	}
};

void solution(vector<string>& board, int turn, const player& p, const string& message) {
	if (p.cur_hp > 0) {
		board[p.pos_y][p.pos_x] = '@';
	}

	for (auto& it : board) {
		cout << it << '\n';
	}
	cout << "Passed Turns : " << turn << '\n';
	cout << "LV : " << p.level << '\n';
	cout << "HP : " << max(0, p.cur_hp) << "/" << p.max_hp << '\n';
	cout << "ATT : " << p.attack << "+" << p.weapon_status << '\n';
	cout << "DEF : " << p.shiled << "+" << p.armor_status << '\n';
	cout << "EXP : " << p.cur_exp << "/" << p.max_exp << '\n';
	cout << message;
}

int main() {
	int H, W;	cin >> H >> W;
	
	int monster_cnt = 0, item_box_cnt = 0, start_pos_x = 0, start_pos_y = 0;
	vector<string> board(H);
	for (int i = 0; i < H; i++) {
		cin >> board[i];
		monster_cnt += count(board[i].begin(), board[i].end(), '&');
		monster_cnt += count(board[i].begin(), board[i].end(), 'M');
		item_box_cnt += count(board[i].begin(), board[i].end(), 'B');

		auto it = find(board[i].begin(), board[i].end(), '@');
		if (it != board[i].end()) {
			start_pos_x = distance(board[i].begin(), it);
			start_pos_y = i;
			board[start_pos_y][start_pos_x] = '.';
		}
	}

	string order;	cin >> order;
	for (int i = 0; i < monster_cnt; i++) {
		int r, c, w, a, h, e;	string s;
		cin >> r >> c >> s >> w >> a >> h >> e;
		monster_table[{(r - 1), (c - 1)}] = {
			s, w, a, h, h, e
		};
	}

	for (int i = 0; i < item_box_cnt; i++) {
		int r, c;	char t;		string s;
		cin >> r >> c >> t >> s;
		item_box_table[{(r - 1), (c - 1)}] = {
			t, s
		};
	}

	player p{
		start_pos_x, start_pos_y, 20, 20, 2, 2, 0, 5, 1, start_pos_x, start_pos_y
	};
	p.accessory.assign(7, 0);

	map<char, pair<int, int>> order_table = {
		{'L', {-1,0} }, {'R', {1,0}},
		{'U', {0,-1} }, {'D', {0,1}}
	};

	for (int i = 0; i < int(order.size()); i++) {
		int nx = p.pos_x + order_table[order[i]].first;
		int ny = p.pos_y + order_table[order[i]].second;
		if (nx >= 0 && nx < W && ny >= 0 && ny < H && board[ny][nx] != '#') {
			if (board[ny][nx] == '&' || board[ny][nx] == 'M') {
				int result = p.battle(&monster_table[{ny, nx}], board[ny][nx] == 'M');
				if (result) {
					if (result == 2) {
						continue;
					}

					if (board[ny][nx] == 'M') {
						p.pos_x = nx;	p.pos_y = ny;
						board[ny][nx] = (board[ny][nx] == '^') ? '^' : '.';
						solution(board, i + 1, p, "YOU WIN!");
						return 0;
					}
				}
				else {
					solution(board, i + 1, p, "YOU HAVE BEEN KILLED BY " + monster_table[{ny, nx}].name + "..");

					return 0;
				}
			}
			else if (board[ny][nx] == 'B') {
				p.get_item_box(&item_box_table[{ny, nx}]);
			}
			else if (board[ny][nx] == '^') {
				int result = p.trap();
				if (!result) {
					solution(board, i + 1, p, "YOU HAVE BEEN KILLED BY SPIKE TRAP..");
					return 0;
				}
				else if(result == 2){
					continue;
				}
			}

			p.pos_x = nx;	p.pos_y = ny;
			board[ny][nx] = (board[ny][nx] == '^') ? '^' : '.';
		}
		else if (board[p.pos_y][p.pos_x] == '^') {
			if (!p.trap()) {
				solution(board, i + 1, p, "YOU HAVE BEEN KILLED BY SPIKE TRAP..");
				return 0;
			}
		}
	}

	solution(board, order.size(), p, "Press any key to continue.");
	return 0;
}