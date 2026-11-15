class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1000000007;

        long long even = 1, odd = 0;
        long long ans = 0;
        int parity = 0;

        for (int num : arr) {
            parity ^= (num & 1);

            if (parity == 0) {
                even++;
                ans = (ans + odd) % MOD;
            } else {
                odd++;
                ans = (ans + even) % MOD;
            }
        }

        return ans;
    }
};