ListNode* Solution::deleteDuplicates(ListNode* A) {
    ListNode* curr = A;
    while(curr!=nullptr && curr->next!=nullptr)
    {
        if(curr->next->val == curr->val)
        {
            curr->next = curr->next->next;
        }
        else
        {
            curr = curr->next;
        }
    }
    return A;
}