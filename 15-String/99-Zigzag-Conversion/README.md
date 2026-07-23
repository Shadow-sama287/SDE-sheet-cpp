# [Zigzag Conversion](PLATFORM_URL_HERE)

## Resources

- [Striver's SDE Sheet](STRIVERS_SDE_SHEET_URL_HERE)

## Problem Description

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:

```
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
```

Example 2:

```
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
```

Example 3:

```
Input: s = "A", numRows = 1
Output: "A"
```

Constraints:

```
1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
```

---

## My thought process

```cp
class Solution {
public:
    string convert(string s, int numRows) {
        int len = s.length();
        vector<vector<char>> pattern(numRows, vector<char>);

        int remainLength = len;
        while(remainLength) {
            //   *        *        *
            //   *     *  *     *  *
            //   *  *     *  *     *
            //   *        *
            // How tf do i do this now...
            // i have to push the s[i] char at perfect place for that, and for `i` I can
            // calculate it as `len - remainLength`
            // for example : len = 14 for s = "PAYPALISHIRING"
            //
            // pattern:
            //   P        I        N
            //   A     L  S     I  G     -
            //   Y  A     H  R     -  -
            //   P        I        -
            //
            // for 14: s[i] => `i` is `14-14 = 0` => "P"
            //
            // Now main problem is positions...
            // for(i = 0;      i < numRows `[ 4 ]`     ; i++) {
            //
            //      pattern[i]
            //      I asked gpt ahead... it showed me the bucket solution
            //
            // }
            //
            //
        }
    }
};
```
