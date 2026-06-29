class LFUCache
{
public:
    class Node
    {
    public:
        int key, value, count;
        Node *next;
        Node *prev;

        Node(int k, int v)
        {
            key = k;
            value = v;
            count = 1; // All new nodes start at frequency 1
            prev = next = nullptr;
        }
    };

    struct List
    {
        int size;
        Node *head;
        Node *tail;

        List()
        {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
            size = 0;
        }

        void addNode(Node *newNode)
        {
            Node *oldNext = head->next;
            head->next = newNode;
            oldNext->prev = newNode;
            newNode->next = oldNext;
            newNode->prev = head;
            size++;
        }

        void delNode(Node *oldNode)
        {
            Node *oldPrev = oldNode->prev;
            Node *oldNext = oldNode->next;
            oldPrev->next = oldNext;
            oldNext->prev = oldPrev;
            size--;
        }
    };

    unordered_map<int, Node *> keyNode;
    unordered_map<int, List *> freqMap;

    int limit;
    int minFreq;
    int curSize;

    LFUCache(int capacity)
    {
        limit = capacity;
        minFreq = 0;
        curSize = 0;
    }

    int get(int key)
    {
        if (keyNode.find(key) == keyNode.end())
            return -1;

        Node *ansNode = keyNode[key];
        int ans = ansNode->value;

        updateFreq(ansNode);

        return ans;
    }

    void put(int key, int value)
    {
        if (limit == 0)
            return;

        // If key exists, update value and frequency
        if (keyNode.find(key) != keyNode.end())
        {
            Node *existingNode = keyNode[key];
            existingNode->value = value;
            updateFreq(existingNode);
            return;
        }

        // LFU LOGIC
        if (curSize == limit)
        {
            // The LRU node is right before the tail of the minFreq list
            List *minList = freqMap[minFreq];
            Node *lruNode = minList->tail->prev;

            keyNode.erase(lruNode->key);
            minList->delNode(lruNode);
            curSize--;
        }

        // Add the brand new node
        curSize++;
        minFreq = 1;

        if (freqMap.find(1) == freqMap.end())
        {
            freqMap[1] = new List();
        }

        Node *newNode = new Node(key, value);
        freqMap[1]->addNode(newNode);
        keyNode[key] = newNode;
    }

    void updateFreq(Node *node)
    {
        keyNode.erase(node->key);
        freqMap[node->count]->delNode(node);

        // If this was the last node in the minFreq list, minFreq goes up
        if (node->count == minFreq && freqMap[node->count]->size == 0)
        {
            minFreq++;
        }

        node->count++;

        // If the list for the new frequency doesn't exist, create it
        if (freqMap.find(node->count) == freqMap.end())
        {
            freqMap[node->count] = new List();
        }

        // Add the node to the new frequency list and update our map
        freqMap[node->count]->addNode(node);
        keyNode[node->key] = node;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */