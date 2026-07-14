# [Pascals Triangle](https://leetcode.com/problems/pascals-triangle/description/)

## Resources

- [Striver's SDE Sheet](https://takeuforward.org/data-structure/program-to-generate-pascals-triangle)

## Problem Description

Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

Example 1:

```
Input: numRows = 5
Output: [[1]
        ,[1,1]
        ,[1,2,1]
        ,[1,3,3,1]
        ,[1,4,6,4,1]]
```

Example 2:

```
Input: numRows = 1
Output: [[1]]
```

Constraints:

```
1 <= numRows <= 30
```

---

## Solution Approach

To print the Nth row of the pascal triangle we can take advantage of the relationship between Nth element and binomial coefficients.

In a pascal's triangle, the Nth row contains the binomial coefficients C(N-1, 0), C(N-1, 1) and so on till C(N-1, N-1). Thus we can simply calculate all these values to return the Nth row of pascal triangle.

Instead of computing full factorials, we can start with the first value as 1, and use the relation C(n, k) = C(n, k−1) × (n−k+1) / k to compute the next value from the previous one in constant time.
