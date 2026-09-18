/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode* dummy = new ListNode(0);
        ListNode* temp = dummy;

        while (a != NULL && b != NULL) {
            if (a->val <= b->val) {
                temp->next = a;
                a = a->next;
            } else {
                temp->next = b;
                b = b->next;
            }

            temp = temp->next;
        }

        if (a != NULL)
            temp->next = a;
        else
            temp->next = b;

        return dummy->next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return NULL;

        ListNode* ans = NULL;

        for (int i = 0; i < lists.size(); i++) {
            ans = mergeTwoLists(ans, lists[i]);
        }

        return ans;
    }
};