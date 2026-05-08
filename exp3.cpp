#include<iostream>
#include<queue>

using namespace std;

// Node Structure
struct NODE {

    int val;
    NODE *next;
};

class GraphLandmarks {

    int GAM[10][10];
    int VISITED[10];
    NODE *HeaderGAL[10];
    int n;

    string Landmark[10] = {
        "Admin",
        "Canteen",
        "Sports",
        "Workshop"
    };

public:

    // Constructor
    GraphLandmarks() {

        initGraph();
    }

    // Initialize Graph
    void initGraph() {

        for (int i = 0; i < 10; i++) {

            VISITED[i] = 0;
            HeaderGAL[i] = NULL;

            for (int j = 0; j < 10; j++)
                GAM[i][j] = 0;
        }
    }

    // Create Graph
    void createGraph() {

        int s, d;
        int choice = 1;

        cout << "\nHow many nodes are there:: ";
        cin >> n;

        while (choice == 1) {

            cout << "\nEnter Source Node:: ";
            cin >> s;

            cout << "Enter Destination Node:: ";
            cin >> d;

            // Adjacency Matrix
            GAM[s][d] = 1;

            // Adjacency List
            NODE *p = new NODE;

            p->val = d;
            p->next = NULL;

            if (HeaderGAL[s] == NULL) {

                HeaderGAL[s] = p;
            }

            else {

                NODE *temp = HeaderGAL[s];

                while (temp->next != NULL)
                    temp = temp->next;

                temp->next = p;
            }

            cout << "\nAdd More Edges? (1/0):: ";
            cin >> choice;
        }
    }

    // Display Matrix
    void displayGAM() {

        cout << "\nAdjacency Matrix\n\n";

        for (int i = 1; i <= n; i++)
            cout << "\t" << Landmark[i - 1];

        cout << endl;

        for (int i = 1; i <= n; i++) {

            cout << Landmark[i - 1] << "\t";

            for (int j = 1; j <= n; j++) {

                cout << GAM[i][j] << "\t";
            }

            cout << endl;
        }
    }

    // Display List
    void displayGAL() {

        cout << "\nAdjacency List\n";

        for (int i = 1; i <= n; i++) {

            cout << Landmark[i - 1] << " -> ";

            NODE *temp = HeaderGAL[i];

            while (temp != NULL) {

                cout << Landmark[temp->val - 1] << " -> ";
                temp = temp->next;
            }

            cout << "NULL\n";
        }
    }

    // Reset VISITED Array
    void initVISITED() {

        for (int i = 0; i < 10; i++)
            VISITED[i] = 0;
    }

    // DFS using Matrix
    void DFS(int v) {

        VISITED[v] = 1;

        cout << Landmark[v - 1] << " -> ";

        for (int i = 1; i <= n; i++) {

            if (GAM[v][i] == 1 && VISITED[i] == 0)
                DFS(i);
        }
    }

    // BFS using List
    void BFS(int v) {

        queue<int> q;

        q.push(v);
        VISITED[v] = 1;

        while (!q.empty()) {

            int current = q.front();
            q.pop();

            cout << Landmark[current - 1] << " -> ";

            NODE *temp = HeaderGAL[current];

            while (temp != NULL) {

                if (VISITED[temp->val] == 0) {

                    q.push(temp->val);
                    VISITED[temp->val] = 1;
                }

                temp = temp->next;
            }
        }
    }
};

int main() {

    GraphLandmarks G;

    int choice = 0, s;

    while (choice != 6) {

        cout << "\n************ Graph Operations ************";
        cout << "\n1. Create Graph";
        cout << "\n2. Display Graph as Adjacency Matrix";
        cout << "\n3. Display Graph as Adjacency List";
        cout << "\n4. DFS Traversal";
        cout << "\n5. BFS Traversal";
        cout << "\n6. Exit";

        cout << "\nEnter Choice:: ";
        cin >> choice;

        switch (choice) {

        case 1:
            G.initGraph();
            G.createGraph();
            break;

        case 2:
            G.displayGAM();
            break;

        case 3:
            G.displayGAL();
            break;

        case 4:
            cout << "\nEnter Starting Vertex:: ";
            cin >> s;

            G.initVISITED();

            cout << "\nDFS Traversal:: ";
            G.DFS(s);
            break;

        case 5:
            cout << "\nEnter Starting Vertex:: ";
            cin >> s;

            G.initVISITED();

            cout << "\nBFS Traversal:: ";
            G.BFS(s);
            break;

        case 6:
            cout << "\nThanks for using Application!";
            break;

        default:
            cout << "\nWrong Choice!";
        }
    }

    return 0;
}
