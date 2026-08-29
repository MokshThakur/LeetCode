/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* makeTree(vector<int>& nums, int left, int right) {
        if (left > right)
            return NULL;

        int mid = left + (right - left) / 2;

        TreeNode* root = new TreeNode(nums[mid]);

        root->left = makeTree(nums, left, mid - 1);
        root->right = makeTree(nums, mid + 1, right);

        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return makeTree(nums, 0, nums.size() - 1);
    }
};