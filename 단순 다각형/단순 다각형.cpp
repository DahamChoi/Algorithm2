#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, pair<long long, long long>> point;

long long ccw(const pair<long long, long long>& a, const pair<long long, long long>& b, const pair<long long, long long>& c) {
	return (a.first * b.second + b.first * c.second + c.first * a.second) -
		(a.second * b.first + b.second * c.first + c.second * a.first);
}

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	int T;	cin >> T;
	while (T--) {
		int N;	cin >> N;

		vector<point> points(N);
		for (int i = 0; i < N; i++) {
			cin >> points[i].second.first >> points[i].second.second;
			points[i].first = i;
		}

		sort(points.begin(), points.end(), [](const point& left, const point& right) {
			return (left.second.second == right.second.second) ? left.second.first < right.second.first : left.second.second < right.second.second;
			});

		sort(points.begin() + 1, points.end(), [&](const point& left, const point& right) {
			long long c = ccw(points.front().second, left.second, right.second);
			return (c != 0) ? c > 0 : left.second.first + left.second.second < right.second.first + right.second.second;
			});

		int pt = N - 1;
		for (int i = N - 1; i >= 1; i--) {
			if (ccw(points.front().second, points[pt].second, points[pt - 1].second) == 0) {
				--pt;
			}
			else {
				break;
			}
		}

		reverse(points.begin() + pt, points.end());

		for (auto& it : points) {
			cout << it.first << ' ';
		}
		cout << '\n';
	}

	return 0;
}