class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        const long long INF = LLONG_MAX / 4;

        multiset<int> left, right;
        long long sumLeft = 0, sumRight = 0;

        auto rebalance = [&]() {
            int target = (left.size() + right.size() + 1) / 2;

            while ((int)left.size() > target) {
                auto it = prev(left.end());
                int val = *it;
                left.erase(it);
                sumLeft -= val;
                right.insert(val);
                sumRight += val;
            }

            while ((int)left.size() < target && !right.empty()) {
                auto it = right.begin();
                int val = *it;
                right.erase(it);
                sumRight -= val;
                left.insert(val);
                sumLeft += val;
            }

            while (!left.empty() && !right.empty() &&
                   *left.rbegin() > *right.begin()) {
                int a = *left.rbegin();
                int b = *right.begin();

                left.erase(prev(left.end()));
                right.erase(right.begin());

                sumLeft += (long long)b - a;
                sumRight += (long long)a - b;

                left.insert(b);
                right.insert(a);
            }
        };

        auto add = [&](int val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sumLeft += val;
            } else {
                right.insert(val);
                sumRight += val;
            }
            rebalance();
        };

        auto remove = [&](int val) {
            auto it = left.find(val);
            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }
            rebalance();
        };

        auto cost = [&]() -> long long {
            long long median = *left.rbegin();
            return median * (long long)left.size() - sumLeft
                 + sumRight - median * (long long)right.size();
        };

        vector<long long> windowCost(n - x + 1);

        for (int i = 0; i < x; ++i)
            add(nums[i]);

        windowCost[0] = cost();

        for (int i = x; i < n; ++i) {
            remove(nums[i - x]);
            add(nums[i]);
            windowCost[i - x + 1] = cost();
        }

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                if (dp[j][i] == INF)
                    continue;

                dp[j][i + 1] = min(dp[j][i + 1], dp[j][i]);

                if (j < k && i + x <= n) {
                    dp[j + 1][i + x] = min(
                        dp[j + 1][i + x],
                        dp[j][i] + windowCost[i]
                    );
                }
            }
        }

        return dp[k][n];
    }
};