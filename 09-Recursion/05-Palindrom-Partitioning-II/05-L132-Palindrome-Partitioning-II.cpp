class Solution
{
public:
    int minCut(string s)
    {
        int n = s.size();

        // 1. Precompute palindromes to drop time complexity from O(N³) to O(N²)
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j < n; j++)
            {
                // It is a palindrome if the ends match AND the inside is a palindrome
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1]))
                {
                    isPal[i][j] = true;
                }
            }
        }

        // 2. Your exact DP logic, but insanely faster
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--)
        {
            int minCuts = INT_MAX;

            for (int j = i; j < n; j++)
            {
                // Instant O(1) lookup instead of a while loop!
                if (isPal[i][j])
                {
                    int cuts = 1 + dp[j + 1];
                    minCuts = min(minCuts, cuts);
                }
            }
            dp[i] = minCuts;
        }

        return dp[0] - 1;
    }
};