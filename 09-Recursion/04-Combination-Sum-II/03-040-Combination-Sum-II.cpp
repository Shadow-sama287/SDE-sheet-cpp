class Solution
{
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        // 1. Sort the array first to handle duplicates easily
        sort(candidates.begin(), candidates.end());
        for (int n : candidates)
        {
            cout << n << " ";
        }
        vector<vector<int>> ans;
        vector<int> combin;
        helper(candidates, 0, target, ans, combin);
        return ans;
    }

private:
    void helper(vector<int> &arr, int start, int target,
                vector<vector<int>> &ans, vector<int> &combin)
    {
        // Base case: We successfully hit the target
        if (target == 0)
        {
            ans.push_back(combin);
            return;
        }

        // Loop through the remaining choices starting from 'start'
        for (int i = start; i < arr.size(); i++)
        {

            // Skip duplicates at the same tree level
            if (i > start && arr[i] == arr[i - 1])
            {
                continue;
            }

            // Minor Optimization: If the current number is bigger than our
            // target, since the array is sorted, all subsequent numbers will
            // also be too big.
            if (arr[i] > target)
            {
                break;
            }

            // Include the current element
            combin.push_back(arr[i]);

            // Recurse. Note that we pass 'i + 1' to avoid reusing the same
            // element
            helper(arr, i + 1, target - arr[i], ans, combin);

            // Backtrack: Remove the element to try the next one in the loop
            combin.pop_back();
        }
    }
};