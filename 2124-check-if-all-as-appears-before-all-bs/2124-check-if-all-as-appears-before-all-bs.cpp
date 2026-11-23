class Solution {
public:
    bool checkString(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'b' && s.find('a', i) != string::npos) {
                return false;
            }
        }

        return true;
    }
};