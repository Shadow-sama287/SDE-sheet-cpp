## [Palindrom Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/description/)

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

Example 1:

```
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

Example 2:

```
Input: s = "a"
Output: 0
```

Example 3:

```
Input: s = "ab"
Output: 1
```

Constraints:

```
1 <= s.length <= 2000
s consists of lowercase English letters only.
```

### According to Striver's walkthrough with DP + Tabulation has TLE of approx **O(n^3)**:

```cpp
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n+1, -1);
        dp[n] = 0;

        for (int i = n - 1; n >= 0; i--) {
            int minCuts = INT_MAX;

            for (int j = i; j < n; j++) {
                if (isPalindrome(i, j, s)) {
                    int cuts = 1 + dp[j+1];
                    minCuts = min(minCuts, cuts);
                }
            }
            dp[i] = minCuts;
        }

        return dp[0] - 1;
    }

    bool isPalindrome(int i, int j, string& s) {
        while (i < j) {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }

    // int helper(int idx, int n, string& s, vector<int>& dp) {
    //     if (idx == n)
    //         return 0;
    //
    //     if (dp[idx] != -1)
    //         return dp[idx];
    //
    //     int minCuts = INT_MAX;
    //
    //     for (int j = idx; j < n; j++) {
    //         if (isPalindrome(idx, j, s)) {
    //             int cuts = 1 + helper(j + 1, n, s, dp);
    //             minCuts = min(minCuts, cuts);
    //         }
    //     }
    //     return dp[idx] = minCuts;
    // }
};
```
