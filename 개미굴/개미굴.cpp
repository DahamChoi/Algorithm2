#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

vector<string> split_string(string s, string delimiter) {
    vector<string> result;

    auto pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        string token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    if (!s.empty()) {
        result.push_back(s);
    }

    return result;
}

void loop_printer(map<string, set<string>>& m, const string& key, int depth) {
    for (auto& it : m[key]) {
        string tmp(depth * 2, '-');
        cout << tmp + it << '\n';

        loop_printer(m, key + "\\" + it, depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    int N;	cin >> N;

    map<string, set<string>> m;
    set<string> root_directory;

    for (int i = 0; i < N; i++) {
        int K;  cin >> K;
        vector<string> split_list(K);
        for (int j = 0; j < K; j++) {
            cin >> split_list[j];
        }
        split_list.push_back("");

        string depth_string;
        for (int j = 0; j < split_list.size() - 1; j++) {
            if (j == 0) {
                root_directory.insert(split_list[j]);
            }

            if (depth_string.empty()) {
                depth_string += ((split_list[j]));
            }
            else {
                depth_string += ("\\" + (split_list[j]));
            }

            if (split_list[j + 1] == "") {
                m[depth_string].insert("ㅎㅇ");
                m[depth_string].erase("ㅎㅇ");
            }
            else {
                m[depth_string].insert(split_list[j + 1]);
            }
        }
    }

    for (auto& it : root_directory) {
        cout << it << '\n';
        loop_printer(m, it, 1);
    }

    return 0;
}