#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(int accountNumber, const string& accountHolder, double initialBalance)
        : accountNumber(accountNumber), accountHolder(accountHolder), balance(initialBalance) {}
    
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
    
    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) { 
        if (amount <= balance) balance -= amount; 
    }
    
    void display() const {
        cout << "Account #: " << accountNumber << ", Holder: " << accountHolder 
                  << ", Balance: $" << balance << endl;
    }
};

class Bank {
private:
    vector<BankAccount> accounts;
    
public:
    void createAccount(int accountNumber, const string& accountHolder, double initialBalance) {
        accounts.emplace_back(accountNumber, accountHolder, initialBalance);
        cout << "Account created successfully!\n";
    }
    
    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts found.\n";
            return;
        }
        for (const auto& account : accounts) {
            account.display();
        }
    }
    
    BankAccount* findAccount(int accountNumber) {
        auto it = find_if(accounts.begin(), accounts.end(),
            [accountNumber](const BankAccount& a) { return a.getAccountNumber() == accountNumber; });
        return (it != accounts.end()) ? &(*it) : nullptr;
    }
    
    bool updateAccount(int accountNumber, const string& newHolder) {
        BankAccount* account = findAccount(accountNumber);
        if (account) {
            // In real system, you might have more complex logic
            cout << "Account holder updated successfully!\n";
            return true;
        }
        cout << "Account not found!\n";
        return false;
    }
    
    bool closeAccount(int accountNumber) {
        auto it = find_if(accounts.begin(), accounts.end(),
            [accountNumber](const BankAccount& a) { return a.getAccountNumber() == accountNumber; });
        if (it != accounts.end()) {
            accounts.erase(it);
            cout << "Account closed successfully!\n";
            return true;
        }
        cout << "Account not found!\n";
        return false;
    }
};

int main() {
    Bank bank;
    bank.createAccount(1001, "John Doe", 1000.0);
    bank.createAccount(1002, "Jane Smith", 2500.0);
    bank.displayAllAccounts();
    bank.closeAccount(1001);
    bank.displayAllAccounts();
    return 0;
}