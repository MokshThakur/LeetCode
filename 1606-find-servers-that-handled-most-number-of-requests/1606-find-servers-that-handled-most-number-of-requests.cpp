class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        using P = pair<long long, int>;
        priority_queue<P, vector<P>, greater<P>> busy;

        vector<int> count(k, 0);
        int maxCount = 0;

        for (int i = 0; i < arrival.size(); i++) {
            long long time = arrival[i];

            while (!busy.empty() && busy.top().first <= time) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            auto it = available.lower_bound(i % k);

            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;
            available.erase(it);

            count[server]++;
            maxCount = max(maxCount, count[server]);

            busy.push({time + load[i], server});
        }

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxCount) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};