class myStack
{
private:
    int top;
    int size;
    int *arr;

public:
    myStack(int n)
    {
        // Define Data Structures
        size = n;
        arr = new int[size];
        top = -1;
    }

    // Best Practice: Added Destructor to prevent memory leaks
    ~myStack()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        // check if the stack is empty
        return top == -1;
    }

    bool isFull()
    {
        // check if the stack is full
        return top == size - 1;
    }

    void push(int x)
    {
        // inserts x at the top of the stack
        if (isFull())
            return;
        top++;
        arr[top] = x;
    }

    void pop()
    {
        // removes an element from the top of the stack
        if (isEmpty())
            return;
        top--;
    }

    int peek()
    {
        // Returns the top element of the stack
        if (isEmpty())
            return -1;
        return arr[top];
    }
};
