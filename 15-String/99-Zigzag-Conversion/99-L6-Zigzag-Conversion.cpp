class Solution
{
public:
    string convert(string s, int numRows)
    {
        // Edge case: if there's only 1 row, or the string is shorter than the rows,
        // it doesn't zigzag at all. Just return the string.
        if (numRows == 1 || numRows >= s.length())
        {
            return s;
        }

        // Create an array of strings for each row
        vector<string> rows(numRows);
        int currentRow = 0;
        bool goingDown = false;

        // Drop each character into the correct row's bucket
        for (char c : s)
        {
            rows[currentRow] += c;

            // If we are at the top or bottom row, flip the direction
            if (currentRow == 0 || currentRow == numRows - 1)
            {
                goingDown = !goingDown;
            }

            // Move up or down based on our current direction
            if (goingDown)
            {
                currentRow++;
            }
            else
            {
                currentRow--;
            }
        }

        // Stitch all the rows together to get the final result
        string result = "";
        for (string row : rows)
        {
            result += row;
        }

        return result;
    }
};