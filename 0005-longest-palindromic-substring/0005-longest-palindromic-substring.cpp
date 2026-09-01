class Solution {
public:
    string expand(string s, int left, int right) {

        while (left >= 0 && right < s.length() &&
               s[left] == s[right]) {
            left--;
            right++;
        }

        return s.substr(left + 1, right - left - 1);
    }

    string longestPalindrome(string s) {

        string ans = "";

        for (int i = 0; i < s.length(); i++) {

            string a = expand(s, i, i);
            string b = expand(s, i, i + 1);

            if (a.length() > ans.length())
                ans = a;

         if (b.length() > ans.length())
                ans = b;
        }

        return ans;
    }
};