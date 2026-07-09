// Instead of using separate arrays, we use the first row and first column of the matrix itself to store whether a row or column needs to be zeroed. We also store two flags:
// -- firstRowZero:Was the first row supposed to be all zero?
// -- firstColZero:Was the first column supposed to be all zero?

// Then:
// -- First pass: Mark zeros in the first row and column for any zero found in the rest of the matrix.
// -- Second pass: Use those markers to set rows and columns to zero.
// -- Finally, handle the first row and column separately based on the flags. This is super space-efficient because we’re reusing the input matrix itself to store markers.

// -- Check if the first row has any zero and store in a boolean flag.
// -- Check if the first column has any zero and store in a boolean flag.
// -- Traverse the rest of the matrix:
// --- If a cell is zero, mark its row in the first column and its column in the first row as zero.
// -- Traverse again (excluding first row and column), setting cells to zero if their row marker or column marker is zero.
// -- Finally, update the first row and first column based on the stored flags.

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        // vector<int> col(n, 0); ===> matrix[0][..]
        // vector<int> row(m, 0); ===> matrix[..][0]

        // Flag to track if first row should be zeroed
        bool firstRowZero = false;
        // Flag to track if first column should be zeroed
        bool firstColZero = false;

        // Check if first row has any zero
        for (int j = 0; j < n; j++)
        {
            if (matrix[0][j] == 0)
            {
                firstRowZero = true;
                break;
            }
        }

        // Check if first column has any zero
        for (int i = 0; i < m; i++)
        {
            if (matrix[i][0] == 0)
            {
                firstColZero = true;
                break;
            }
        }

        // Mark rows and columns in first row/column
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Set matrix cells to zero based on markers
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // Handle first row
        if (firstRowZero)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[0][j] = 0;
            }
        }

        // Handle first column
        if (firstColZero)
        {
            for (int i = 0; i < m; i++)
            {
                matrix[i][0] = 0;
            }
        }
    }
};