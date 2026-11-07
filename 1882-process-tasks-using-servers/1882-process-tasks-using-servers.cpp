class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        using P = pair<int, int>;
        using T = tuple<long long, int, int>;

        priority_queue<P, vector<P>, greater<P>> available;
        priority_queue<T, vector<T>, greater<T>> busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);
        long long time = 0;

        for (int i = 0; i < m; i++) {
            time = max(time, (long long)i);

            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [finish, weight, index] = busy.top();
                busy.pop();
                available.push({weight, index});
            }

            if (available.empty()) {
                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [finish, weight, index] = busy.top();
                    busy.pop();
                    available.push({weight, index});
                }
            }

            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            busy.push({time + tasks[i], weight, index});
        }

        return ans;
    }
};