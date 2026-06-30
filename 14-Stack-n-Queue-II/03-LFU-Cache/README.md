# [LFU Cache](https://leetcode.com/problems/lfu-cache/description/)

## Resources

- [Striver's SDE Sheet](https://takeuforward.org/data-structure/lfu-cache)

## Solution walkthrough

The Setup: What are we actually storing?

Before we trace the steps, let's visualize your two maps:

```
keyNode: This is just a directory. You give it a key (like 1), and it gives you a direct memory address to that exact Node.

freqMap: This is the heavy lifter. The map's key is the frequency (1, 2, 3, etc.). The map's value is an entire List object (which contains a head and a tail).
```

When you use addNode, it puts the new node right after the head. This means:

```
Next to head = Most Recently Used (MRU)

Next to tail = Least Recently Used (LRU)
```

Step-by-Step Execution Trace

```
Capacity = 2
```

1. put(1, 1)

```
   Action: Cache is empty. Create Node(1,1) with frequency = 1.

State:

minFreq = 1

keyNode: {1: Node(1)}

freqMap[1]: HEAD <-> [Node 1] <-> TAIL
```

2. put(2, 2)

```
   Action: Cache has space. Create Node(2,2) with frequency = 1. Add it to the front of freqMap[1].

State:

minFreq = 1

keyNode: {1: Node(1), 2: Node(2)}

freqMap[1]: HEAD <-> [Node 2] <-> [Node 1] <-> TAIL (Node 2 is MRU, Node 1 is LRU)
```

3. get(1) -> Returns 1

```
   Action: Look up key 1. It exists. Remove it from freqMap[1]. Increase its frequency to 2. Create freqMap[2] and put it there.

State:

minFreq = 1 (Because freqMap[1] still has Node 2 in it)

keyNode: {1: Node(1), 2: Node(2)}

freqMap[1]: HEAD <-> [Node 2] <-> TAIL

freqMap[2]: HEAD <-> [Node 1] <-> TAIL
```

4. put(3, 3) (⚠️ THE EVICTION)

```
   Action: Cache is full (size 2). We must evict.

Step A: Look at minFreq, which is 1.

Step B: Go to freqMap[1]. Find the LRU node right before the tail (tail->prev). That is Node(2).

Step C: Delete Node(2) from the list, and erase 2 from keyNode.

Step D: Add Node(3,3) with frequency 1. Reset minFreq to 1.
```

State:

```
minFreq = 1

keyNode: {1: Node(1), 3: Node(3)}

freqMap[1]: HEAD <-> [Node 3] <-> TAIL

freqMap[2]: HEAD <-> [Node 1] <-> TAIL
```

5. get(2) -> Returns -1

```
   Action: Look up key 2 in keyNode. It's not there (we just evicted it). Return -1.
```

6. get(3) -> Returns 3

```
   Action: Look up key 3. It exists. Remove it from freqMap[1]. Increase frequency to 2. Move it to freqMap[2].
```

State:

```
minFreq = 2 (CRITICAL: freqMap[1] is now empty, so minFreq goes up!)

keyNode: {1: Node(1), 3: Node(3)}

freqMap[1]: HEAD <-> TAIL (Empty)

freqMap[2]: HEAD <-> [Node 3] <-> [Node 1] <-> TAIL (Node 3 was just added, so it is MRU. Node 1 is LRU).
```

7. put(4, 4) (⚠️ ANOTHER EVICTION)

```
   Action: Cache is full.

Step A: Look at minFreq, which is 2.

Step B: Go to freqMap[2]. Look at tail->prev. That is Node(1).

Step C: Delete Node(1) from the list and from keyNode.

Step D: Add Node(4,4) with frequency 1. Reset minFreq to 1.
```

State:

```
minFreq = 1

keyNode: {3: Node(3), 4: Node(4)}

freqMap[1]: HEAD <-> [Node 4] <-> TAIL

freqMap[2]: HEAD <-> [Node 3] <-> TAIL
```

8. get(1) -> Returns -1

```
   Action: Look up key 1. Not in keyNode. Return -1.
```

9. get(3) -> Returns 3

```
   Action: Look up key 3. Remove from freqMap[2]. Increase frequency to 3. Create freqMap[3] and put it there.
```

State:

```
minFreq = 1 (Because freqMap[1] still has Node 4)

keyNode: {3: Node(3), 4: Node(4)}

freqMap[1]: HEAD <-> [Node 4] <-> TAIL

freqMap[2]: HEAD <-> TAIL (Empty)

freqMap[3]: HEAD <-> [Node 3] <-> TAIL
```

10. get(4) -> Returns 4

```
    Action: Look up key 4. Remove from freqMap[1]. Increase frequency to 2. Move to freqMap[2].
```

State:

```
minFreq = 2 (freqMap[1] is now empty)

keyNode: {3: Node(3), 4: Node(4)}

freqMap[1]: HEAD <-> TAIL (Empty)

freqMap[2]: HEAD <-> [Node 4] <-> TAIL

freqMap[3]: HEAD <-> [Node 3] <-> TAIL
```

---

## Problem Description

Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

- **LFUCache(int capacity)** Initializes the object with the capacity of the data structure.
- **int get(int key)** Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
- **void put(int key, int value)** Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
- To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

Example 1:

```
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]

Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3
```

Constraints:

```
1 <= capacity <= 104
0 <= key <= 105
0 <= value <= 109
At most 2 * 105 calls will be made to get and put.
```
