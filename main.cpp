#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

// Task class representing a task with name, priority, and burst time
class Task {
public:
    std::string name;
    int priority;
    int burstTime;

    Task(const std::string& n, int p, int burst)
        : name(n), priority(p), burstTime(burst) {}
};

// Scheduler interface with a function for scheduling tasks
class Scheduler {
public:
    virtual void scheduleTasks(const std::vector<Task>& tasks) = 0;
};

// First-Come, First-Served (FCFS) scheduling algorithm
class FCFS : public Scheduler {
public:
    void scheduleTasks(const std::vector<Task>& tasks) {
        std::cout << "FCFS Scheduling:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            const Task& task = tasks[i];
            std::cout << "Executing task: " << task.name << "\n";
        }
        std::cout << "\n";
    }
};

// Shortest-Job-First (SJF) scheduling algorithm
class SJF : public Scheduler {
public:
    void scheduleTasks(const std::vector<Task>& tasks) {
        std::cout << "SJF Scheduling:\n";
        std::vector<Task> sortedTasks = tasks;
        std::sort(sortedTasks.begin(), sortedTasks.end(), CompareBurstTime());
        for (size_t i = 0; i < sortedTasks.size(); ++i) {
            const Task& task = sortedTasks[i];
            std::cout << "Executing task: " << task.name << "\n";
        }
        std::cout << "\n";
    }

private:
    struct CompareBurstTime {
        bool operator()(const Task& a, const Task& b) const {
            return a.burstTime < b.burstTime;
        }
    };
};

// Priority Scheduling algorithm
class PriorityScheduling : public Scheduler {
public:
    void scheduleTasks(const std::vector<Task>& tasks) {
        std::cout << "Priority Scheduling:\n";
        std::vector<Task> sortedTasks = tasks;
        std::sort(sortedTasks.begin(), sortedTasks.end(), ComparePriority());
        for (size_t i = 0; i < sortedTasks.size(); ++i) {
            const Task& task = sortedTasks[i];
            std::cout << "Executing task: " << task.name << "\n";
        }
        std::cout << "\n";
    }

private:
    struct ComparePriority {
        bool operator()(const Task& a, const Task& b) const {
            return a.priority > b.priority;
        }
    };
};

// Round-Robin scheduling algorithm
class RoundRobin : public Scheduler {
public:
    void scheduleTasks(const std::vector<Task>& tasks) {
        std::cout << "Round-Robin Scheduling:\n";
        const int timeQuantum = 10;
        std::deque<Task> taskQueue(tasks.begin(), tasks.end());
        while (!taskQueue.empty()) {
            Task task = taskQueue.front();
            taskQueue.pop_front();
            if (task.burstTime > timeQuantum) {
                task.burstTime -= timeQuantum;
                taskQueue.push_back(task);
            } else {
                std::cout << "Executing task: " << task.name << "\n";
            }
        }
        std::cout << "\n";
    }
};

// Priority with Round-Robin scheduling algorithm
class PriorityWithRR : public Scheduler {
public:
    void scheduleTasks(const std::vector<Task>& tasks) {
        std::cout << "Priority with Round-Robin Scheduling:\n";
        const int timeQuantum = 10;
        std::deque<Task> taskQueue(tasks.begin(), tasks.end());
        while (!taskQueue.empty()) {
            Task task = taskQueue.front();
            taskQueue.pop_front();
            if (task.burstTime > timeQuantum) {
                task.burstTime -= timeQuantum;
                taskQueue.push_back(task);
            } else {
                std::cout << "Executing task: " << task.name << "\n";
            }
        }
        std::cout << "\n";
    }
};

int main() {
    // Open the input file "schedule.txt"
    std::ifstream file("schedule.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'schedule.txt'. Please make sure the file is in the correct location.\n";
        return 1;
    }

    // Read task data from the file and store in a vector of Task objects
    std::vector<Task> tasks;
    std::string name;
    int priority, burstTime;

    while (file >> name >> priority >> burstTime) {
        tasks.push_back(Task(name, priority, burstTime));
    }

    // Create instances of scheduling algorithms
    FCFS fcfs;
    SJF sjf;
    PriorityScheduling priorityScheduling;
    RoundRobin roundRobin;
    PriorityWithRR priorityWithRR;

    // Execute scheduling algorithms
    fcfs.scheduleTasks(tasks);
    sjf.scheduleTasks(tasks);
    priorityScheduling.scheduleTasks(tasks);
    roundRobin.scheduleTasks(tasks);
    priorityWithRR.scheduleTasks(tasks);

    return 0;
}

