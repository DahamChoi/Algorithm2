#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

int Hd, Ad, Hk, Ak, B, D, answer;
bool is_heal;
void battle(int dragon_hp, int dragon_attack, int knight_hp, int knight_attack, int depth, bool is_dragon_turn, int buff_cnt, int debuff_cnt) {
	if (is_dragon_turn) {
		if (knight_hp - dragon_attack <= 0) {
			answer = min(answer, depth);
		}
		else {
			if (dragon_hp - knight_attack <= 0) {
				if (debuff_cnt > 0 && dragon_hp - (max(0, knight_attack - D)) > 0) {
					battle(dragon_hp, dragon_attack, knight_hp, max(0, knight_attack - D), depth, !is_dragon_turn, buff_cnt, debuff_cnt - 1);
				}
				else if (!is_heal) {
					is_heal = true;
					battle(Hd, dragon_attack, knight_hp, knight_attack, depth, !is_dragon_turn, buff_cnt, debuff_cnt);
				}
			}
			else {
				is_heal = false;
				if (debuff_cnt > 0) {
					battle(dragon_hp, dragon_attack, knight_hp, max(0, knight_attack - D), depth, !is_dragon_turn, buff_cnt, debuff_cnt - 1);
				}
				else if (buff_cnt > 0) {
					battle(dragon_hp, dragon_attack + B, knight_hp, knight_attack, depth, !is_dragon_turn, buff_cnt - 1, debuff_cnt);
				}
				else {
					battle(dragon_hp, dragon_attack, knight_hp - dragon_attack, knight_attack, depth, !is_dragon_turn, buff_cnt, debuff_cnt);
				}
			}
		}
	}
	else {
		if (dragon_hp - knight_attack > 0) {
			battle(dragon_hp - knight_attack, dragon_attack, knight_hp, knight_attack, depth + 1, !is_dragon_turn, buff_cnt, debuff_cnt);
		}
	}
}

int main() {
	int T;	cin >> T;
	int Index = 1;

	while (T--) {
		cin >> Hd >> Ad >> Hk >> Ak >> B >> D;

		answer = INT_MAX;	is_heal = false;
		for (int i = 0; i <= 100; i++) {
			for (int j = 0; j <= 100; j++) {
				battle(Hd, Ad, Hk, Ak, 1, true, i, j);
			}
		}

		if (answer != INT_MAX) {
			printf("Case #%d: %d\n", Index, answer);
		}
		else {
			printf("Case #%d: IMPOSSIBLE\n", Index);
		}

		++Index;
	}

	return 0;
}

/*
10
42 68 35 1 69 24
79 59 63 65 5 45
82 28 62 92 95 42
28 37 92 5 2 53
93 83 22 17 18 95
48 27 72 39 69 12
68 100 36 95 3 11
23 34 74 65 41 11
54 69 48 45 62 57
38 60 24 42 29 78

1
82 28 62 92 95 42

Case #1: 1
Case #2: 2
Case #3: 4
Case #4: 3
Case #5: 1
Case #6: 2
Case #7: 1
Case #8: IMPOSSIBLE
Case #9: 1
Case #10: 1
*/