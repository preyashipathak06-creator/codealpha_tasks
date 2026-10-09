
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() {
        cout << left << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << details << endl;
    }
};

// Account class
class Account {
public:
    int accountNumber;
    double balance;
    vector<Transaction> history;

    Account(int number, double initialBalance) {
        accountNumber = number;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        history.push_back(
            Transaction("Deposit", amount, "Money deposited")
        );

        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
        } else if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            history.push_back(
                Transaction("Withdrawal", amount, "Money withdrawn")
            );

            cout << "Withdrawal successful!\n";
        }
    }

    bool transfer(Account &receiver, double amount) {
        if (amount <= 0) {
            cout << "Invalid transfer amount!\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance for transfer!\n";
            return false;
        }

        balance -= amount;
        receiver.balance += amount;

        history.push_back(
            Transaction("Transfer Out", amount,
                        "To account " +
                        to_string(receiver.accountNumber))
        );

        receiver.history.push_back(
            Transaction("Transfer In", amount,
                        "From account " +
                        to_string(accountNumber))
        );

        cout << "Transfer successful!\n";
        return true;
    }

    void showBalance() {
        cout << fixed << setprecision(2);
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAvailable Balance: Rs. " << balance << endl;
    }

    void showTransactions() {
        cout << "\n========== TRANSACTION HISTORY ==========\n";

        if (history.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        cout << left << setw(15) << "Type"
             << setw(12) << "Amount"
             << "Details\n";

        int start = history.size() > 5
                    ? history.size() - 5 : 0;

        for (int i = start; i < (int)history.size(); i++) {
            history[i].display();
        }
    }
};

// Customer class
class Customer {
public:
    string name;
    int customerId;
    Account account;

    Customer(string n, int id, int accNo, double initialBalance)
        : name(n), customerId(id),
          account(accNo, initialBalance) {}

    void displayCustomer() {
        cout << "\nCustomer Name: " << name;
        cout << "\nCustomer ID: " << customerId;
        account.showBalance();
    }
};

int main() {
    string name1, name2;
    int choice;
    double amount;

    cout << "===== BANKING SYSTEM =====\n";

    cout << "Enter first customer's name: ";
    getline(cin, name1);

    cout << "Enter second customer's name: ";
    getline(cin, name2);

    Customer c1(name1, 101, 1001, 5000.00);
    Customer c2(name2, 102, 1002, 3000.00);

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Display customer details\n";
        cout << "2. Deposit money\n";
        cout << "3. Withdraw money\n";
        cout << "4. Transfer money\n";
        cout << "5. Check account balance\n";
        cout << "6. View transaction history\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                cout << "Enter customer ID (101 or 102): ";
                cin >> id;

                if (id == 101)
                    c1.displayCustomer();
                else if (id == 102)
                    c2.displayCustomer();
                else
                    cout << "Customer not found!\n";
                break;
            }

            case 2: {
                int id;
                cout << "Enter account number (1001 or 1002): ";
                cin >> id;
                cout << "Enter deposit amount: ";
                cin >> amount;

                if (id == 1001)
                    c1.account.deposit(amount);
                else if (id == 1002)
                    c2.account.deposit(amount);
                else
                    cout << "Account not found!\n";
                break;
            }

            case 3: {
                int id;
                cout << "Enter account number (1001 or 1002): ";
                cin >> id;
                cout << "Enter withdrawal amount: ";
                cin >> amount;

                if (id == 1001)
                    c1.account.withdraw(amount);
                else if (id == 1002)
                    c2.account.withdraw(amount);
                else
                    cout << "Account not found!\n";
                break;
            }

            case 4: {
                int sender, receiver;
                cout << "Enter sender account (1001 or 1002): ";
                cin >> sender;
                cout << "Enter receiver account (1001 or 1002): ";
                cin >> receiver;
                cout << "Enter transfer amount: ";
                cin >> amount;

                if (sender == 1001 && receiver == 1002)
                    c1.account.transfer(c2.account, amount);
                else if (sender == 1002 && receiver == 1001)
                    c2.account.transfer(c1.account, amount);
                else
                    cout << "Invalid sender or receiver account!\n";
                break;
            }

            case 5: {
                int id;
                cout << "Enter account number (1001 or 1002): ";
                cin >> id;

                if (id == 1001)
                    c1.account.showBalance();
                else if (id == 1002)
                    c2.account.showBalance();
                else
                    cout << "Account not found!\n";
                break;
            }

            case 6: {
                int id;
                cout << "Enter account number (1001 or 1002): ";
                cin >> id;

                if (id == 1001)
                    c1.account.showTransactions();
                else if (id == 1002)
                    c2.account.showTransactions();
                else
                    cout << "Account not found!\n";
                break;
            }

            case 7:
                cout << "Thank you for using our Banking System!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}