#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact(const string& name, const string& phone, const string& email)
        : name(name), phone(phone), email(email) {}
    
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
    
    void setPhone(const string& phone) { this->phone = phone; }
    void setEmail(const string& email) { this->email = email; }
    
    void display() const {
        cout << "Name: " << name << ", Phone: " << phone << ", Email: " << email << endl;
    }
    
    bool operator==(const string& otherName) const {
        return name == otherName;
    }
};

class ContactManager {
private:
    vector<Contact> contacts;
    
public:
    void addContact(const string& name, const string& phone, const string& email) {
        contacts.emplace_back(name, phone, email);
        cout << "Contact added successfully!\n";
    }
    
    void displayAllContacts() const {
        if (contacts.empty()) {
            cout << "No contacts found.\n";
            return;
        }
        for (const auto& contact : contacts) {
            contact.display();
        }
    }
    
    Contact* findContact(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [&name](const Contact& c) { return c.getName() == name; });
        return (it != contacts.end()) ? &(*it) : nullptr;
    }
    
    bool updateContact(const string& name, const string& phone, const string& email) {
        Contact* contact = findContact(name);
        if (contact) {
            contact->setPhone(phone);
            contact->setEmail(email);
            cout << "Contact updated successfully!\n";
            return true;
        }
        cout << "Contact not found!\n";
        return false;
    }
    
    bool deleteContact(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(),
            [&name](const Contact& c) { return c.getName() == name; });
        if (it != contacts.end()) {
            contacts.erase(it);
            cout << "Contact deleted successfully!\n";
            return true;
        }
        cout << "Contact not found!\n";
        return false;
    }
};

int main() {
    ContactManager cm;
    cm.addContact("Alice", "123-456-7890", "alice@email.com");
    cm.addContact("Bob", "098-765-4321", "bob@email.com");
    cm.displayAllContacts();
    cm.updateContact("Alice", "111-222-3333", "alice.new@email.com");
    cm.deleteContact("Bob");
    cm.displayAllContacts();
    return 0;
}