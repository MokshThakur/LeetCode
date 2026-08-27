class Solution {
public:
    int romanToInt(string s) {

        int ans = 0;

        for (int i = 0; i < s.length(); i++) {

            int value;

            if (s[i] == 'I') value = 1;
            else if (s[i] == 'V') value = 5;
            else if (s[i] == 'X') value = 10;
            else if (s[i] == 'L') value = 50;
            else if (s[i] == 'C') value = 100;
            else if (s[i] == 'D') value = 500;
            else value = 1000;

            if (i + 1 < s.length()) {

                int next;

                if (s[i + 1] == 'I') next = 1;
                else if (s[i + 1] == 'V') next = 5;
                else if (s[i + 1] == 'X') next = 10;
                else if (s[i + 1] == 'L') next = 50;
                else if (s[i + 1] == 'C') next = 100;
                else if (s[i + 1] == 'D') next = 500;
                else next = 1000;

                if (value < next)
                    ans -= value;
                else
                    ans += value;
            }
            else {
                ans += value;
            }
        }

        return ans;
    }
}; 