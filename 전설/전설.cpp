#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

vector<int> check(2001);
struct TrieNode {
	map<char, TrieNode*> children;
	bool termial;

	void insert(const char* key) {
		if (*key == 0) {
			termial = true;
		}
		else {
			if (!children[*key]) {
				children[*key] = new TrieNode();
			}
			children[*key]->insert(key + 1);
		}
	}

	TrieNode* find(const char* key, bool is_color, int depth = 0) {
		if (termial)	++check[depth];
		if (*key == 0)	return this;
		if (children.find(*key) == children.end())	return nullptr;
		return children[*key]->find(key + 1, is_color, is_color ? depth + 1 : depth - 1);
	}
};

int main() {
	ios::sync_with_stdio(0);	cin.tie(0);

	TrieNode* color_root = new TrieNode(),* name_root = new TrieNode();

	int C, N;	cin >> C >> N;
	for (int i = 0; i < C; i++) {
		string str;	cin >> str;
		color_root->insert(str.c_str());
	}

	for (int i = 0; i < N; i++) {
		string str;	cin >> str;
		reverse(str.begin(), str.end());
		name_root->insert(str.c_str());
	}

	int Q;	cin >> Q;
	for (int i = 0; i < Q; i++) {
		bool is_safe = false;
		string name;	cin >> name;

		for (int k = 0; k < name.length(); k++) {
			check[k] = 0;
		}

		TrieNode* node = color_root->find(name.c_str(), true);
		reverse(name.begin(), name.end());
		TrieNode* name_node = name_root->find(name.c_str(), false, name.length());
		for (int i = 0; i < name.length(); i++) {
			if (check[i] == 2) {
				is_safe = true;
				break;
			}
		}

		cout << (is_safe ? "Yes\n" : "No\n");
	}

	return 0;
}