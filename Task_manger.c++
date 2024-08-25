#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(const string& desc) : description(desc), completed(false) {}

    void markComplete() {
        completed = true;
    }
};

class TaskManager {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    TaskManager() {
        loadTasks();
    }

    void addTask(const string& description) {
        Task newTask(description);
        tasks.push_back(newTask);
        saveTasks();
    }

    void markTaskComplete(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markComplete();
            saveTasks();
        }
    }

    void displayTasks() {
        cout << "Tasks:\n";
        cout << setw(4) << "Index" << setw(25) << "Description" << setw(12) << "Status" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << setw(4) << i + 1 << setw(25) << tasks[i].description << setw(12) 
                 << (tasks[i].completed ? "Completed" : "Incomplete") << endl;
        }
        cout << "--------------------------\n";
    }

private:
    void loadTasks() {
        ifstream file(filename);
        if (file.is_open()) {
            Task task("");
            while (getline(file, task.description)) {
                file >> task.completed;
                tasks.push_back(task);
                file.ignore();  // Consume the newline character
            }
            file.close();
        }
    }

    void saveTasks() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.description << endl << task.completed << endl;
            }
            file.close();
        }
    }
};

int main() {
    TaskManager taskManager;

    while (true) {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Complete\n";
        cout << "3. Display Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();  // Clear the input buffer
                cout << "Enter task description: ";
                string description;
                getline(cin, description);
                taskManager.addTask(description);
                break;
            }
            case 2: {
                int index;
                cout << "Enter task index to mark as complete: ";
                cin >> index;
                taskManager.markTaskComplete(index - 1);
                break;
            }
            case 3:
                taskManager.displayTasks();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
