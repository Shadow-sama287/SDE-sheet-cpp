class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int pivot = -1, n = nums.size();

        // traverse array till the current index number is smaller than the next one -- BREAKING POINT
        for (int i = n - 2; i >= 0; i--)
        {
            if (nums[i] < nums[i + 1])
            {
                pivot = i;
                break;
            }
        }

        // Edge case that given permutation is last one.
        if (pivot == -1)
        {
            reverse(nums.begin(), nums.end());
            return;
        }

        // if not the last permutation
        // traverse from the end again to find first number greater than the breaking point number and Swap them
        for (int i = n - 1; i > pivot; i--)
        {
            if (nums[i] > nums[pivot])
            {
                swap(nums[i], nums[pivot]); // we selected the next greater element
                break;
            }
        }

        // now reverse the remaing part at the end
        int i = pivot + 1, j = n - 1;
        while (i <= j)
        {
            swap(nums[i++], nums[j--]);
        }
    }
};