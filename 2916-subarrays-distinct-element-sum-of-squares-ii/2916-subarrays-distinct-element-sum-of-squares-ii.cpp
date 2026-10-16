class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> lazy(4 * n, 0);
        vector<long long> sum(4 * n, 0);
        vector<long long> sumSq(4 * n, 0);

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr, long long val) -> void {
            if (ql <= l && r <= qr) {
                sumSq[node] = (sumSq[node] + 2 * val * sum[node] % MOD
                               + val * val % MOD * (r - l + 1)) % MOD;
                sum[node] = (sum[node] + val * (r - l + 1)) % MOD;
                lazy[node] = (lazy[node] + val) % MOD;
                return;
            }

            int mid = (l + r) / 2;

            if (lazy[node] != 0) {
                long long v = lazy[node];

                for (int child : {node * 2, node * 2 + 1}) {
                    int len = child == node * 2 ? mid - l + 1 : r - mid;
                    sumSq[child] = (sumSq[child] + 2 * v * sum[child] % MOD
                                    + v * v % MOD * len) % MOD;
                    sum[child] = (sum[child] + v * len) % MOD;
                    lazy[child] = (lazy[child] + v) % MOD;
                }

                lazy[node] = 0;
            }

            if (ql <= mid)
                self(self, node * 2, l, mid, ql, qr, val);

            if (qr > mid)
                self(self, node * 2 + 1, mid + 1, r, ql, qr, val);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sumSq[node] = (sumSq[node * 2] + sumSq[node * 2 + 1]) % MOD;
        };

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last.count(nums[i]) ? last[nums[i]] + 1 : 0;

            update(update, 1, 0, n - 1, left, i, 1);

            ans = (ans + sumSq[1]) % MOD;
            last[nums[i]] = i;
        }

        return ans;
    }
};