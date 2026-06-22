class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        ;
        vector<int> prev(amount + 1, 0);
        vector<int> curr(amount + 1, 0);
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        for (int T = 0; T <= amount; T++)
        { // calculating for fist row
            if (T % coins[0] == 0)
                prev[T] = T / coins[0];
            else
                prev[T] = 1e9;
        }

        for (int idx = 1; idx < n; idx++)
        { // calculating for remaining rows
            for (int T = 0; T <= amount; T++)
            {
                int notTake = 0 + prev[T];
                int take = INT_MAX;
                if (coins[idx] <= T)
                {
                    take = 1 + curr[T - coins[idx]];
                }
                curr[T] = min(take, notTake);
            }

            prev = curr;
        }

        int ans = prev[amount];
        if (ans >= 1e9)
            return -1;
        return ans;
    }
};