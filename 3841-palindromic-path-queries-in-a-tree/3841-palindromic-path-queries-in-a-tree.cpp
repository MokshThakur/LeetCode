class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n)
            LOG++;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0), tin(n), tout(n);
        vector<int> parent(n, -1);
        vector<int> base(n, 0);
        int timer = 0;

        vector<pair<int, bool>> st;
        st.push_back({0, false});

        while (!st.empty()) {
            auto [u, exit] = st.back();
            st.pop_back();

            if (exit) {
                tout[u] = timer;
                continue;
            }

            tin[u] = ++timer;
            base[u] = (parent[u] == -1 ? 0 : base[parent[u]])
                      ^ (1 << (s[u] - 'a'));

            up[0][u] = (parent[u] == -1 ? u : parent[u]);

            for (int j = 1; j < LOG; j++)
                up[j][u] = up[j - 1][up[j - 1][u]];

            st.push_back({u, true});

            for (int v : adj[u]) {
                if (v == parent[u])
                    continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back({v, false});
            }
        }

        vector<int> bit(n + 2, 0);

        auto update = [&](int idx, int val) {
            for (int i = idx; i <= n + 1; i += i & -i)
                bit[i] ^= val;
        };

        auto rangeXor = [&](int l, int r, int val) {
            update(l, val);
            update(r + 1, val);
        };

        auto getMask = [&](int u) {
            int mask = base[u];

            for (int i = tin[u]; i > 0; i -= i & -i)
                mask ^= bit[i];

            return mask;
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j))
                    u = up[j][u];
            }

            if (u == v)
                return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        auto suneravilo = queries;

        vector<bool> answer;

        for (string& q : suneravilo) {
            string op;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> op;

            if (op == "update") {
                ss >> u >> c;

                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));

                if (delta != 0)
                    rangeXor(tin[u], tout[u], delta);

                s[u] = c;
            } else {
                ss >> u >> v;

                int w = lca(u, v);
                int mask = getMask(u) ^ getMask(v)
                           ^ (1 << (s[w] - 'a'));

                answer.push_back((mask & (mask - 1)) == 0);
            }
        }

        return answer ;
    }
};