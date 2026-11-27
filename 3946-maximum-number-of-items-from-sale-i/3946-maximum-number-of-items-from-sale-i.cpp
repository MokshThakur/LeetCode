class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freeCnt(n, 0);
        int cheapest = INT_MAX;

        for (int i = 0; i < n; i++) {
            cheapest = min(cheapest, items[i][1]);

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    freeCnt[i]++;
                }
            }
        }

        const int NEG = -1000000000;
        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int gain = freeCnt[i] + 1;

            for (int b = budget; b >= price; b--) {
                if (dp[b - price] != NEG) {
                    dp[b] = max(dp[b], dp[b - price] + gain);
                }
            }
        }

        int ans = 0;

        for (int spent = 0; spent <= budget; spent++) {
            if (dp[spent] != NEG) {
                int extra = (budget - spent) / cheapest;
                ans = max(ans, dp[spent] + extra);
            }
        }

        return ans;
    }
};