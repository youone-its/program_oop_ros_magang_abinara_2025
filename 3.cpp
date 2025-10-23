#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Employee {
private:
    int empId;
    string name;
    string department;
    double salary;

public:
    Employee(int empId, const string& name, const string& department, double salary)
        : empId(empId), name(name), department(department), salary(salary) {}
    
    int getEmpId() const { return empId; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    double getSalary() const { return salary; }
    
    void setDepartment(const string& dept) { department = dept; }
    void setSalary(double salary) { this->salary = salary; }
    
    void display() const {
        cout << "ID: " << empId << ", Name: " << name 
                  << ", Department: " << department << ", Salary: $" << salary << endl;
    }
};

class EmployeeManager {
private:
    vector<Employee> employees;
    
public:
    void hireEmployee(int empId, const string& name, const string& department, double salary) {
        employees.emplace_back(empId, name, department, salary);
        cout << "Employee hired successfully!\n";
    }
    
    void displayAllEmployees() const {
        if (employees.empty()) {
            cout << "No employees found.\n";
            return;
        }
        for (const auto& emp : employees) {
            emp.display();
        }
    }
    
    Employee* findEmployee(int empId) {
        auto it = find_if(employees.begin(), employees.end(),
            [empId](const Employee& e) { return e.getEmpId() == empId; });
        return (it != employees.end()) ? &(*it) : nullptr;
    }
    
    bool updateEmployee(int empId, const string& department, double salary) {
        Employee* emp = findEmployee(empId);
        if (emp) {
            emp->setDepartment(department);
            emp->setSalary(salary);
            cout << "Employee updated successfully!\n";
            return true;
        }
        cout << "Employee not found!\n";
        return false;
    }
    
    bool fireEmployee(int empId) {
        auto it = find_if(employees.begin(), employees.end(),
            [empId](const Employee& e) { return e.getEmpId() == empId; });
        if (it != employees.end()) {
            employees.erase(it);
            cout << "Employee fired successfully!\n";
            return true;
        }
        cout << "Employee not found!\n";
        return false;
    }
};

int main() {
    EmployeeManager em;
    em.hireEmployee(101, "John", "IT", 75000);
    em.hireEmployee(102, "Sarah", "HR", 65000);
    em.displayAllEmployees();
    em.updateEmployee(101, "IT", 80000);
    em.fireEmployee(102);
    em.displayAllEmployees();
    return 0;
}