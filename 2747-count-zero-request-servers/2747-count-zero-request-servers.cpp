class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {
        vector<pair<int, int>> sortedQueries;

        for (int i = 0; i < queries.size(); i++) {
            sortedQueries.push_back({queries[i], i});
        }

        sort(sortedQueries.begin(), sortedQueries.end());
        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        vector<int> freq(n + 1, 0);
        vector<int> ans(queries.size());

        int left = 0, right = 0, active = 0;

        for (auto [q, index] : sortedQueries) {
            while (right < logs.size() && logs[right][1] <= q) {
                int server = logs[right][0];
                if (freq[server]++ == 0)
                    active++;
                right++;
            }

            while (left < right && logs[left][1] < q - x) {
                int server = logs[left][0];
                if (--freq[server] == 0)
                    active--;
                left++;
            }

            ans[index] = n - active;
        }

        return ans;
    }
};