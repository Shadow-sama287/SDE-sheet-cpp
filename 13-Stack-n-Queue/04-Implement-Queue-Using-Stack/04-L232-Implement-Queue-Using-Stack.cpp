class MyQueue
{
public:
    stack<int> in;
    stack<int> out;

    MyQueue() {}

    void push(int x) { in.push(x); }

    int pop()
    {
        if (out.empty())
        {
            while (!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        // If queue is still empty, return -1 (or throw an error if
        // preferred)
        if (out.empty())
        {
            return -1;
        }

        int x = out.top();
        out.pop();
        return x;
    }

    int peek()
    {
        if (out.empty())
        {
            while (!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        // If queue is still empty, return -1 (or throw an error if
        // preferred)
        if (out.empty())
        {
            return -1;
        }

        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */