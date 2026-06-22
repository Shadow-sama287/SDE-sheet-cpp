## [Job Sequencing Problem](https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1)

## [Job Sequencing Problem- TUF](https://takeuforward.org/data-structure/job-sequencing-problem)

You are given two arrays: deadline[], and profit[], which represent a set of jobs, where each job is associated with a deadline, and a profit. Each job takes 1 unit of time to complete, and only one job can be scheduled at a time. You will earn the profit associated with a job only if it is completed by its deadline.

Your task is to find:

1. The maximum number of jobs that can be completed within their deadlines.
2. The total maximum profit earned by completing those jobs.

**Examples :**

```
Input: deadline[] = [4, 1, 1, 1], profit[] = [20, 10, 40, 30]
Output: [2, 60]
Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).
```

```
Input: deadline[] = [2, 1, 2, 1, 1], profit[] = [100, 19, 27, 25, 15]
Output: [2, 127]
Explanation: Job1 and Job3 can be done with maximum profit of 127 (100+27).
```

```
Input: deadline[] = [3, 1, 2, 2], profit[] = [50, 10, 20, 30]
Output: [3, 100]
Explanation: Job1, Job3 and Job4 can be completed with a maximum profit of 100 (50 + 20 + 30).
```

Constraints:

```
1 ≤ deadline.size() = profit.size() ≤ 105
1 ≤ deadline[i] ≤ deadline.size()
1 ≤ profit[i] ≤ 500
```

---

You are given a set of n jobs, each with a unique job ID, a deadline, and a profit associated with it. Each job takes exactly one unit of time to complete, and only one job can be scheduled at any given time. The goal is to schedule jobs in a way that maximizes the total profit while ensuring no job misses its deadline. Each job must be completed by its deadline to earn the associated profit.

 

### Intuition

The intuition behind this approach is to maximize profit by completing the most profitable jobs within their respective deadlines. Sorting the jobs by profit allows us to prioritize higher-profit jobs and find optimal scheduling that meets deadlines.

 

### Approach Steps

- Sort Jobs by Profit: Begin by sorting the list of jobs in descending order based on their profit, allowing us to focus on the most profitable jobs first.
- Determine Maximum Deadline: Calculate the maximum deadline across all jobs to determine the size of the scheduling array.
- Create Scheduling Array: Initialize an array to track occupied time slots. The array's length equals the maximum deadline, with each index representing a time slot.
- Schedule Jobs:
  - For each job in the sorted list, attempt to schedule it in the latest possible slot before its deadline.
  - If the job’s deadline slot is available, schedule the job, mark the slot as occupied, and add the job's profit to the total profit.
  - If the deadline slot is occupied, look for earlier slots. If a free slot is found, schedule the job there.
  - Break Early: If the number of jobs scheduled equals the number of available slots (maximum deadline), break the loop early as no further scheduling is possible.
  - Return Results: After scheduling, return the total number of jobs scheduled and the total profit earned.

### Time Complexity

```
Sorting Jobs: Takes O(n log n) time.

Scheduling Jobs: In the worst case, scheduling each job might require backtracking through the scheduling array, leading to O(n * max_deadline) time.

Thus, the overall time complexity is O(n * max_deadline).
```

### Space Complexity

```
The space complexity is O(max_deadline) due to the scheduling array used to track available slots.
```

### Why This Approach?

This approach ensures we maximize profits while meeting all job deadlines. By sorting jobs by profit and using a scheduling array, we efficiently handle job assignments within given time constraints. This method prioritizes the most profitable jobs, guaranteeing the best possible outcome under the problem's constraints.

---

## Optimized Solution Approach DSU:

While the linear backtracking approach works fine for smaller constraints, that $O(n \times \text{max\_deadline})$ worst-case time complexity hurts when both $n$ and the deadlines get large.

If a lot of jobs have deadlines far in the future and the slots are crowded, we waste too much time linearly scanning backward.

We can optimize this significantly using a Disjoint Set Union (DSU) data structure (also known as Union-Find).

- The DSU Optimization IntuitionInstead of scanning backward slot-by-slot to find an empty space, we can make each slot "point" to the next available free slot to its left.
- Initially, every time slot $t$ points to itself (meaning it is free).
- When a job occupies slot $t$, we union it with slot $t-1$.
- The next time a job demands slot $t$, finding its root representative will instantly point us to the actual next available free slot before $t$ in $O(1)$ amortized time.
- If the representative root of a deadline points to 0, it means no free slots are available for that job.

```
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Job {
    int deadline;
    int profit;
};

// Disjoint Set Union (DSU) Structure
struct DSU {
    vector<int> parent;

    DSU(int n) {
        parent.resize(n + 1);
        // Initially, each slot is its own parent (points to itself)
        iota(parent.begin(), parent.end(), 0);
    }

    // Find the next available free slot (with path compression)
    int find_slot(int val) {
        if (val == parent[val])
            return val;
        return parent[val] = find_slot(parent[val]); // Path compression
    }

    // Point an occupied slot to the available slot on its left
    void union_slots(int u, int v) {
        parent[u] = v;
    }
};

class Solution {
  public:
    static bool comparison(const Job& a, const Job& b) {
        return a.profit > b.profit;
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        int n = deadline.size();
        vector<Job> jobs(n);

        int maxDeadline = 0;
        for (int i = 0; i < n; i++) {
            jobs[i] = {deadline[i], profit[i]};
            maxDeadline = max(maxDeadline, deadline[i]);
        }

        // Step 1: Sort jobs by profit in descending order
        sort(jobs.begin(), jobs.end(), comparison);

        // Step 2: Initialize DSU with maxDeadline slots
        DSU dsu(maxDeadline);

        int countJobs = 0;
        int maxProfit = 0;

        // Step 3: Process jobs greedily
        for (int i = 0; i < n; i++) {
            // Find the highest available time slot <= jobs[i].deadline
            int availableSlot = dsu.find_slot(jobs[i].deadline);

            // If availableSlot is greater than 0, a free slot exists
            if (availableSlot > 0) {
                // Book this slot by pointing it to the next available slot on its left (availableSlot - 1)
                dsu.union_slots(availableSlot, availableSlot - 1);

                countJobs++;
                maxProfit += jobs[i].profit;
            }

            // Early break: Stop if we've filled all possible slots up to maxDeadline
            if (countJobs == maxDeadline) {
                break;
            }
        }

        return {countJobs, maxProfit};
    }
};
```

#### Time Complexity

Time (Sorting): $O(n \log n)$

Time (Scheduling): $O(n \times \alpha(\text{max\_deadline}))$

Overall Time Complexity: $O(n \log n)$

#### Space Complexity

$O(\text{max\_deadline})$

---

<br/>
not similar but related to Problem statement that you must try to solve:

[L1235. Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/)
