#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

Node* buildTree(const string& prefix) {
    stack<Node*> s;

    for (int i = prefix.size() - 1; i >= 0; --i) {
        Node* node = new Node();
        node->data = prefix[i];
        node->left = node->right = nullptr;

        if (isOperator(prefix[i])) {
            node->left  = s.top(); s.pop();
            node->right = s.top(); s.pop();
        }

        s.push(node);
    }

    return s.top();
}

// ─── Inorder traversal using a stack 

void inorder(Node* root) {
    stack<Node*> s;
    Node* cur = root;

    while (cur || !s.empty()) {
        while (cur) { s.push(cur); cur = cur->left; }
        cur = s.top(); s.pop();
        cout << cur->data << " ";
        cur = cur->right;
    }
}
// ─── Postorder traversal using two stacks

void postorder(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);
        if (node->left)  s1.push(node->left);
        if (node->right) s1.push(node->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}
// ─── Delete entire tree using a stack ────────────────────────────────────────

void deleteTree(Node* root) {
    if (!root) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* node = s.top(); s.pop();
        if (node->left)  s.push(node->left);
        if (node->right) s.push(node->right);
        delete node;
    }
}

int main() {
    string prefix;
    Node* root = nullptr;
    int choice = 0;

    while (choice != 5) {

        cout << "\n\n******** Expression Tree ********";
        cout << "\n1. Read Prefix Expression";
        cout << "\n2. Build Tree";
        cout << "\n3. Inorder Traversal";
        cout << "\n4. Postorder Traversal";
        cout << "\n5. Exit";

        cout << "\nEnter Choice:: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\nEnter Prefix Expression:: ";
            cin >> prefix;
            break;

        case 2:
            if (root) deleteTree(root);
            root = buildTree(prefix);
            cout << "\nExpression Tree Created!";
            break;

        case 3:
            cout << "\nInorder Traversal:: ";
            inorder(root);
            break;

        case 4:
            cout << "\nPostorder Traversal:: ";
            postorder(root);
            break;

        case 5:
            deleteTree(root);
            cout << "\nThanks for using Application!";
            break;

        default:
            cout << "\nWrong Choice!";
        }
    }

    return 0;
}
