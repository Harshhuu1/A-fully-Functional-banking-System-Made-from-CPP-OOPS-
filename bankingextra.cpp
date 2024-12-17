#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class BankAccount {
    int accountNumber;
    string accountHolderName;
    char accountType;
    double balance;

public:
    void createAccount() {
        cout << "\nEnter the Account Number: ";
        cin >> accountNumber;
        cin.ignore(); // To clear the newline from the buffer
        cout << "\nEnter the Account Holder's Name: ";
        getline(cin, accountHolderName);
        cout << "\nEnter Account Type (C/S): ";
        cin >> accountType;
        accountType = toupper(accountType);
        cout << "\nEnter Initial Deposit (>=500 for Savings and >=1000 for Current): ";
        cin >> balance;
        cout << "\nAccount Created Successfully!\n";
    }

    void displayAccount() const {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder Name: " << accountHolderName;
        cout << "\nAccount Type: " << accountType;
        cout << "\nBalance: " << fixed << setprecision(2) << balance << endl;
    }

    void modifyAccount() {
        cout << "\nEnter New Account Holder Name: ";
        cin.ignore();
        getline(cin, accountHolderName);
        cout << "\nEnter New Account Type (C/S): ";
        cin >> accountType;
        accountType = toupper(accountType);
        cout << "\nEnter New Balance: ";
        cin >> balance;
        cout << "\nAccount Modified Successfully!\n";
    }

    void deposit(double amount) {
        balance += amount;
        cout << "\nAmount Deposited Successfully!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "\nInsufficient Balance!\n";
        } else {
            balance -= amount;
            cout << "\nAmount Withdrawn Successfully!\n";
        }
    }

    void displayReport() const {
        cout << accountNumber << setw(20) << accountHolderName << setw(10) << accountType << setw(12) << fixed << setprecision(2) << balance << endl;
    }

    int getAccountNumber() const { return accountNumber; }
};

void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAllAccounts();
void depositOrWithdraw(int, int);

int main() {
    char choice;
    int accountNumber;

    do {
        cout << "\n\n\t\tBank Management System";
        cout << "\n\t1. Create New Account";
        cout << "\n\t2. Deposit Money";
        cout << "\n\t3. Withdraw Money";
        cout << "\n\t4. Balance Inquiry";
        cout << "\n\t5. Display All Accounts";
        cout << "\n\t6. Close an Account";
        cout << "\n\t7. Modify an Account";
        cout << "\n\t8. Exit";
        cout << "\n\nEnter Your Choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case '1': writeAccount(); break;
            case '2': 
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                depositOrWithdraw(accountNumber, 1);
                break;
            case '3': 
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                depositOrWithdraw(accountNumber, 2);
                break;
            case '4': 
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                displayAccount(accountNumber);
                break;
            case '5': displayAllAccounts(); break;
            case '6': 
                cout << "\nEnter Account Number to Close: ";
                cin >> accountNumber;
                deleteAccount(accountNumber);
                break;
            case '7': 
                cout << "\nEnter Account Number to Modify: ";
                cin >> accountNumber;
                modifyAccount(accountNumber);
                break;
            case '8': cout << "\nThank you for using the Bank Management System!\n"; break;
            default: cout << "\nInvalid Choice! Please try again.\n";
        }
        cin.ignore();
        cin.get();
    } while (choice != '8');

    return 0;
}

void writeAccount() {
    BankAccount account;
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    account.createAccount();
    outFile.write(reinterpret_cast<const char*>(&account), sizeof(BankAccount));
    outFile.close();
}

void displayAccount(int accountNumber) {
    BankAccount account;
    ifstream inFile("accounts.dat", ios::binary);
    bool found = false;

    if (!inFile) {
        cout << "\nFile could not be opened!";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        if (account.getAccountNumber() == accountNumber) {
            account.displayAccount();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}

void modifyAccount(int accountNumber) {
    BankAccount account;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    if (!file) {
        cout << "\nFile could not be opened!";
        return;
    }

    while (!file.eof() && file.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        if (account.getAccountNumber() == accountNumber) {
            account.displayAccount();
            cout << "\nEnter New Details:\n";
            account.modifyAccount();
            file.seekp(-static_cast<int>(sizeof(BankAccount)), ios::cur);
            file.write(reinterpret_cast<const char*>(&account), sizeof(BankAccount));
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}

void deleteAccount(int accountNumber) {
    BankAccount account;
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    if (!inFile) {
        cout << "\nFile could not be opened!";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        if (account.getAccountNumber() == accountNumber) {
            found = true;
        } else {
            outFile.write(reinterpret_cast<const char*>(&account), sizeof(BankAccount));
        }
    }
    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) {
        cout << "\nAccount Deleted Successfully!\n";
    } else {
        cout << "\nAccount Not Found!\n";
    }
}

void displayAllAccounts() {
    BankAccount account;
    ifstream inFile("accounts.dat", ios::binary);

    if (!inFile) {
        cout << "\nFile could not be opened!";
        return;
    }

    cout << "\n\n\tAccount Holder List\n\n";
    cout << "====================================================\n";
    cout << "Account No.      Name        Type     Balance\n";
    cout << "====================================================\n";

    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        account.displayReport();
    }
    inFile.close();
}

void depositOrWithdraw(int accountNumber, int option) {
    BankAccount account;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    double amount;

    if (!file) {
        cout << "\nFile could not be opened!";
        return;
    }

    while (!file.eof() && file.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        if (account.getAccountNumber() == accountNumber) {
            account.displayAccount();
            if (option == 1) {
                cout << "\nEnter Amount to Deposit: ";
                cin >> amount;
                account.deposit(amount);
            } else if (option == 2) {
                cout << "\nEnter Amount to Withdraw: ";
                cin >> amount;
                account.withdraw(amount);
            }
            file.seekp(-static_cast<int>(sizeof(BankAccount)), ios::cur);
            file.write(reinterpret_cast<const char*>(&account), sizeof(BankAccount));
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }
}
