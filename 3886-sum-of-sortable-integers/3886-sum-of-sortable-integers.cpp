class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> prefDrop(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
            prefDrop[i + 1] = prefDrop[i];

            if (i > 0 && nums[i - 1] > nums[i])
                prefDrop[i + 1]++;
        }

        for (int i = n - 1; i >= 0; i--)
            suffMin[i] = min(suffMin[i + 1], nums[i]);

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;

            for (int i = 0; i < n; i += k) {
                int end = i + k - 1;

                int drops = prefDrop[end + 1] - prefDrop[i];

                if (nums[end] > nums[i])
                    drops++;

                if (drops > 1 || prefMax[i] > suffMin[i]) {
                    valid = false;
                    break;
                }
            }

            if (valid)
                ans += k;
        }

        return ans;
    }
};