class myQueue
{
private:
    int front;
    int back;
    int size;
    int *que;

public:
    myQueue(int n)
    {
        // Define Data Structures
        size = n;
        front = -1;
        back = -1;
        que = new int[size];
    }

    // Best Practice: Prevent memory leaks
    ~myQueue()
    {
        delete[] que;
    }

    bool isEmpty()
    {
        // check if the queue is empty
        return front == -1;
    }

    bool isFull()
    {
        // check if the queue is full
        return front == 0 && back == size - 1;
    }

    void enqueue(int x)
    {
        if (isFull())
            return;

        if (isEmpty())
        {
            front = 0; // Initialize front on first insert
        }
        // SHIFT LOGIC: If back hit the wall, but there's space at the front
        else if (back == size - 1 && front > 0)
        {
            int currentElementCount = back - front + 1;

            // Shift all active elements left to start at index 0
            for (int i = 0; i < currentElementCount; i++)
            {
                que[i] = que[front + i];
            }

            // Reset pointers after shifting
            front = 0;
            back = currentElementCount - 1;
        }

        // Now safely add the new element
        back++;
        que[back] = x;
    }

    void dequeue()
    {
        // Removes the front element of the queue.
        if (isEmpty())
            return;

        front++;

        // If front passes back, the queue is completely empty. Reset to initial state.
        if (front > back)
        {
            front = -1;
            back = -1;
        }
    }

    int getFront()
    {
        // Returns the front element of the queue.
        if (isEmpty())
            return -1;
        return que[front];
    }

    int getRear()
    {
        // Return the last element of queue
        if (isEmpty())
            return -1;
        return que[back];
    }
};