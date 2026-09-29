class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Path length must be even
        if ((m + n - 1) % 2 != 0)
            return false;

        // Must start with '(' and end with ')'
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(m + n + 1, -1))
        );

        return solve(0, 0, 0, grid, dp);
    }

    bool solve(int i, int j, int balance,
               vector<vector<char>>& grid,
               vector<vector<vector<int>>>& dp) {

        int m = grid.size();
        int n = grid[0].size();

        if (i >= m || j >= n)
            return false;

        if (grid[i][j] == '(')
            balance++;
        else
            balance--;

        // More ')' than '('
        if (balance < 0)
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool down = solve(i + 1, j, balance, grid, dp);
        bool right = solve(i, j + 1, balance, grid, dp);

        return dp[i][j][balance] = down || right;
    }
};