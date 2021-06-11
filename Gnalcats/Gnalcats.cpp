#include <iostream>
#include <vector>

using namespace std;

static const int STACK_SIZE = 100000;

struct base {
    int index;
    base* left;
    base* right;
};

struct compare {
    bool operator()(const base* left, const base* right) {
        return (left->index == right->index);
    }
};

void print_base(base* node) {
    if (node->left && node->index != node->left->index) {
        print_base(node->left);
    }
    
    if (node->left) {
        cout << "<";
        cout << node->index;
    }

    if (node->right) {
        cout << ",";
        print_base(node->right);
    }
    cout << ">";
}

bool parse(const string& str, vector<base*>& stack) {
    for (auto& it : str) {
        if (it == 'C') {
            stack.push_back(new base(*stack.back()));
        }
        else if (it == 'D') {
            stack.pop_back();
        }
        else if (it == 'L') {
            if (stack.back()->right == nullptr) {
                return false;
            }

            base* n = stack.back();
            stack.back()->right = nullptr;
            stack.pop_back();
            stack.push_back(new base(*n->left));
        }
        else if (it == 'P') {
            base* n = new base(*stack.back());
            stack.pop_back();
            base* m = new base(*stack.back());
            stack.pop_back();
            stack.push_back(new base{ n->index, n, m });
        }
        else if (it == 'R') {
            if (stack.back()->right == nullptr) {
                return false;
            }

            base* n = new base(*stack.back()->right);
            stack.pop_back();
            stack.push_back(n);
        }
        else if (it == 'S') {
            swap(stack.back(), stack[stack.size() - 2]);
        }
        else if (it == 'U') {
            if (stack.back()->left == nullptr || stack.back()->right == nullptr) {
                return false;
            }

            base* n = new base(*stack.back()->left);
            base* m = new base(*stack.back()->right);
            stack.pop_back();
            stack.push_back(m);
            stack.push_back(n);
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);	cin.tie(NULL);
    string s1, s2;  cin >> s1 >> s2;
    bool is_fail_s1 = false, is_fail_s2 = false;
    
    vector<base*> stack_1(STACK_SIZE), stack_2(STACK_SIZE);
    for (int i = 0; i < STACK_SIZE; i++) {
        stack_1[i] = new base{ i, nullptr, nullptr };
        stack_1[i]->left = stack_1[i];
        stack_2[i] = new base{ i, nullptr, nullptr };
        stack_2[i]->left = stack_2[i];
    }

    is_fail_s1 = parse(s1, stack_1);
    is_fail_s2 = parse(s2, stack_2);

    if (((!is_fail_s1 && !is_fail_s2) || ((is_fail_s1 && is_fail_s2) && stack_1.size() == stack_2.size() &&
        equal(stack_1.begin(), stack_1.end(), stack_2.begin(), compare())))) {
        cout << "True";
    }
    else {
        cout << "False";
    }

    return 0;
}

