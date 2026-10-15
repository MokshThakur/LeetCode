class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num)
            return "";

        string ans;
        int remaining = sum;

        for (int i = 0; i < num; i++) {
            int digit = min(9, remaining);
            ans += char('0' + digit);
            remaining -= digit;
        }

        return remaining == 0 ? ans : "";
    }
};