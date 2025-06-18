ListNode* Solution::solve(ListNode* A) {
    vector<int> evenVals;
    ListNode* curr = A;
    int index = 0;
    while (curr) {
        if (index % 2 == 1) {
            evenVals.push_back(curr->val);
        }
        curr = curr->next;
        index++;
    }
    curr = A;
    index = 0;
    int revIndex = evenVals.size() - 1;
    while (curr) {
        if (index % 2 == 1) {
            curr->val = evenVals[revIndex--];
        }
        curr = curr->next;
        index++;
    }
    return A;
}