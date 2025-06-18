int Solution::kthsmallest(const vector<int> &A, int B) {
    map<int, int> freq;
    for (int i = 0; i<A.size(); i++) freq[A[i]]++;
    for (auto it = freq.begin(); it != freq.end(); it++)
    {
        B -= it->second;
        if (B <= 0) return it->first;
    }
}