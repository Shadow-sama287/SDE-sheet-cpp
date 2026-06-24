class Solution
{
public:
    string getPermutation(int n, int k)
    {
        int fact = 1;
        vector<int> numbers;
        for (int i = 1; i < n; i++)
        {
            fact = fact * i; // Calculate factorial of n-1
            numbers.push_back(i);
        }
        numbers.push_back(n); // Add last element (n)
        string ans = "";
        k = k - 1; // Convert k to 0-based index
        while (true)
        {
            ans = ans +
                  to_string(numbers[k / fact]); // Add the digit at the position
            numbers.erase(numbers.begin() +
                          k / fact); // Remove that number from the list

            if (numbers.size() == 0)
            {
                break; // Exit when all numbers are used
            }

            k = k %
                fact; // Reduce k to fit within the remaining sub-permutation
            fact = fact /
                   numbers.size(); // Update factorial for the remaining numbers
        }
        return ans; // Return the Kth permutation sequence
    }
};