class Solution {
public:
    struct State {
        int len = 0;
        int link = -1;
        int cnt = 0;
        unordered_map<int, int> next;
    };

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<State> st(2 * n);
        int sz = 1;
        int last = 0;

        for (int x : nums) {
            int cur = sz++;
            st[cur].len = st[last].len + 1;
            st[cur].cnt = 1;

            int p = last;

            while (p != -1 && !st[p].next.count(x)) {
                st[p].next[x] = cur;
                p = st[p].link;
            }

            if (p == -1) {
                st[cur].link = 0;
            } else {
                int q = st[p].next[x];

                if (st[p].len + 1 == st[q].len) {
                    st[cur].link = q;
                } else {
                    int clone = sz++;
                    st[clone] = st[q];
                    st[clone].len = st[p].len + 1;
                    st[clone].cnt = 0;

                    while (p != -1 && st[p].next[x] == q) {
                        st[p].next[x] = clone;
                        p = st[p].link;
                    }

                    st[q].link = clone;
                    st[cur].link = clone;
                }
            }

            last = cur;
        }

        vector<int> order(sz);
        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });

        for (int v : order) {
            if (st[v].link != -1) {
                st[st[v].link].cnt += st[v].cnt;
            }
        }

        int ans = n;

        for (int i = 1; i < sz; i++) {
            if (st[i].cnt == 1) {
                ans = min(ans, st[st[i].link].len + 1);
            }
        }

        return ans;
    }
};