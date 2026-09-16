class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1000000007;

        long long ans = 1;

        for (int i = 1; i <= 2 * k; i++) {
            ans = ans * (n + k - i) % MOD;

            long long inv = 1;
            long long base = i;
            long long exp = MOD - 2;

            while (exp > 0) {
                if (exp & 1)
                    inv = inv * base % MOD;

                base = base * base % MOD;
                exp >>= 1;
            }

            ans = ans * inv % MOD;
        }

        return ans;
    }
};