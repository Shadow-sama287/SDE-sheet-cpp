# [Sort The Stack](https://www.geeksforgeeks.org/problems/sort-a-stack/1)

## Resources

- [Striver's SDE Sheet](https://takeuforward.org/data-structure/sort-a-stack)

## Approach:

- If the stack is empty, stop.
- Remove the top element of the stack.
- Sort the remaining stack recursively.
- Insert the removed element back into the stack while maintaining descending order.
- Use a helper function to place the element in its correct position.

## Problem Description

Given a stack of integers st[]. Sort the stack in ascending order (smallest element at the bottom and largest at the top).

Examples:

```
Input: st[] = [41, 3, 32, 2, 11]
Output: [41, 32, 11, 3, 2]
Explanation: After sorting, the smallest element (2) is at the bottom and the largest element (41) is at the top.
```

```
Input: st[] = [3, 2, 1]
Output: [3, 2, 1]
Explanation: The stack is already sorted in ascending order.
```

Constraints:

```
1 ≤ st.size() ≤ 103
0 ≤ stack element ≤ 103
```
