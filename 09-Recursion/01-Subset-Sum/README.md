## [Subset Sum : Sum of all Subsets](https://takeuforward.org/data-structure/subset-sum-sum-of-all-subsets)

Problem Statement: Given an array print all the sum of the subset generated from it, in the increasing order.

Examples

```
Input: N = 3, arr[] = {5,2,1}

Output: 0,1,2,3,5,6,7,8

Explanation: We have to find all the subset’s sum and print them.in this case the generated subsets are [ [], [1], [2], [2,1], [5], [5,1], [5,2]. [5,2,1] ], so the sums we get will be  0,1,2,3,5,6,7,8
```

```
Input: N=3,arr[]= {3,1,2}

Output: 0,1,2,3,3,4,5,6

Explanation: We have to find all the subset’s sum and print them.in this case the generated subsets are [ [], [1], [2], [2,1], [3], [3,1], [3,2]. [3,2,1] ], so the sums we get will be  0,1,2,3,3,4,5,6
```

### Solution:

```cpp
class Solution {
public:
    // Helper function to generate subset sums recursively
    void findSums(int index, int currentSum, vector<int>& arr, vector<int>& sums) {
        // Base case: if we have considered all elements
        if (index == arr.size()) {
            sums.push_back(currentSum);
            return;
        }

        // Include current element
        findSums(index + 1, currentSum + arr[index], arr, sums);

        // Exclude current element
        findSums(index + 1, currentSum, arr, sums);
    }

    // Main function
    vector<int> subsetSums(vector<int>& arr) {
        vector<int> sums;
        findSums(0, 0, arr, sums);
        sort(sums.begin(), sums.end()); // Sort in increasing order
        return sums;
    }
};
```

---

## [Subset Sum Problem](https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1)

Given an array of positive integers arr[] and a value sum, determine if there is a subset of arr[] with sum equal to given sum.

Examples:

```
Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
Output: true
Explanation: Here there exists a subset with target sum = 9, 4+3+2 = 9.
```

```
Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
Output: false
Explanation: There is no subset with target sum 30.
```

```
Input: arr[] = [1, 2, 3], sum = 6
Output: true
Explanation: The entire array can be taken as a subset, giving 1 + 2 + 3 = 6.
```

Constraints:

```
1 <= arr.size() <= 200
1<= arr[i] <= 200
1<= sum <= 104
```

### Solution:

```cpp
class Solution {
public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();

        // dp[j] will be true if there is a subset with sum j
        vector<bool> dp(sum + 1, false);

        // Base case: A sum of 0 is always possible (empty subset)
        dp[0] = true;

        // Iterate through all elements in the array
        for (int i = 0; i < n; i++) {
            // Iterate backwards to prevent using the same element multiple times
            for (int j = sum; j >= arr[i]; j--) {
                // If the sum j is possible without arr[i], or
                // if the sum (j - arr[i]) is possible, then sum j is possible.
                dp[j] = dp[j] || dp[j - arr[i]];
            }
        }

        // The answer will be whether the target 'sum' is possible
        return dp[sum];
    }
};
```
