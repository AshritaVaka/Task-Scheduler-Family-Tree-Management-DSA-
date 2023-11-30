
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Task {
    string name;
    int priority;
    int burstTime;
};

// Comparator for the priority queue
struct CompareTaskPriority {
    bool operator()(const Task& t1, const Task& t2) {
        // Higher priority tasks have higher values
        return t1.priority > t2.priority;
    }
};

int main() {
    int quantum;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    priority_queue<Task, vector<Task>, CompareTaskPriority> taskQueue;  // Ready Queue
    Task taskHold;
    taskHold.burstTime = -1;  // Initialize burst time to -1 to indicate no task is held.

    while (true) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. Add a new task\n";
        cout << "2. Execute tasks\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Task task;
            cout << "Enter task name: ";
            cin >> task.name;
            cout << "Enter task priority (higher number is lower priority): ";
            cin >> task.priority;
            cout << "Enter burst time for the task: ";
            cin >> task.burstTime;

            taskQueue.push(task);
        } else if (choice == 2) {
            if (taskQueue.empty() && taskHold.burstTime == -1) {
                cout << "No tasks to execute." << endl;
                continue;
            }

            if (taskHold.burstTime != -1) {
                // If a task is already being held, push it back into the queue
                taskQueue.push(taskHold);
                taskHold.burstTime = -1;
            }

            if (!taskQueue.empty()) {
                Task currentTask = taskQueue.top();
                taskQueue.pop();

                cout << "Executing task: " << currentTask.name << " (Priority: " << currentTask.priority << ", Burst Time: " << currentTask.burstTime << ")\n";

                if (currentTask.burstTime > quantum) {
                    currentTask.burstTime -= quantum;
                    cout << "Task partially executed. Remaining burst time: " << currentTask.burstTime << "\n";
                    taskHold = currentTask;
                } else {
                    cout << "Task completed.\n";
                }
            } else {
                cout << "No tasks in the ready queue." << endl;
            }
        } else if (choice == 3) {
            break; // Exit the program
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
