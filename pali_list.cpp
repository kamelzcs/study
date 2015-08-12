/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverse(ListNode* cur){
        if(!cur || !cur->next){
            return cur;
        }
        ListNode *ans = reverse(cur->next);
        ListNode *tail = cur->next;
        cur->next = tail->next;
        tail->next = cur;
        return ans;
    }
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next){
            return true;
        }
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *slow = dummy, *fast = dummy;
        while(fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* second_start = reverse(slow->next);
        ListNode* first_start = head;
        while(true) {
            if(first_start->val != second_start->val){
                return false;
            }
            if(first_start == slow){
                break;
            }
            first_start = first_start->next;
            second_start = second_start->next;
        }
        return true;
    }
};

