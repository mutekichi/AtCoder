#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <utility>
#include <complex>
#include <climits>
#include <cfloat>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Task {
    int deadline;
    int cost;
    long long score;
};

long long solve_O_factorial(const vector<Task> &tasks) {
    
    int task_num = tasks.size();

    vector<int> task_order(task_num);
    iota(task_order.begin(), task_order.end(), 0);

    long long scores_max = 0;

    do {
        int current_date = 0;
        long long scores = 0;
        
        for (int i = 0; i < task_num; ++i) {
            Task task = tasks[task_order[i]];
            if (current_date + task.cost <= task.deadline) {
                scores += task.score;
                current_date += task.cost;
            }
        }

        scores_max = max(scores_max, scores);

    } while (next_permutation(task_order.begin(), task_order.end()));

    return scores_max;
}

void sort_tasks(vector<Task> &tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task &task1, const Task &task2) {
        if (task1.deadline != task2.deadline) return task1.deadline < task2.deadline;
        else return task1.cost > task2.cost;
    });
}

bool check_tasks_executable(const vector<Task> &tasks) {
    int current_date = 0;
    for (int i = 0; i < tasks.size(); ++i) {
        if (current_date + tasks[i].cost > tasks[i].deadline) {
            return false; 
        } else {
            current_date += tasks[i].cost;
        }
    }
    return true;
}

long long calc_score_sum(const vector<Task> &tasks) {
    long long score_sum = 0;
    for (int i = 0; i < tasks.size(); ++i) {
        score_sum += tasks[i].score;
    }
    return score_sum;
}

long long solve_O_exponential(const vector<Task> &tasks) {
    int task_num = tasks.size();

    long long scores_max = 0;

    vector<Task> tasks_sorted = tasks;
    sort_tasks(tasks_sorted);

    for (int bits = 0; bits < (1<<task_num); ++bits) {
        vector<Task> tasks_to_do;

        for (int i = 0; i < task_num; ++i) {
            if (bits & (1<<i)) {
                tasks_to_do.push_back(tasks_sorted[i]);
            }
        }
        if (check_tasks_executable(tasks_to_do)) {
            scores_max = max(scores_max, calc_score_sum(tasks_to_do));
        }
    }

    return scores_max;
}

long long solve_O_NmaxD(const vector<Task> &tasks) {
    int task_num = tasks.size();

    vector<Task> tasks_sorted = tasks;
    sort_tasks(tasks_sorted);

    const int DP_TABLE_SIZE = 5010;

    vector<vector<long long>> dp(DP_TABLE_SIZE, vector<long long>(DP_TABLE_SIZE, 0));

    for (int i = 1; i < task_num + 1; ++i) {
        const Task task = tasks_sorted[i - 1];
        for (int j = 0; j < DP_TABLE_SIZE; ++j) {
            if (task.cost > j || task.deadline < j) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - task.cost] + task.score);
        }
    }

    long long max_score = 0;

    // for (int i = 0; i <task_num + 1; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < DP_TABLE_SIZE; ++i) {
        max_score = max(dp[task_num][i], max_score);
    }


    return max_score;
}

int main() {

    int n;
    cin >> n;

    vector<Task> tasks(n);

    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].deadline >> tasks[i].cost >> tasks[i].score;
    }

    if (n <= 8) cout << solve_O_factorial(tasks) << endl;
    else if (n <= 20) cout << solve_O_exponential(tasks) << endl;
    else cout << solve_O_NmaxD(tasks) << endl;
    
    return 0;
}