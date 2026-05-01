#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    float marks;
};


vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    Student s;

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.marks;
        students.push_back(s);
    }

    file.close();
    return students;
}


void saveStudents(vector<Student> students) {
    ofstream file("students.txt");
    for (auto s : students) {
        file << s.id << endl;
        file << s.name << endl;
        file << s.marks << endl;
    }
    file.close();
}

int main() {
    vector<Student> students = loadStudents();
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore();
        switch(choice) {

            case 1: {
                Student s;
                cout << "Enter ID: ";
                cin >> s.id;
                cin.ignore();

                cout << "Enter Full Name: ";
                getline(cin, s.name);

                cout << "Enter Marks: ";
                cin >> s.marks;

                students.push_back(s);
                saveStudents(students);

                cout << "Student added successfully!\n";
                break;
            }

            case 2: {
                cout << "\n--- Student List ---\n";
                for (auto s : students) {
                    cout << "ID: " << s.id
                         << ", Name: " << s.name
                         << ", Marks: " << s.marks << endl;
                }
                break;
            }

            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;

                bool found = false;

                for (auto it = students.begin(); it != students.end(); it++) {
                    if (it->id == id) {
                        students.erase(it);
                        found = true;
                        break;
                    }
                }

                if (found) {
                    saveStudents(students);
                    cout << "Student deleted!\n";
                } else {
                    cout << "Student not found!\n";
                }

                break;
            }

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    return 0;
}