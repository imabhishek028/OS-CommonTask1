#include <iostream>
#include <vector>
#include <algorithm>

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;

    Process(int id, int at, int bt)
        : pid(id), arrival_time(at), burst_time(bt), waiting_time(0), turnaround_time(0) {}
};

void fifo_scheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        process.waiting_time = current_time - process.arrival_time;
        process.turnaround_time = process.waiting_time + process.burst_time;
        current_time += process.burst_time;

        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
    }

    double avg_waiting_time = (double)total_waiting_time / processes.size();
    double avg_turnaround_time = (double)total_turnaround_time / processes.size();

    std::cout << "Average Waiting Time: " << avg_waiting_time << std::endl;
    std::cout << "Average Turnaround Time: " << avg_turnaround_time << std::endl;
}

int main() {
    std::vector<Process> processes = {
        Process(1, 0, 4),
        Process(2, 1, 3),
        Process(3, 2, 1),
        Process(4, 3, 2)
    };

    fifo_scheduling(processes);

    return 0;
}
