class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1'000'000'007;
        int m = grid.size(), n = grid[0].size();

        vector<vector<array<int, 2>>> dp(
            m + 1, vector<array<int, 2>>(n + 1, {0, 0})
        );

        dp[0][1] = {1, 1};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    int ways = (dp[i][j + 1][1] +
                                dp[i + 1][j][0]) % MOD;

                    dp[i + 1][j + 1][0] = ways;
                    dp[i + 1][j + 1][1] = ways;
                } else {
                    dp[i + 1][j + 1][0] = dp[i][j + 1][1];
                    dp[i + 1][j + 1][1] = dp[i + 1][j][0];
                }
            }
        }

        return dp[m][n][0];
    }
};