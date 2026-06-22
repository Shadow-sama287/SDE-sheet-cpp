class Solution
{
public:
    int minPlatform(vector<int> &arr, vector<int> &dep)
    {
        int n = arr.size();

        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());

        int reqPlat = 1;
        int ans = 1;
        int i = 1, j = 0;

        while (i < n && j < n)
        {
            if (arr[i] <= dep[j])
            { // if another train arrives before the departure of previous one
                reqPlat++;
                i++;
            }
            else
            {
                reqPlat--;
                j++;
            }
            ans = max(ans, reqPlat);
        }

        return ans;
    }
};
