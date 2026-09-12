class Solution {
public:
    struct State {
        long long weight;
        vector<int> indices;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({intervals[i][0], intervals[i][1],
                         intervals[i][2], i});
        }

        sort(a.begin(), a.end());

        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                State skip = dp[i + 1][k];

                int lo = i + 1;
                int hi = n;

                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;

                    if (a[mid][0] > a[i][1])
                        hi = mid;
                    else
                        lo = mid + 1;
                }

                State take = dp[lo][k - 1];

                take.weight += a[i][2];
                take.indices.push_back((int)a[i][3]);

                sort(take.indices.begin(), take.indices.end());

                if (take.weight > skip.weight ||
                    (take.weight == skip.weight &&
                     take.indices < skip.indices)) {
                    dp[i][k] = take;
                } else {
                    dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].indices;
    }
};