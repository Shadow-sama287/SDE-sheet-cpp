class Solution
{
public:
    // Define the struct locally inside the class
    struct Item
    {
        int value;
        int weight;
    };

    // Comparator function to sort items by value/weight ratio
    // Passed by const reference for better performance
    static bool comparative(const Item &a, const Item &b)
    {
        double r1 = (double)a.value / (double)a.weight;
        double r2 = (double)b.value / (double)b.weight;
        return r1 > r2;
    }

    double fractionalKnapsack(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();

        // Step 1: Pair the separated vectors into a single vector of Items
        vector<Item> items(n);
        for (int i = 0; i < n; i++)
        {
            items[i] = {val[i], wt[i]};
        }

        // Step 2: Sort items based on the value/weight ratio in descending order
        sort(items.begin(), items.end(), comparative);

        int curWeight = 0;       // Current weight of knapsack
        double finalValue = 0.0; // Maximum value we can achieve

        // Step 3: Iterate through the sorted items and fill the knapsack
        for (int i = 0; i < n; i++)
        {

            // If the current item can be fully added to the knapsack
            if (curWeight + items[i].weight <= capacity)
            {
                curWeight += items[i].weight;
                finalValue += items[i].value;
            }
            // If the current item can't be fully added, take the fractional part
            else
            {
                int remain = capacity - curWeight;
                finalValue += ((double)items[i].value / (double)items[i].weight) * (double)remain;
                break; // The knapsack is now completely full
            }
        }

        return finalValue;
    }
};