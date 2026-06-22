## [Coin Change](https://leetcode.com/problems/coin-change/)

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

Example 1:

```
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:
```

```
Input: coins = [2], amount = 3
Output: -1
Example 3:
```

```
Input: coins = [1], amount = 0
Output: 0
```

Constraints:

```
1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
```

### Solutions:

#### Intuition

Imagine you're a cashier and need to give someone 11 cents in change, and you only have 1, 2, and 5 cent coins. How would you do it using the fewest coins?

Your first thought might be to use the biggest coin possible. You'd grab a 5, leaving you with 6 cents. Then you'd grab another 5, leaving 1 cent. Finally, you'd grab a 1. That's 5+5+1, a total of 3 coins. This is a greedy approach, and it works for this example.

But what if the coins were [1, 3, 4] and the amount was 6? A greedy approach would pick 4, leaving 2. Now you're stuck! You can't make 2 with 3s so you have to choose two 1s and hence getting a total 3 coins. But the optimal solution is 3+3, which is only 2 coins.

This tells us we need to explore all possibilities. For a given amount, we could try using one of our coins (say, a 1-cent coin), and then the problem becomes "what's the minimum number of coins for amount - 1?". We could do this for every coin we have and then take the best result.

This idea of breaking the main problem down into smaller, identical subproblems is a perfect signal for using recursion or dynamic programming.

#### Approach

We will explore three ways to solve this problem, starting with a simple but slow method and gradually improving it to the best solution.

### Approach 1: Brute-Force Recursion (Top-Down)

The most direct way to translate our intuition is to use recursion. We define a function, let's call it solve(amount), that returns the minimum coins for that amount.

Inside this function, we do the following:

- Base Cases:
  If amount is 0, we need 0 coins. Return 0.

- If amount is less than 0, it's an impossible situation (we overshot). Return -1 (or some other indicator of failure).

- Recursive Step:
  Initialize a variable min_coins to infinity.

- For each coin in our coins list:

- Recursively call solve(amount - coin).

- If the result of this call is not a failure, it means we found a valid combination. The total coins for this path would be 1 (for the current coin) plus the result.

- Update min_coins = min(min_coins, 1 + result).

- After checking all coins, if min_coins is still infinity, it means no solution was found. Otherwise, it holds our answer.

This approach is correct, but it's very slow because it recalculates the solution for the same amount over and over again. For example, to get to amount = 11, both 11 -> 10 -> 5 and 11 -> 6 -> 5 will try to solve for amount = 5 independently.

Code (This can give error on leetcode for large n)

```
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 0) return -1;
        if (amount == 0) return 0;

        int min_count = INT_MAX;

        for (int coin : coins) {
            int res = coinChange(coins, amount - coin);
            // If a solution exists for the subproblem
            if (res >= 0 && res < min_count) {
                min_count = 1 + res;
            }
        }

        return (min_count == INT_MAX) ? -1 : min_count;
    }
};
```

This solution will likely Time Limit Exceed on LeetCode, but it's a great starting point.

### Approach 2: Top-Down Dynamic Programming with Memoization

To fix the repeated calculations from Approach 1, we can use a technique called memoization. It's just a fancy word for remembering the results of subproblems we've already solved.

We'll use an array (or a map), let's call it memo, to store the answers. memo[i] will store the minimum coins needed for amount i.

The logic is almost the same as before, with one crucial addition:

- Before calculating solve(amount), we first check if memo[amount] already has an answer.

- If it does, we just return that stored answer immediately without any further calculation.

- If it doesn't, we perform the calculation just like in Approach 1.

- Crucially, before returning the result, we store it in memo[amount] so we don't have to calculate it again later.

This simple optimization dramatically improves the speed, as each subproblem is now solved only once.

```
Code
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // memo[i] will store the min coins for amount i.
        // Initialize with -2 to indicate "not computed yet".
        vector<int> memo(amount + 1, -2);
        return solve(coins, amount, memo);
    }
private:
    int solve(vector<int>& coins, int rem, vector<int>& memo) {
        if (rem < 0) return -1; // Invalid state
        if (rem == 0) return 0;  // Base case: amount is 0
        if (memo[rem] != -2) return memo[rem]; // Return cached result

        int min_count = INT_MAX;

        for (int coin : coins) {
            int res = solve(coins, rem - coin, memo);
            if (res >= 0 && res < min_count) {
                min_count = 1 + res;
            }
        }

        // Cache the result before returning
        memo[rem] = (min_count == INT_MAX) ? -1 : min_count;
        return memo[rem];
    }
};
```

### Approach 3: Bottom-Up Dynamic Programming (Tabulation)

This is the most common and often slightly more efficient way to solve this problem. Instead of starting from the top (amount) and using recursion, we build the solution from the bottom up.

We create an array dp of size amount + 1. The goal is to fill this array, where dp[i] will represent the minimum number of coins to make change for amount i.

- Initialization:
  dp[0] = 0 because it takes 0 coins to make an amount of 0.

- Fill the rest of the dp array with a placeholder value representing infinity. A good choice is amount + 1, because you can never need more than amount coins (if you used all 1-cent coins).

Iteration:

- We loop through all amounts from i = 1 up to amount.

- For each amount i, we loop through each coin.

- If a coin is less than or equal to i, it's possible to use this coin. We can then form amount i by taking this coin and adding it to the optimal solution for the remaining amount, which is i - coin.

- The number of coins for this combination would be 1 + dp[i - coin].

- We want the best (minimum) solution, so we update dp[i] with the formula: dp[i] = min(dp[i], 1 + dp[i - coin]).

- Result:
  After the loops complete, dp[amount] will hold the answer for our target amount.

- If dp[amount] is still the "infinity" value (amount + 1), it means we were never able to find a combination of coins to make that amount. In this case, we return -1.

```
Let's trace coins = [1, 2, 5], amount = 5:

dp array of size 6, initialized to [0, 6, 6, 6, 6, 6]

i = 1: Use coin 1. dp[1] = min(6, 1 + dp[0]) = 1. dp is [0, 1, 6, 6, 6, 6]

i = 2: Use coin 1. dp[2] = min(6, 1 + dp[1]) = 2. Use coin 2. dp[2] = min(2, 1 + dp[0]) = 1. dp is [0, 1, 1, 6, 6, 6]

i = 3: Use coin 1. dp[3] = min(6, 1 + dp[2]) = 2. Use coin 2. dp[3] = min(2, 1 + dp[1]) = 2. dp is [0, 1, 1, 2, 6, 6]

i = 4: Use coin 1. dp[4] = min(6, 1 + dp[3]) = 3. Use coin 2. dp[4] = min(3, 1 + dp[2]) = 2. dp is [0, 1, 1, 2, 2, 6]

i = 5: Use coin 1. dp[5] = min(6, 1 + dp[4]) = 3. Use coin 2. dp[5] = min(3, 1 + dp[3]) = 3. Use coin 5. dp[5] = min(3, 1 + dp[0]) = 1. dp is [0, 1, 1, 2, 2, 1]

Final answer is dp[5], which is 1.
```

```
Code
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] will be storing the minimum number of coins required for amount i.
        // We use amount + 1 as an "infinity" value.
        vector<int> dp(amount + 1, amount + 1);

        // Base case: 0 coins are needed for amount 0.
        dp[0] = 0;

        // Iterate through all amounts from 1 to the target amount.
        for (int i = 1; i <= amount; ++i) {
            // For each amount, check each coin.
            for (int coin : coins) {
                if (i - coin >= 0) {
                    // If we can use this coin, update the dp table for the current amount.
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        // If dp[amount] is still the "infinity" value, it means the amount cannot be formed.
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```

### Complexity

```
** Time complexity: O(S⋅n) **
Where S is the number of coins and n is the target amount. We have an outer loop that runs from 1 to amount (n times), and an inner loop that runs for each coin (S times). This gives us a total of S⋅n operations.

Space complexity: O(n)
We use an extra array dp of size amount + 1 to store the minimum coin counts for all amounts from 0 to amount.
```
