#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

// Employee Structure
struct EMP {

    int EID;
    string name;
    string designation;
    float salary;
};

class SequentialFile {

    EMP obj;

public:

    // Read Employee Data
    void readData() {

        cout << "\nEnter Employee ID : ";
        cin >> obj.EID;

        cout << "Enter Employee Name : ";
        cin >> obj.name;

        cout << "Enter Designation : ";
        cin >> obj.designation;

        cout << "Enter Salary : ";
        cin >> obj.salary;
    }

    // Display One Record
    void printData() {

        cout << "\n"
             << obj.EID
             << setw(15) << obj.name
             << setw(15) << obj.designation
             << setw(15) << obj.salary;
    }

    // Insert Record
    void insertRecord() {

        ofstream out("employee.txt", ios::app | ios::binary);

        readData();

        out.write((char*)&obj, sizeof(obj));

        out.close();
    }

    // Display All Records
    void displayRecords() {

        ifstream in("employee.txt", ios::binary);

        cout << "\n\nEID"
             << setw(15) << "NAME"
             << setw(15) << "DESIGNATION"
             << setw(15) << "SALARY\n";

        while (in.read((char*)&obj, sizeof(obj))) {

            printData();
        }

        in.close();
    }

    // Search Record
    void searchRecord(string name) {

        ifstream in("employee.txt", ios::binary);

        while (in.read((char*)&obj, sizeof(obj))) {

            if (obj.name == name) {

                cout << "\nRecord Found!\n";

                printData();

                in.close();
                return;
            }
        }

        cout << "\nRecord Not Found!";

        in.close();
    }

    // Update Record
    void updateRecord(string name) {

        fstream file("employee.txt",
                     ios::in | ios::out | ios::binary);

        while (file.read((char*)&obj, sizeof(obj))) {

            if (obj.name == name) {

                cout << "\nOld Record:\n";

                printData();

                cout << "\n\nEnter New Details\n";

                readData();

                file.seekp(-sizeof(obj), ios::cur);

                file.write((char*)&obj, sizeof(obj));

                cout << "\nRecord Updated!";

                file.close();
                return;
            }
        }

        cout << "\nRecord Not Found!";

        file.close();
    }

    // Delete Record
    void deleteRecord(string name) {

        ifstream in("employee.txt", ios::binary);

        ofstream out("temp.txt", ios::binary);

        bool found = false;

        while (in.read((char*)&obj, sizeof(obj))) {

            if (obj.name != name) {

                out.write((char*)&obj, sizeof(obj));
            }

            else {

                found = true;
            }
        }

        in.close();
        out.close();

        remove("employee.txt");

        rename("temp.txt", "employee.txt");

        if (found)
            cout << "\nRecord Deleted!";
        else
            cout << "\nRecord Not Found!";
    }
};

int main() {

    SequentialFile t1;

    string name;

    int ch = 0;

    while (ch != 6) {

        cout << "\n******* SEQUENTIAL FILE PROGRAM ********";
        cout << "\n1. Insert Record";
        cout << "\n2. Display All Records";
        cout << "\n3. Search Record";
        cout << "\n4. Update Record";
        cout << "\n5. Delete Record";
        cout << "\n6. Exit";

        cout << "\nEnter Choice : ";
        cin >> ch;

        switch (ch) {

        case 1:

            t1.insertRecord();

            cout << "\nRecord Inserted!";
            break;

        case 2:

            t1.displayRecords();
            break;

        case 3:

            cout << "\nEnter Name to Search : ";
            cin >> name;

            t1.searchRecord(name);
            break;

        case 4:

            cout << "\nEnter Name to Update : ";
            cin >> name;

            t1.updateRecord(name);
            break;

        case 5:

            cout << "\nEnter Name to Delete : ";
            cin >> name;

            t1.deleteRecord(name);
            break;

        case 6:

            cout << "\nProgram Ended!";
            break;

        default:

            cout << "\nWrong Choice!";
        }
    }

    return 0;
}
