class Solution
{
public:
    vector<int> nextSmallerEle(vector<int> &arr)
    {
        //  code here
        int n = arr.size();
        stack<int> s;
        vector<int> ans(n, -1);

        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && s.top() >= arr[i])
            {
                s.pop();
            }

            int nextSmall = s.empty() ? -1 : s.top();
            ans[i] = nextSmall;
            s.push(arr[i]);
        }

        return ans;
    }
};