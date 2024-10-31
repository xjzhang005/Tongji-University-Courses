#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) {
    stack<char> s;
    string postfix;
    for (char c : infix) {
        if (isalpha(c)) {
            postfix += c;
        }
        else if (c == '(') {
            s.push(c);
        }
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && precedence(c) <= precedence(s.top())) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

TreeNode* buildExpressionTree(const string& postfix) {
    stack<TreeNode*> s;
    for (char c : postfix) {
        if (isalpha(c)) {
            s.push(new TreeNode(c));
        }
        else {
            TreeNode* node = new TreeNode(c);
            node->right = s.top(); s.pop();
            node->left = s.top(); s.pop();
            s.push(node);
        }
    }
    return s.top();
}

int getHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

void fillTree(vector<vector<char>>& tree, TreeNode* node, int row, int col, int height) {
    if (!node) return;
    tree[row][col] = node->value;
    if (node->left) {
        tree[row + 1][col - (1 << (height - row / 2 - 2))] = '/';
        fillTree(tree, node->left, row + 2, col - (1 << (height - row / 2 - 2)), height);
    }
    if (node->right) {
        tree[row + 1][col + (1 << (height - row / 2 - 2))] = '\\';
        fillTree(tree, node->right, row + 2, col + (1 << (height - row / 2 - 2)), height);
    }
}

void printTree(TreeNode* root) {
    int height = getHeight(root);
    int width = (1 << height) - 1;
    vector<vector<char>> tree(2 * height - 1, vector<char>(width, ' '));
    fillTree(tree, root, 0, width / 2, height);
    for (const auto& row : tree) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

int evaluateExpression(TreeNode* root, const unordered_map<char, int>& variables) {
    if (!root) return 0;
    if (isalpha(root->value)) {
        return variables.at(root->value);
    }
    int left = evaluateExpression(root->left, variables);
    int right = evaluateExpression(root->right, variables);
    switch (root->value) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return left / right;
    }
    return 0;
}

int main() {
    string infix;
    cin >> infix;
    int n;
    cin >> n;
    unordered_map<char, int> variables;
    for (int i = 0; i < n; ++i) {
        char var;
        int value;
        cin >> var >> value;
        variables[var] = value;
    }

    string postfix = infixToPostfix(infix);
    cout << postfix << endl;

    TreeNode* root = buildExpressionTree(postfix);
    printTree(root);

    int result = evaluateExpression(root, variables);
    cout << result << endl;

    return 0;
}