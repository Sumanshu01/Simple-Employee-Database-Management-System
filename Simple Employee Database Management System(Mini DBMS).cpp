#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Record structure
struct Record {
    int id;
    string name;
    int age;
    string department;
};

// Class to manage the database
class Database {
private:
    vector<Record> records;
    const string filename = "database.txt";

    // Save the database to a file
    void saveToFile() {
        ofstream file(filename, ios::trunc);
        for (const auto &record : records) {
            file << record.id << "," << record.name << "," << record.age << "," << record.department << endl;
        }
        file.close();
    }

    // Load the database from a file
    void loadFromFile() {
        ifstream file(filename);
        records.clear();
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, ageStr, department;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, department, ',');
            Record record = {stoi(idStr), name, stoi(ageStr), department};
            records.push_back(record);
        }
        file.close();
    }

public:
    Database() {
        loadFromFile();
    }

    // Add a new record
    void insertRecord(int id, const string &name, int age, const string &department) {
        for (const auto &record : records) {
            if (record.id == id) {
                cout << "Error: Record with ID " << id << " already exists." << endl;
                return;
            }
        }
        records.push_back({id, name, age, department});
        saveToFile();
        cout << "Record inserted successfully!" << endl;
    }

    // Update an existing record
    void updateRecord(int id, const string &name, int age, const string &department) {
        for (auto &record : records) {
            if (record.id == id) {
                record.name = name;
                record.age = age;
                record.department = department;
                saveToFile();
                cout << "Record updated successfully!" << endl;
                return;
            }
        }
        cout << "Error: Record with ID " << id << " not found." << endl;
    }

    // Delete a record
    void deleteRecord(int id) {
        auto it = remove_if(records.begin(), records.end(), [id](const Record &record) {
            return record.id == id;
        });
        if (it != records.end()) {
            records.erase(it, records.end());
            saveToFile();
            cout << "Record deleted successfully!" << endl;
        } else {
            cout << "Error: Record with ID " << id << " not found." << endl;
        }
    }

    // Display all records
    void displayRecords() {
        if (records.empty()) {
            cout << "No records found." << endl;
            return;
        }
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age" << "Department" << endl;
        cout << string(40, '-') << endl;
        for (const auto &record : records) {
            cout << left << setw(5) << record.id << setw(20) << record.name << setw(5) << record.age << record.department << endl;
        }
    }

    // Query a record by ID
    void queryRecord(int id) {
        for (const auto &record : records) {
            if (record.id == id) {
                cout << "Record found:" << endl;
                cout << "ID: " << record.id << ", Name: " << record.name
                     << ", Age: " << record.age << ", Department: " << record.department << endl;
                return;
            }
        }
        cout << "Error: Record with ID " << id << " not found." << endl;
    }
};

// Main function
int main() {
    Database db;
    int choice;

    do {
        cout << "\n=== Mini DBMS ===\n";
        cout << "1. Insert Record\n";
        cout << "2. Update Record\n";
        cout << "3. Delete Record\n";
        cout << "4. Display All Records\n";
        cout << "5. Query Record by ID\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, age;
                string name, department;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Department: ";
                cin.ignore();
                getline(cin, department);
                db.insertRecord(id, name, age, department);
                break;
            }
            case 2: {
                int id, age;
                string name, department;
                cout << "Enter ID to update: ";
                cin >> id;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Age: ";
                cin >> age;
                cout << "Enter New Department: ";
                cin.ignore();
                getline(cin, department);
                db.updateRecord(id, name, age, department);
                break;
            }
            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                db.deleteRecord(id);
                break;
            }
            case 4:
                db.displayRecords();
                break;
            case 5: {
                int id;
                cout << "Enter ID to query: ";
                cin >> id;
                db.queryRecord(id);
                break;
            }
            case 6:
                cout << "Exiting Mini DBMS. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
