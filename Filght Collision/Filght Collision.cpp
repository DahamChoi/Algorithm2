#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <climits>

using namespace std;

struct drone {
    long double m;
    int index;
};

struct compare {
    bool operator()(const pair<long double, pair<int, int>>& left, const pair<long double, pair<int, int>>& right) {
        return left.first > right.first;
    }
};

long double get_meet_point(long double m1, long double b1, long double m2, long double b2) {
    if (m1 == m2) {
        return -1.0; //{ -1.0, -1.0 };
    }

    long double x = { (b2 - b1) / (m1 - m2) };
//    long double y = { (m1 * (b2 - b1) / (m1 - m2)) + b1 };
    return x; //{ x, y };
}

int main() {
    int N;  scanf("%d", &N);
    map<long double, drone> drones;
    for (int i = 0; i < N; i++) {
        long double x, v;
        scanf("%Lf %Lf", &x, &v);
        drones[x] = { v, i + 1 };
    }

    priority_queue<
        pair<long double, pair<int,int>>,
        vector<pair<long double, pair<int,int>>>, compare> pq;

    for (auto it = drones.begin(); it != drones.end(); it++) {
        auto& current = (it);
        if (current->second.m > 0) {
            auto next = (++it);    --it;
            if (next != drones.end()) {
                long double x = get_meet_point(current->second.m, current->first, next->second.m, next->first);
                if (x > 0) {
                    pq.push({ x, {current->first, next->first } });
                }
            }
        }
        else if (current->second.m < 0 && it != drones.begin()) {
            auto prev = (--it);    ++it;
            long double x = get_meet_point(current->second.m, current->first, prev->second.m, prev->first);
            if (x > 0) {
                pq.push({ x, { prev->first, current->first }});
            }
        }
    }

    while (!pq.empty()) {
        pair<long double, pair<int, int>> top = pq.top();
        pq.pop();

        if (drones.find(top.second.first) != drones.end() &&
            drones.find(top.second.second) != drones.end()) {
            auto prev = drones.find(top.second.first);
            --prev;
            auto next = drones.find(top.second.second);
            ++next;
            if (prev != drones.end() && next != drones.end()) {
                long double x = get_meet_point(prev->second.m, prev->first, next->second.m, next->first);
                if (x > 0) {
                    pq.push({ x, {prev->first, next->first} });
                }
            }

            drones.erase(top.second.first);
            drones.erase(top.second.second);
        }
    }

    vector<pair<long double, drone>> v_drones(drones.begin(), drones.end());
    sort(v_drones.begin(), v_drones.end(), [](const pair<long double, drone>& left, const pair<long double, drone>& right) {
        return left.second.index < right.second.index;
        });

    printf("%d\n", drones.size());
    for (auto& it : drones) {
        printf("%d ", it.second.index);
    }

    return 0;
}