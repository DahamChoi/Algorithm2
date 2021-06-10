#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <string>

using namespace std;

struct competition {
	string start;
	long long panalty, last, ce, cscore, format;
};

struct problem {
	long long order, pscore;
};

struct submission {
	string uid, date;
	long long sid, pid, result, presult, score;
};

struct result {
	long long type, try_cnt, good_solution_pid, penalty_1, penalty_2, try_cnt_2, good_solution_score;
};

struct user {
	string id;
	long long score, penalty, last_ac_id, last_submission_id;

	map<long long, result> problem_result;
};

struct compare {
	bool operator()(const pair<string, user>& _left, const pair<string, user>& _right) {
		const user& left = _left.second;	const user& right = _right.second;
		if (left.score == right.score) {
			if (left.penalty == right.penalty) {
				if (left.last_ac_id == right.last_ac_id) {
					if (left.last_submission_id == right.last_submission_id) {
						return left.id < right.id;
					}
					return left.last_submission_id < right.last_submission_id;
				}
				return left.last_ac_id < right.last_ac_id;
			}
			return left.penalty < right.penalty;
		}
		return left.score > right.score;
	}
};

long long get_solution_time(const string& start, const string& end) {
	tm end_time = {
		atoi(end.substr(17, 2).c_str()),
		atoi(end.substr(14, 2).c_str()),
		atoi(end.substr(11, 2).c_str()),
		atoi(end.substr(8, 2).c_str()),
		atoi(end.substr(5, 2).c_str()) - 1,
		atoi(end.substr(0, 4).c_str()) - 1900
	};
	tm start_time = {
		atoi(start.substr(17, 2).c_str()),
		atoi(start.substr(14, 2).c_str()),
		atoi(start.substr(11, 2).c_str()),
		atoi(start.substr(8, 2).c_str()),
		atoi(start.substr(5, 2).c_str()) - 1,
		atoi(start.substr(0, 4).c_str()) - 1900
	};
	
	double diff = (difftime(mktime(&end_time), mktime(&start_time)));
	long long tm_min = diff / 60;
	return tm_min;
}

string make_string(long long min) {
	string s1 = to_string(min / 60);
	string s2 = to_string(min % 60);
	if (s2.size() == 1) {
		s2.insert(s2.begin(), '0');
	}

	return s1 + ":" + s2;
}

int main() {
	ios::sync_with_stdio(false);	cin.tie(NULL);

	// 대회 정보
	competition compet;
	cin >> compet.panalty;
	string str;
	cin >> str;
	compet.start = str + ' ';
	cin >> str;
	compet.start.insert(compet.start.end(), str.begin(), str.end());
	cin >> compet.last >> compet.ce >> compet.cscore >> compet.format;

	// 문제 정보
	long long N;	cin >> N;
	map<long long, problem> problems;
	for (long long i = 0; i < N; i++) {
		long long id, order, pscore;	cin >> id >> order >> pscore;
		problems[id] = { order, pscore };
	}

	// 유저 정보
	long long M;	cin >> M;
	map<string, user> users;
	for (long long i = 0; i < M; i++) {
		string str;	cin >> str;
		users[str].id = str;
		for (auto& it : problems) {
			users[str].problem_result[it.first];
		}
	}

	// 제출 정보
	long long S;	cin >> S;
	vector<submission> submissions(S);
	for (long long i = 0; i < S; i++) {
		cin >> submissions[i].sid >> submissions[i].pid >> submissions[i].uid >> submissions[i].result >> submissions[i].presult >> submissions[i].score;
		string str;
		cin >> str;
		submissions[i].date = str + ' ';
		cin >> str;
		submissions[i].date.insert(submissions[i].date.end(), str.begin(), str.end());
	}

	for (auto& it : submissions) {
		if (users[it.uid].id.empty() || (compet.ce == 1 && it.result == 11) || it.result == 13) {
			continue;
		}

		users[it.uid].last_submission_id = it.sid;
		auto& p_result = users[it.uid].problem_result[it.pid];

		// 일반 대회
		if (compet.cscore == 0) {
			if (it.result == 4) {
				if (p_result.good_solution_pid == 0) {
					p_result.good_solution_pid = it.pid;
					p_result.penalty_1 = (p_result.try_cnt++) * compet.panalty;
					p_result.penalty_2 = get_solution_time(compet.start, it.date);
					++users[it.uid].score;
					p_result.type = 1;
				}
				users[it.uid].last_ac_id = it.sid;
			}
			else if (p_result.good_solution_pid == 0) {
				++p_result.try_cnt;
			}
		}
		// 점수 대회
		else {
			if (it.result == 4) {
				if (it.score > 0) {
					if (it.score > p_result.good_solution_score) {
						p_result.good_solution_score = it.score;
						p_result.penalty_1 = (p_result.try_cnt_2++) * compet.panalty;
						p_result.penalty_2 = get_solution_time(compet.start, it.date);
						p_result.type = 1;
						p_result.try_cnt = p_result.try_cnt_2;
					}
					else {
						++p_result.try_cnt_2;
					}
				}
				else {
					if (p_result.good_solution_score < problems[it.pid].pscore) {
						p_result.good_solution_score = problems[it.pid].pscore;
						p_result.penalty_1 = (p_result.try_cnt_2++) * compet.panalty;
						p_result.penalty_2 = get_solution_time(compet.start, it.date);
						p_result.type = 1;
						p_result.try_cnt = p_result.try_cnt_2;
					}
					else {
						++p_result.try_cnt_2;
					}
				}
				users[it.uid].last_ac_id = it.sid;
			}
			else {
				++p_result.try_cnt_2;
			}
		}
	}

	for (auto& it : users) {
		if (compet.last == 0) {
			for (auto& it2 : it.second.problem_result) {
				it.second.penalty += (it2.second.penalty_1 + it2.second.penalty_2);
			}
		}
		else {
			long long max_value = 0;
			for (auto& it2 : it.second.problem_result) {
				max_value = max(it2.second.penalty_2, max_value);
				it.second.penalty += it2.second.penalty_1;
			}
			it.second.penalty += max_value;
		}

		if (compet.cscore == 1) {
			for (auto& it2 : it.second.problem_result) {
				it.second.score += it2.second.good_solution_score;
			}
		}
	}

	vector<pair<string, user>> users_vector(users.begin(), users.end());
	sort(users_vector.begin(), users_vector.end(), compare());

	long long rank = 1;
	for (long long i = 0; i < users_vector.size(); i++) {
		if (users[users_vector[i].first].id.empty()) {
			continue;
		}

		cout << rank << "," << users_vector[i].first << ",";

		vector<pair<long long, result>> problem_result_vector(
			users_vector[i].second.problem_result.begin(), users_vector[i].second.problem_result.end());

		sort(problem_result_vector.begin(), problem_result_vector.end(), [&](const pair<long long, result>& left, const pair<long long, result>& right) {
			return problems[left.first].order < problems[right.first].order;
			});

		for (auto& it : problem_result_vector) {
			// 일반 대회
			if (compet.cscore == 0) {
				if (it.second.try_cnt == 0) {
					cout << "0/--,";
				}
				else {
					if (it.second.type == 1) {
						long long penalty = (compet.last == 0 ? it.second.penalty_1 + it.second.penalty_2 : it.second.penalty_2);
						cout << "a/" << it.second.try_cnt << "/" <<
							(compet.format == 1 ? make_string(penalty) : to_string(penalty)) << ",";
					}
					else {
						cout << "w/" << it.second.try_cnt << "/--,";
					}
				}
			}
			// 점수 대회
			else {
				if (it.second.try_cnt_2 == 0) {
					cout << "0/--,";
				}
				else {
					if (it.second.type == 1) {
						if (it.second.good_solution_score == problems[it.first].pscore) {
							cout << "a/";
						}
						else {
							cout << "p/";
						}

						long long penalty = (compet.last == 0 ? it.second.penalty_1 + it.second.penalty_2 : it.second.penalty_2);
						cout << it.second.good_solution_score << "/" << it.second.try_cnt << "/" <<
							(compet.format == 1 ? make_string(penalty) : to_string(penalty)) << ",";
					}
					else {
						cout << "w/" << it.second.try_cnt_2 << "/--,";
					}
				}
			}
		}

		cout << users_vector[i].second.score << "/" <<
			(compet.format == 1 ? make_string(users_vector[i].second.penalty) : to_string(users_vector[i].second.penalty)) << '\n';

		if (i + 1 < users_vector.size() &&
			!(users_vector[i].second.score == users_vector[i + 1].second.score &&
				users_vector[i].second.penalty == users_vector[i + 1].second.penalty)) {
			rank = i + 2;
		}
	}

	return 0;
}