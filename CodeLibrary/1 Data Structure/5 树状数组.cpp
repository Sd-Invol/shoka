int getKth(int k) {
    int x = 0 , i;
    for (i = 16 ; i >= 0 ; -- i)
        if (x + (1 << i) <= D && c[x + (1 << i)] < k) {
            x += 1 << i;
            k -= c[x];
        }
    return x + 1;
}
struct CHU_2_BIT {
    int n;
    LL B[N] , C[N];
    void init(int size) {
        n = size;
        memset(B , 0 , n + 1 << 3);
        memset(C , 0 , n + 1 << 3);
    }
    CHU_2_BIT() {}
    CHU_2_BIT(int size) {
        init(size);
    }
    inline LL _sum(LL* c , int x) {
        LL res = 0;
        for ( ; x > 0 ; x -= x & -x)
            res += c[x];
        return res;
    }
    void add(int l , int r , LL w) {
        for (int i = l ; i <= n ; i += i & -i)
            B[i] += w , C[i] += w * l;
        ++ r;
        for (int i = r ; i <= n ; i += i & -i)
            B[i] -= w , C[i] -= w * r;
    }
    LL sum(int l , int r) {
        LL res = 0; -- l;
        res += (r + 1) * _sum(B , r) - _sum(C , r);
        res -= (l + 1) * _sum(B , l) - _sum(C , l);
        return res;
    }
}T;
