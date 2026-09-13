class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;

        for (int r = -(n - 1); r <= n - 1; r++) {
            for (int c = -(n - 1); c <= n - 1; c++) {

                int count = 0;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {

                        int x = i + r;
                        int y = j + c;

                        if (x >= 0 && x < n &&
                            y >= 0 && y < n &&
                            img1[i][j] == 1 &&
                            img2[x][y] == 1) {
                            count++;
                        }
                    }
                }

                ans = max(ans, count);
            }
        }

        return ans;
    }
};