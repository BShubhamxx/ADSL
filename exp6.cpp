#include<iostream>

using namespace std;

#define SIZE 5

// Client Structure
struct CLIENT {

    long int telephoneNo;
    string name;
};

class TelephoneDirectory {

    CLIENT LP[SIZE];
    CLIENT QP[SIZE];

    CLIENT cObj;

public:

    // Constructor
    TelephoneDirectory() {

        init();
    }

    // Initialize Tables
    void init() {

        for (int i = 0; i < SIZE; i++) {

            LP[i].telephoneNo = -1;
            QP[i].telephoneNo = -1;
        }
    }

    // Read Data
    void readData() {

        cout << "\nEnter Telephone Number : ";
        cin >> cObj.telephoneNo;

        cout << "Enter Client Name : ";
        cin >> cObj.name;
    }

    // ---------------- LINEAR PROBING ----------------

    void insertRecordLP() {

        readData();

        int index = cObj.telephoneNo % SIZE;

        for (int i = 0; i < SIZE; i++) {

            int newIndex = (index + i) % SIZE;

            if (LP[newIndex].telephoneNo == -1) {

                LP[newIndex] = cObj;

                cout << "\nRecord Inserted!";
                return;
            }
        }

        cout << "\nHash Table Full!";
    }

    void displayRecordsLP() {

        cout << "\nTelephone No\tName\n";

        for (int i = 0; i < SIZE; i++) {

            cout << LP[i].telephoneNo
                 << "\t\t"
                 << LP[i].name
                 << endl;
        }
    }

    void searchRecordLP(long int number) {

        int index = number % SIZE;

        int comparisons = 0;

        for (int i = 0; i < SIZE; i++) {

            int newIndex = (index + i) % SIZE;

            comparisons++;

            if (LP[newIndex].telephoneNo == number) {

                cout << "\nRecord Found!";
                cout << "\nComparisons : "
                     << comparisons;

                return;
            }
        }

        cout << "\nRecord Not Found!";
    }

    // ---------------- QUADRATIC PROBING ----------------

    void insertRecordQP() {

        readData();

        int index = cObj.telephoneNo % SIZE;

        for (int i = 0; i < SIZE; i++) {

            int newIndex = (index + i * i) % SIZE;

            if (QP[newIndex].telephoneNo == -1) {

                QP[newIndex] = cObj;

                cout << "\nRecord Inserted!";
                return;
            }
        }

        cout << "\nHash Table Full!";
    }

    void displayRecordsQP() {

        cout << "\nTelephone No\tName\n";

        for (int i = 0; i < SIZE; i++) {

            cout << QP[i].telephoneNo
                 << "\t\t"
                 << QP[i].name
                 << endl;
        }
    }

    void searchRecordQP(long int number) {

        int index = number % SIZE;

        int comparisons = 0;

        for (int i = 0; i < SIZE; i++) {

            int newIndex = (index + i * i) % SIZE;

            comparisons++;

            if (QP[newIndex].telephoneNo == number) {

                cout << "\nRecord Found!";
                cout << "\nComparisons : "
                     << comparisons;

                return;
            }
        }

        cout << "\nRecord Not Found!";
    }
};

int main() {

    TelephoneDirectory t1;

    int ch = 0;
    int ch1;

    long int telephoneNo;

    while (ch != 4) {

        cout << "\n****** HASH TABLE PROGRAM ******";
        cout << "\n1. Insert Record";
        cout << "\n2. Display Records";
        cout << "\n3. Search Record";
        cout << "\n4. Exit";

        cout << "\nEnter Choice : ";
        cin >> ch;

        switch (ch) {

        case 1:

            cout << "\n1. Linear Probing";
            cout << "\n2. Quadratic Probing";

            cout << "\nChoose Method : ";
            cin >> ch1;

            if (ch1 == 1)
                t1.insertRecordLP();
            else
                t1.insertRecordQP();

            break;

        case 2:

            cout << "\n1. Linear Probing";
            cout << "\n2. Quadratic Probing";

            cout << "\nChoose Method : ";
            cin >> ch1;

            if (ch1 == 1)
                t1.displayRecordsLP();
            else
                t1.displayRecordsQP();

            break;

        case 3:

            cout << "\nEnter Telephone Number : ";
            cin >> telephoneNo;

            cout << "\n1. Linear Probing";
            cout << "\n2. Quadratic Probing";

            cout << "\nChoose Method : ";
            cin >> ch1;

            if (ch1 == 1)
                t1.searchRecordLP(telephoneNo);
            else
                t1.searchRecordQP(telephoneNo);

            break;

        case 4:

            cout << "\nProgram Ended!";
            break;

        default:

            cout << "\nWrong Choice!";
        }
    }

    return 0;
}
