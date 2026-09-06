class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }

        int ans = INT_MAX;

        for (auto &p : mp) {
            vector<int> v = p.second;

            for (int i = 0; i + 2 < v.size(); i++) {
                int distance = 2 * (v[i + 2] - v[i]);
                ans = min(ans, distance);
            }
        }

        if (ans == INT_MAX)
            return -1;

        return ans;
    }
};