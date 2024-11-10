#include<iostream>
#include<string>
using namespace std;
class Task {
private:
    string description;
    bool completed;

public:
    Task(const string& desc) : description(desc), completed(false) {}

    void markCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    string getDescription() const {
        return description;
    }
};

class TodoList {
private:
    Task** tasks;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        Task** newTasks = new Task * [capacity];
        for (int i = 0; i < size; ++i) {
            newTasks[i] = tasks[i];
        }
        delete[] tasks;
        tasks = newTasks;
    }

public:
    TodoList(int initialCapacity = 5) : capacity(initialCapacity), size(0) {
        tasks = new Task * [capacity];
    }

    ~TodoList() {
        for (int i = 0; i < size; ++i) {
            delete tasks[i];
        }
        delete[] tasks;
    }

    void addTask(const string& description) {
        if (size == capacity) {
            resize();
        }
        tasks[size++] = new Task(description);
    }

    void markTaskCompleted(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid task number.\n";
            return;
        }
        tasks[index]->markCompleted();
        cout << "Task " << index + 1 << " marked as completed.\n";
    }

    void displayTasks() const {
        if (size == 0) {
            cout << "No tasks to display.\n";
            return;
        }
        for (int i = 0; i < size; ++i) {
            cout << i + 1 << ". " << tasks[i]->getDescription();
            if (tasks[i]->isCompleted()) {
                cout << " [Completed]";
            }
            cout << "\n";
        }
    }
};

int main() {
    TodoList todoList;
    int choice;

    while (true) {
        cout << "\n1. Add Task\n2. Mark Task as Completed\n3. View Tasks\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            cin.ignore();
            string description;
            cout << "Enter task description: ";
            getline(cin, description);
            todoList.addTask(description);
            break;
        }
        case 2: {
            int taskNumber;
            cout << "Enter task number to mark as completed: ";
            cin >> taskNumber;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            todoList.markTaskCompleted(taskNumber - 1);
            break;
        }
        case 3:
            todoList.displayTasks();
            break;
        case 4:
            cout << "Exiting the application.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
