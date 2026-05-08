#include <iostream>
#include <stack>
using namespace std;

struct Node {
    string word, meaning;
    Node *left, *right;

    Node(string w, string m) {
        word = w;
        meaning = m;
        left = right = NULL;
    }
};

class BST {
    Node *root;

public:
    BST() {
        root = NULL;
    }

    // Insert Node
    void insert(string word, string meaning) {
        Node *newNode = new Node(word, meaning);

        if (root == NULL) {
            root = newNode;
            return;
        }

        Node *temp = root;

        while (true) {
            if (word < temp->word) {
                if (temp->left == NULL) {
                    temp->left = newNode;
                    return;
                }
                temp = temp->left;
            }
            else if (word > temp->word) {
                if (temp->right == NULL) {
                    temp->right = newNode;
                    return;
                }
                temp = temp->right;
            }
            else {
                cout << "\nWord already exists!";
                delete newNode;
                return;
            }
        }
    }

    // Ascending Display
    void ascending(Node *temp) {
        if (temp != NULL) {
            ascending(temp->left);
            cout << temp->word << " : " << temp->meaning << endl;
            ascending(temp->right);
        }
    }

    // Descending Display using STL Stack
    void descending() {
        stack<Node*> s;
        Node *temp = root;

        while (temp != NULL || !s.empty()) {

            while (temp != NULL) {
                s.push(temp);
                temp = temp->right;
            }

            temp = s.top();
            s.pop();

            cout << temp->word << " : " << temp->meaning << endl;

            temp = temp->left;
        }
    }

    // Search Node
    void search(string key) {
        Node *temp = root;
        int count = 0;

        while (temp != NULL) {
            count++;

            if (key == temp->word) {
                cout << "\nWord Found!";
                cout << "\nMeaning : " << temp->meaning;
                cout << "\nComparisons : " << count;
                return;
            }
            else if (key < temp->word)
                temp = temp->left;
            else
                temp = temp->right;
        }

        cout << "\nWord Not Found!";
    }

    // Update Meaning
    void update(string key) {
        Node *temp = root;

        while (temp != NULL) {

            if (key == temp->word) {
                cout << "\nEnter New Meaning : ";
                cin >> temp->meaning;
                cout << "\nUpdated Successfully!";
                return;
            }
            else if (key < temp->word)
                temp = temp->left;
            else
                temp = temp->right;
        }

        cout << "\nWord Not Found!";
    }

    // Find Minimum Node
    Node* minValue(Node *temp) {
        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // Delete Node
    Node* deleteNode(Node *temp, string key) {

        if (temp == NULL)
            return NULL;

        if (key < temp->word)
            temp->left = deleteNode(temp->left, key);

        else if (key > temp->word)
            temp->right = deleteNode(temp->right, key);

        else {

            // No child
            if (temp->left == NULL && temp->right == NULL) {
                delete temp;
                return NULL;
            }

            // One child
            else if (temp->left == NULL) {
                Node *t = temp->right;
                delete temp;
                return t;
            }

            else if (temp->right == NULL) {
                Node *t = temp->left;
                delete temp;
                return t;
            }

            // Two children
            Node *t = minValue(temp->right);

            temp->word = t->word;
            temp->meaning = t->meaning;

            temp->right = deleteNode(temp->right, t->word);
        }

        return temp;
    }

    void deleteWord(string key) {
        root = deleteNode(root, key);
    }

    Node* getRoot() {
        return root;
    }
};

int main() {

    BST b;
    int choice;
    string word, meaning;

    do {

        cout << "\n\n===== BST Dictionary =====";
        cout << "\n1. Add Word";
        cout << "\n2. Display Ascending";
        cout << "\n3. Display Descending";
        cout << "\n4. Search Word";
        cout << "\n5. Update Meaning";
        cout << "\n6. Delete Word";
        cout << "\n7. Exit";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\nEnter Word : ";
            cin >> word;

            cout << "Enter Meaning : ";
            cin >> meaning;

            b.insert(word, meaning);
            break;

        case 2:
            cout << "\nDictionary in Ascending Order:\n";
            b.ascending(b.getRoot());
            break;

        case 3:
            cout << "\nDictionary in Descending Order:\n";
            b.descending();
            break;

        case 4:
            cout << "\nEnter Word to Search : ";
            cin >> word;

            b.search(word);
            break;

        case 5:
            cout << "\nEnter Word to Update : ";
            cin >> word;

            b.update(word);
            break;

        case 6:
            cout << "\nEnter Word to Delete : ";
            cin >> word;

            b.deleteWord(word);
            break;

        case 7:
            cout << "\nProgram Ended!";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while (choice != 7);

    return 0;
}
