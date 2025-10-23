#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Task {
private:
    int taskId;
    string description;
    bool completed;

public:
    Task(int taskId, const string& description) 
        : taskId(taskId), description(description), completed(false) {}
    
    int getTaskId() const { return taskId; }
    string getDescription() const { return description; }
    bool isCompleted() const { return completed; }
    
    void setDescription(const string& desc) { description = desc; }
    void setCompleted(bool completed) { this->completed = completed; }
    
    void display() const {
        cout << "Task " << taskId << ": " << description 
                  << " [" << (completed ? "Completed" : "Pending") << "]" << endl;
    }
};

class TaskManager {
private:
    vector<Task> tasks;
    
public:
    void addTask(int taskId, const string& description) {
        tasks.emplace_back(taskId, description);
        cout << "Task added successfully!\n";
    }
    
    void displayAllTasks() const {
        if (tasks.empty()) {
            cout << "No tasks found.\n";
            return;
        }
        for (const auto& task : tasks) {
            task.display();
        }
    }
    
    Task* findTask(int taskId) {
        auto it = find_if(tasks.begin(), tasks.end(),
            [taskId](const Task& t) { return t.getTaskId() == taskId; });
        return (it != tasks.end()) ? &(*it) : nullptr;
    }
    
    bool updateTask(int taskId, const string& description, bool completed) {
        Task* task = findTask(taskId);
        if (task) {
            task->setDescription(description);
            task->setCompleted(completed);
            cout << "Task updated successfully!\n";
            return true;
        }
        cout << "Task not found!\n";
        return false;
    }
    
    bool deleteTask(int taskId) {
        auto it = find_if(tasks.begin(), tasks.end(),
            [taskId](const Task& t) { return t.getTaskId() == taskId; });
        if (it != tasks.end()) {
            tasks.erase(it);
            cout << "Task deleted successfully!\n";
            return true;
        }
        cout << "Task not found!\n";
        return false;
    }
};

int main() {
    TaskManager tm;
    tm.addTask(1, "Complete project proposal");
    tm.addTask(2, "Review code");
    tm.displayAllTasks();
    tm.updateTask(1, "Complete project proposal", true);
    tm.deleteTask(2);
    tm.displayAllTasks();
    return 0;
}