
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SmartWaste {
private:
    string day;
    float food, plastic;

    string foodPriority(float f) {
        if (f > 50) return "HIGH 🔴";
        else if (f >= 30) return "MEDIUM 🟡";
        else return "LOW 🟢";
    }

    string plasticPriority(float p) {
        if (p > 20) return "HIGH 🔴";
        else if (p >= 10) return "MEDIUM 🟡";
        else return "LOW 🟢";
    }

public:
    // ADMIN LOGIN
    bool login() {
        string user, pass;
        cout << "\n--- ADMIN LOGIN ---\n";
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        return (user == "admin" && pass == "1234");
    }

    // ADD RECORD
    void addRecord() {
        ofstream file("waste.txt", ios::app);

        cout << "Day: ";
        cin >> day;
        cout << "Food waste (kg): ";
        cin >> food;
        cout << "Plastic waste (kg): ";
        cin >> plastic;

        file << day << " " << food << " " << plastic << endl;
        file.close();

        cout << "\nRecord Added Successfully!\n";
        cout << "Food Priority: " << foodPriority(food) << endl;
        cout << "Plastic Priority: " << plasticPriority(plastic) << endl;
    }

    // VIEW RECORDS
    void viewRecords() {
        ifstream file("waste.txt");
        if (!file) {
            cout << "No data available.\n";
            return;
        }

        cout << "\nDay\tFood\tPlastic\n";
        cout << "--------------------------\n";
        while (file >> day >> food >> plastic) {
            cout << day << "\t" << food << "\t" << plastic << endl;
        }
        file.close();
    }

    // ALERT SUMMARY
    void alertSummary() {
        ifstream file("waste.txt");
        if (!file) return;

        cout << "\n--- ALERT SUMMARY ---\n";
        while (file >> day >> food >> plastic) {
            cout << "\nDay: " << day;
            cout << "\nFood: " << foodPriority(food);
            cout << "\nPlastic: " << plasticPriority(plastic) << endl;
        }
        file.close();
    }

    // WEEKLY / MONTHLY SUMMARY
    void summary() {
        ifstream file("waste.txt");
        float totalFood = 0, totalPlastic = 0;
        int days = 0;

        while (file >> day >> food >> plastic) {
            totalFood += food;
            totalPlastic += plastic;
            days++;
        }
        file.close();

        cout << "\n--- SUMMARY REPORT ---\n";
        cout << "Days Recorded: " << days << endl;
        cout << "Total Food Waste: " << totalFood << " kg\n";
        cout << "Total Plastic Waste: " << totalPlastic << " kg\n";
        cout << "Average Food Waste: " << totalFood / days << " kg\n";
        cout << "Average Plastic Waste: " << totalPlastic / days << " kg\n";
    }
};

int main() {
    SmartWaste sw;
    int choice;

    if (!sw.login()) {
        cout << "Login Failed!\n";
        return 0;
    }

    do {
        cout << "\nSMART WASTE MANAGEMENT SYSTEM\n";
        cout << "1. Add Waste Record\n";
        cout << "2. View Records\n";
        cout << "3. Alert Summary\n";
        cout << "4. Weekly/Monthly Summary\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sw.addRecord(); break;
            case 2: sw.viewRecords(); break;
            case 3: sw.alertSummary(); break;
            case 4: sw.summary(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 5);

    return 0;
}