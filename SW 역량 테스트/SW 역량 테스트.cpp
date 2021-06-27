#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct problem {
	long long score, panetly, time;
};

int N, T;
vector<problem> problems;
vector<vector<long long>> memory;

long long solution(int index, long long time) {
	if (index >= N)	return 0LL;

	long long& ref = memory[index][(int)time];
	if (ref != -1)	return ref;

	ref = max(ref, solution(index + 1, time));
	if (time + problems[index].time <= T) {
		ref = max(ref, solution(index + 1, time + problems[index].time) +
			(problems[index].score - ((time + problems[index].time) * problems[index].panetly)));
	}
	return ref;
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	cin >> N >> T;
	
	problems.resize(N);
	memory.assign(N, vector<long long>(T + 1, -1));

	for (int i = 0; i < N; i++) {
		int M;	cin >> M;
		problems[i].score = M;
	}

	for (int i = 0; i < N; i++) {
		int P;	cin >> P;
		problems[i].panetly = P;
	}

	for (int i = 0; i < N; i++) {
		int R;	cin >> R;
		problems[i].time = R;
	}

	sort(problems.begin(), problems.end(), [](const problem& left, const problem& right) {
		return (left.time / (double)left.panetly) < (right.time / (double)right.panetly);
		});

	cout << solution(0, 0);

	return 0;
}