void generateSubsets(int index, vector<int>& A, vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);

    for (int i = index; i < A.size(); ++i) {
        if (i > index && A[i] == A[i - 1]) continue;

        current.push_back(A[i]);
        generateSubsets(i + 1, A, current, result);
        current.pop_back();
    }
}

vector<vector<int>> Solution::subsetsWithDup(vector<int> &A) {
    sort(A.begin(), A.end());
    vector<vector<int>> result;
    vector<int> current;
    generateSubsets(0, A, current, result);
    return result;
}
