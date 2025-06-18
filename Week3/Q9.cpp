int Solution::pow(int x, int n, int d) {
    long long base = x % d;
    long long result = 1;
    for (int i = n; i>0; i/=2)
    {
        if (i%2==1) result = (result*base)%d;
        base = (base*base)%d;
    }
    return (result + d) % d;
}
