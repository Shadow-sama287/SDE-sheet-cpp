class Solution
{
public:
    void sortStack(stack<int> &s)
    {
        // code here
        if (!s.empty())
        {
            int temp = s.top();
            s.pop();

            sortStack(s);

            insert(s, temp);
        }
    }

    void insert(stack<int> &s, int temp)
    {
        // Base case: if the stack is empty or temp is larger than the top element
        if (s.empty() || s.top() <= temp)
        {
            s.push(temp);
            return;
        }

        // Otherwise, pop the top element and recursively insert
        int val = s.top();
        s.pop();
        insert(s, temp);

        // Push the popped element back
        s.push(val);
    }
};
