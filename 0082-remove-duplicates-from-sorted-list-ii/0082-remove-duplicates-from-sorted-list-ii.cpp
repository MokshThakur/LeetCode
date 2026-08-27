class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;
        ListNode* curr = head;

        while (curr != NULL) {

            bool duplicate = false;

            while (curr->next != NULL &&
                   curr->val == curr->next->val) {

                duplicate = true;
                curr = curr->next;
            }

            if (duplicate) {
                prev->next = curr->next;
            }
            else {
                prev = prev->next;
            }

            curr = curr->next;
        }

        return dummy->next;
    }
};