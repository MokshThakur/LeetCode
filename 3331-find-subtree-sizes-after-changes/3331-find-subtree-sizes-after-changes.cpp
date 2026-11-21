class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last(26, -1);
        vector<int> newParent = parent;

        function<void(int)> dfs = [&](int node) {
            int c = s[node] - 'a';
            int old = last[c];

            if (old != -1) {
                newParent[node] = old;
            }

            last[c] = node;

            for (int child : adj[node]) {
                dfs(child);
            }

            last[c] = old;
        };

        dfs(0);

        vector<vector<int>> newTree(n);

        for (int i = 1; i < n; i++) {
            newTree[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        function<int(int)> calculate = [&](int node) {
            for (int child : newTree[node]) {
                ans[node] += calculate(child);
            }

            return ans[node];
        };

        calculate(0);

        return ans;
    }
};