class Solution
{
public:
    struct Job
    {
        int deadline;
        int profit;
    };
    // Comparator function to sort jobs in descending order of profit
    static bool comparison(const Job &a, const Job &b)
    {
        return a.profit > b.profit;
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit)
    {
        int n = deadline.size();
        vector<Job> jobs(n);

        int maxDeadline = 0;
        // Combine deadline and profit into a structure and find max deadline
        for (int i = 0; i < n; i++)
        {
            jobs[i] = {deadline[i], profit[i]};
            maxDeadline = max(maxDeadline, deadline[i]);
        }

        // Step 1: Sort all jobs according to decreasing order of profit
        sort(jobs.begin(), jobs.end(), comparison);

        // Step 3: Create a scheduling array initialized to -1 (indicating free slots)
        // Size is maxDeadline + 1 to comfortably map 1-based deadlines
        vector<int> slot(maxDeadline + 1, -1);

        int countJobs = 0;
        int maxProfit = 0;

        // Step 4: Iterate through all given jobs
        for (int i = 0; i < n; i++)
        {
            // Find a free slot for this job, starting from its last possible slot
            for (int j = jobs[i].deadline; j > 0; j--)
            {
                // Free slot found
                if (slot[j] == -1)
                {
                    slot[j] = i; // Assign job to this slot
                    countJobs++;
                    maxProfit += jobs[i].profit;
                    break; // Move to the next job
                }
            }

            // Early break optimization: if all available slots are filled, stop
            if (countJobs == maxDeadline)
            {
                break;
            }
        }

        // Return the total number of jobs scheduled and the maximum profit
        return {countJobs, maxProfit};
    }
};
