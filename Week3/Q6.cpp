ListNode* Solution::reverseList(ListNode* A) {
    if (A == nullptr || A->next == nullptr)
        return A;

    ListNode* rest = reverseList(A->next);
    A->next->next = A;
    A->next = nullptr;
    return rest;
}