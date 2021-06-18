#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABETS = 26;
int to_number(char ch) {
	return ch - 'a';
}

struct TrieNode {
	vector<TrieNode*> children;
	int children_cnt{ 0 };
	bool termial;
	TrieNode() : termial(false) {
		children.assign(ALPHABETS, nullptr);
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i]) {
				delete children[i];
			}
		}
	}

	void insert(const char* key) {
		if (*key == 0) {
			termial = true;
		}
		else {
			int next = to_number(*key);
			if (!children[next]) {
				children[next] = new TrieNode();
				++children_cnt;
			}
			children[next]->insert(key + 1);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0)	return this;
		int next = to_number(*key);
		if (!children[next])	return nullptr;
		return children[next]->find(key + 1);
	}
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);
	cout.precision(2);	cout << fixed;

	int N;
	while (cin >> N) {
		TrieNode* root = new TrieNode();
		vector<string> dict;
		for (int i = 0; i < N; i++) {
			string s;	cin >> s;
			root->insert(s.c_str());
			dict.push_back(s);
		}
		
		int answer = 0;
		for (auto& it : dict) {
			int skip_cnt = it.length();
			TrieNode* node = root;
			for (int i = 0; i < it.length(); i++) {
				node = node->find(it.substr(i, 1).c_str());
				if (node && !node->termial && node->children_cnt == 1) {
					--skip_cnt;
				}
			}
			
			answer += skip_cnt;
		}

		cout << (answer / (double)dict.size()) << '\n';

		delete root;
	}

	return 0;
}