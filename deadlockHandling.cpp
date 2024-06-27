#include <iostream>
#include <vector>

bool is_deadlock(int n, int m, std::vector<int>& available, std::vector<std::vector<int>>& max_demand, std::vector<std::vector<int>>& allocation) {
    std::vector<std::vector<int>> need(n, std::vector<int>(m));
    std::vector<bool> finish(n, false);
    std::vector<int> work = available;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max_demand[i][j] - allocation[i][j];
        }
    }

    while (true) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool can_finish = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }
                if (can_finish) {
                    for (int j = 0; j < m; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!finish[i]) {
            return true; 
        }
    }
    return false;
}

int main() {
    int n = 5;  
    int m = 3;  

    std::vector<int> available = {3, 3, 2};
    std::vector<std::vector<int>> max_demand = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    std::vector<std::vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    if (is_deadlock(n, m, available, max_demand, allocation)) {
        std::cout << "Deadlock detected." << std::endl;
    } else {
        std::cout << "No deadlock detected." << std::endl;
    }
    return 0;
}
