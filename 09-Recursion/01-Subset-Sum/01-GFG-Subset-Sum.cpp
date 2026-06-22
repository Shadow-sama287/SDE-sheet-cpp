class Solution
{
public:
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        int n = arr.size();

        // dp[j] will be true if there is a subset with sum j
        vector<bool> dp(sum + 1, false);

        // Base case: A sum of 0 is always possible (empty subset)
        dp[0] = true;

        // Iterate through all elements in the array
        for (int i = 0; i < n; i++)
        {
            // Iterate backwards to prevent using the same element multiple times
            for (int j = sum; j >= arr[i]; j--)
            {
                // If the sum j is possible without arr[i], or
                // if the sum (j - arr[i]) is possible, then sum j is possible.
                dp[j] = dp[j] || dp[j - arr[i]];
            }
        }

        // The answer will be whether the target 'sum' is possible
        return dp[sum];
    }
};