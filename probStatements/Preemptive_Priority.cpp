#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int pid, at, bt, priority;
    int remaining_bt;
    int ft, tat, wt;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter AT, BT & Priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
        p[i].pid = i + 1;
        p[i].remaining_bt = p[i].bt;
    }

    int completed = 0, time = 0;

    while (completed != n)
    {
        int idx = -1;
        int best_priority = 1e9;

        // Find process with highest priority (lowest value)
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].remaining_bt > 0)
            {
                if (p[i].priority < best_priority)
                {
                    best_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].remaining_bt--;

            // If finished
            if (p[idx].remaining_bt == 0)
            {
                p[idx].ft = time + 1;
                completed++;
            }
        }

        time++;
    }

    // Calculate TAT and WT
    cout << "\nPID\tAT\tBT\tPri\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ft - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].priority << "\t"
             << p[i].ft << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;
    }

    return 0;
}
