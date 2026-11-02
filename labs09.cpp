#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to store Expense details
struct Expense {
    int id;
    char date[15];
    char category[20];
    float amount;
};

// Global variables for user credentials and budget
string regUser = "", regPass = "";
float monthlyBudget = 0.0;

// Function for User Registration
void registerUser() {
    cout << "\n--- USER REGISTRATION ---\n";
    cout << "Enter username: ";
    cin >> regUser;
    cout << "Enter password: ";
    cin >> regPass;
    cout << "Registration successful!\n";
}

// Function for User Login
bool loginUser() {
    string user, pass;
    cout << "\n--- USER LOGIN ---\n";
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    if (user == regUser && pass == regPass) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid username or password!\n";
        return false;
    }
}

// Function to set monthly budget
void setBudget() {
    cout << "\n--- SET MONTHLY BUDGET ---\n";
    cout << "Enter your monthly budget: Rs. ";
    cin >> monthlyBudget;
    cout << "Budget set successfully to Rs. " << monthlyBudget << "\n";
}

// Function to add a daily expense and save to file
void addExpense(int id) {
    Expense exp;
    exp.id = id;
    
    cout << "\n--- ADD DAILY EXPENSE ---\n";
    cout << "Enter date (DD/MM/YYYY): ";
    cin >> exp.date;
    cout << "Enter category (e.g., Food, Transport, Rent): ";
    cin >> exp.category;
    cout << "Enter amount: Rs. ";
    cin >> exp.amount;

    // Save to text file (File Handling)
    ofstream outFile("expenses.txt", ios::app);
    outFile << exp.id << " " << exp.date << " " << exp.category << " " << exp.amount << endl;
    outFile.close();

    cout << "Expense added and saved to file successfully!\n";

    // Budget Warning Check
    if (monthlyBudget > 0) {
        ifstream inFile("expenses.txt");
        float totalSpent = 0;
        int tempId;
        char tempDate[15], tempCat[20];
        float tempAmt;

        while (inFile >> tempId >> tempDate >> tempCat >> tempAmt) {
            totalSpent += tempAmt;
        }
        inFile.close();

        if (totalSpent > monthlyBudget) {
            cout << "\n WARNING! You have exceeded your monthly budget!\n";
            cout << "Total Spent: Rs. " << totalSpent << " | Budget: Rs. " << monthlyBudget << "\n";
        } else if (totalSpent >= 0.8 * monthlyBudget) {
            cout << "\n ALERT! You have reached 80% of your monthly budget!\n";
        }
    }
}

// Function to view all expense history from file
void viewExpenses() {
    cout << "\n--- EXPENSE HISTORY ---\n";
    ifstream inFile("expenses.txt");
    if (!inFile) {
        cout << "No expense records found!\n";
        return;
    }

    int id;
    char date[15], category[20];
    float amount;

    cout << "ID\tDate\t\tCategory\tAmount\n";
    cout << "--------------------------------------------------\n";
    while (inFile >> id >> date >> category >> amount) {
        cout << id << "\t" << date << "\t" << category << "\t\tRs. " << amount << endl;
    }
    inFile.close();
}

// Function to generate category-wise report
void categoryReport() {
    char searchCat[20];
    cout << "\n--- CATEGORY-WISE EXPENSE REPORT ---\n";
    cout << "Enter category to search (e.g., Food): ";
    cin >> searchCat;

    ifstream inFile("expenses.txt");
    if (!inFile) {
        cout << "No records found!\n";
        return;
    }

    int id;
    char date[15], category[20];
    float amount, totalCatExpense = 0;

    cout << "\nExpenses for category: " << searchCat << "\n";
    while (inFile >> id >> date >> category >> amount) {
        string c1(category), c2(searchCat);
        if (c1 == c2) {
            cout << "Date: " << date << " | Amount: Rs. " << amount << endl;
            totalCatExpense += amount;
        }
    }
    inFile.close();
    cout << "Total spent on " << searchCat << ": Rs. " << totalCatExpense << "\n";
}

// Main Menu Driven Program
int main() {
    int choice;
    int expenseIdCounter = 1;
    bool loggedIn = false;

    do {
        cout << "\n===============================\n";
        cout << "   SMART DIGITAL EXPENSE TRACKER\n";
        cout << "===============================\n";
        cout << "1. User Registration\n";
        cout << "2. Login System\n";
        cout << "3. Set Monthly Budget\n";
        cout << "4. Add Daily Expense\n";
        cout << "5. View Expense History\n";
        cout << "6. Category-wise Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser();
                break;
            case 3:
                if (loggedIn) setBudget();
                else cout << "Please login first!\n";
                break;
            case 4:
                if (loggedIn) {
                    addExpense(expenseIdCounter);
                    expenseIdCounter++;
                } else {
                    cout << "Please login first!\n";
                }
                break;
            case 5:
                if (loggedIn) viewExpenses();
                else cout << "Please login first!\n";
                break;
            case 6:
                if (loggedIn) categoryReport();
                else cout << "Please login first!\n";
                break;
            case 7:
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
