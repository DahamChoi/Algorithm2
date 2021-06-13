#include <iostream>
#include <vector>

using namespace std;

vector<int> getPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0);
    
    int begin = 1, matched = 0;
    while (begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0) {
                ++begin;
            }
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return pi;
}

vector<int> getprefixMatch(const string& s) {
    vector<int> ret, pi = getPartialMatch(s);
    int k = s.size();
    while (k > 0) {
        ret.push_back(k);
        k = pi[k - 1];
    }
    return ret;
}

int solution(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while (begin < n) {
        if (matched < m && a[begin + matched] == b[matched]) {
            ++matched;
            if (begin + matched == n) {
                return matched;
            }
        }
        else {
            if (matched == 0) {
                ++begin;
            }
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);

    int N;      cin >> N;
    string str; cin >> str;
    string r_str(str.rbegin(), str.rend());

    cout << (N - solution(str, r_str));

    return 0;
}