ListNode* Solution::getIntersectionNode(ListNode* A, ListNode* B) {
    ListNode* p1 = A;
    ListNode* p2 = B;
    
    while (p1!=p2)
    {
        p1 = (p1 == nullptr) ? B : p1->next;
        p2 = (p2 == nullptr) ? A : p2->next;
    }
    return p2;
}
