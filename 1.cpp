#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Student {
private:
    int id;
    string name;
    double grade;

public:
    Student(int id, const string& name, double grade) 
        : id(id), name(name), grade(grade) {}
    
    int getId() const { return id; }
    string getName() const { return name; }
    double getGrade() const { return grade; }
    
    void setName(const string& name) { this->name = name; }
    void setGrade(double grade) { this->grade = grade; }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Grade: " << grade << endl;
    }
};

class StudentManager {
private:
    vector<Student> students;
    
public:
    // Create
    void addStudent(int id, const string& name, double grade) {
        students.emplace_back(id, name, grade);
        cout << "Student added successfully!\n";
    }
    
    // Read
    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students found.\n";
            return;
        }
        for (const auto& student : students) {
            student.display();
        }
    }
    
    Student* findStudent(int id) {
        auto it = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.getId() == id; });
        return (it != students.end()) ? &(*it) : nullptr;
    }
    
    // Update
    bool updateStudent(int id, const string& name, double grade) {
        Student* student = findStudent(id);
        if (student) {
            student->setName(name);
            student->setGrade(grade);
            cout << "Student updated successfully!\n";
            return true;
        }
        cout << "Student not found!\n";
        return false;
    }
    
    // Delete
    bool deleteStudent(int id) {
        auto it = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            students.erase(it);
            cout << "Student deleted successfully!\n";
            return true;
        }
        cout << "Student not found!\n";
        return false;
    }
};

int main() {
    StudentManager manager;
    manager.addStudent(1, "Alice", 85.5);
    manager.addStudent(2, "Bob", 92.0);
    manager.displayAllStudents();
    manager.updateStudent(1, "Alice Johnson", 88.0);
    manager.deleteStudent(2);
    manager.displayAllStudents();
    return 0;
}