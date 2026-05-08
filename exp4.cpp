#include<iostream>
#include<cstring>

using namespace std;

// Word Structure
struct WORD {

    char key[20];
    char meaning[100];
};

// AVL Node
struct NODE {

    WORD data;
    NODE *LC, *RC;
    int height;
};

class AVL {

    NODE *root;

public:

    AVL() {

        root = NULL;
    }

    NODE* getroot() {

        return root;
    }

    // Height
    int height(NODE *t) {

        if (t == NULL)
            return 0;

        int lh = height(t->LC);
        int rh = height(t->RC);

        return max(lh, rh) + 1;
    }

    // Balance Factor
    int balanceFactor(NODE *t) {

        if (t == NULL)
            return 0;

        return height(t->LC) - height(t->RC);
    }

    // Create Node
    NODE* createNode(WORD w) {

        NODE *p = new NODE;

        p->data = w;
        p->LC = p->RC = NULL;
        p->height = 1;

        return p;
    }

    // Right Rotation (LL)
    NODE* rightRotate(NODE *y) {

        NODE *x = y->LC;
        NODE *t2 = x->RC;

        x->RC = y;
        y->LC = t2;

        cout << "\nLeft Left Rotation";

        return x;
    }

    // Left Rotation (RR)
    NODE* leftRotate(NODE *x) {

        NODE *y = x->RC;
        NODE *t2 = y->LC;

        y->LC = x;
        x->RC = t2;

        cout << "\nRight Right Rotation";

        return y;
    }

    // Insert Node
    NODE* insert(NODE *t, WORD w) {

        // Normal BST Insert
        if (t == NULL)
            return createNode(w);

        if (strcmp(w.key, t->data.key) < 0)
            t->LC = insert(t->LC, w);

        else if (strcmp(w.key, t->data.key) > 0)
            t->RC = insert(t->RC, w);

        else {
            cout << "\nDuplicate Keyword!";
            return t;
        }

        // Balance Factor
        int bf = balanceFactor(t);

        // LL Rotation
        if (bf > 1 && strcmp(w.key, t->LC->data.key) < 0)
            return rightRotate(t);

        // RR Rotation
        if (bf < -1 && strcmp(w.key, t->RC->data.key) > 0)
            return leftRotate(t);

        // LR Rotation
        if (bf > 1 && strcmp(w.key, t->LC->data.key) > 0) {

            t->LC = leftRotate(t->LC);

            cout << "\nLeft Right Rotation";

            return rightRotate(t);
        }

        // RL Rotation
        if (bf < -1 && strcmp(w.key, t->RC->data.key) < 0) {

            t->RC = rightRotate(t->RC);

            cout << "\nRight Left Rotation";

            return leftRotate(t);
        }

        return t;
    }

    // Add Word
    void addWord(WORD w) {

        root = insert(root, w);
    }

    // Display Dictionary
    void displayIN(NODE *t) {

        if (t != NULL) {

            displayIN(t->LC);

            cout << t->data.key
                 << " : "
                 << t->data.meaning
                 << endl;

            displayIN(t->RC);
        }
    }

    // Search Word
    void searchNode(string key) {

        NODE *temp = root;

        int count = 0;

        while (temp != NULL) {

            count++;

            if (key == temp->data.key) {

                cout << "\nWord Found!";
                cout << "\nMeaning : "
                     << temp->data.meaning;

                cout << "\nComparisons : "
                     << count;

                return;
            }

            else if (key < temp->data.key)
                temp = temp->LC;

            else
                temp = temp->RC;
        }

        cout << "\nWord Not Found!";
    }
};

int main() {

    AVL B;

    int cho = 0;

    WORD w;

    char key[30];

    while (cho != 4) {

        cout << "\n******** AVL Dictionary ********";
        cout << "\n1. Add Word";
        cout << "\n2. Display Dictionary";
        cout << "\n3. Search Key";
        cout << "\n4. Exit";

        cout << "\nEnter Choice : ";
        cin >> cho;

        cin.ignore();

        switch (cho) {

        case 1:

            cout << "\nEnter Keyword : ";
            cin.getline(w.key, 20);

            cout << "Enter Meaning : ";
            cin.getline(w.meaning, 100);

            B.addWord(w);

            break;

        case 2:

            cout << "\nDictionary Data\n";

            B.displayIN(B.getroot());

            break;

        case 3:

            cout << "\nEnter Keyword : ";
            cin.getline(key, 20);

            B.searchNode(key);

            break;

        case 4:

            cout << "\nProgram Exits!!";
            break;

        default:

            cout << "\nWrong Choice!";
        }
    }

    return 0;
}
