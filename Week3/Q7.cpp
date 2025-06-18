int Solution::findCount(const vector<int> &A, int B) {
    int n = A.size();
    int low = 0, high = n - 1, first = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (A[mid] == B) {
            first = mid;
            high = mid - 1;
        } else if (A[mid] < B) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (first == -1) return 0;
    low = 0, high = n - 1;
    int last = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (A[mid] == B) {
            last = mid;
            low = mid + 1;
        } else if (A[mid] < B) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return last - first + 1;
}
