class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        int minPrice = INT_MAX;

        for (auto& item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, item[1]);
        }

        // Count items whose factors are multiples of each factor.
        vector<long long> multiples(n + 1, 0);

        for (int f = 1; f <= n; f++) {
            for (int x = f; x <= n; x += f) {
                multiples[f] += freq[x];
            }
        }

        // Each bonus purchase gives 2 items:
        // 1 purchased + 1 free.
        vector<pair<int, long long>> candidates;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            long long gain = multiples[factor] - 1;

            // Ignore bonus purchases costing >= 2 cheapest items.
            if (gain > 0 && 2LL * minPrice > price) {
                candidates.push_back({price, gain});
            }
        }

        sort(candidates.begin(), candidates.end());

        long long remaining = budget;
        long long bonusCount = 0;

        long long ans = budget / minPrice;

        int i = 0;

        while (i < candidates.size()) {
            int price = candidates[i].first;
            long long totalGain = 0;

            // Combine all bonus copies having the same price.
            while (i < candidates.size() &&
                   candidates[i].first == price) {
                totalGain += candidates[i].second;
                i++;
            }

            long long take = min(totalGain, remaining / price);

            bonusCount += take;
            remaining -= take * price;

            long long current =
                2LL * bonusCount + remaining / minPrice;

            ans = max(ans, current);
        }

        return (int)ans;
    }
};