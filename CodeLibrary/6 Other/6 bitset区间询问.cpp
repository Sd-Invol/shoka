int u[N] , v[N];
struct Range {
    int key[N] , val[N];
    bitset<N> w[N / B + 1][N / B + 1];
    void init() { // u有序，B可以开大一点
        int m = (n + B - 1) / B;
        for (int i = 0 ; i < n ; ++ i) {
            key[i] = u[i];
            val[i] = v[i];
        }
        for (int i = 0 ; i < m ; ++ i) {
            int L = i * B , R = min(n , L + B);
            for (int j = L ; j < R ; ++ j) {
                w[i][i].set(v[j]);
            }
        }
        for (int i = 0 ; i < m ; ++ i) {
            for (int j = i + 1 ; j < m ; ++ j) {
                w[i][j] = w[i][j - 1] | w[j][j];
            }
        }
    } // 提取key在一个区间内的val构成的bitset
    bitset<N> get(int l , int r) {
        l = lower_bound(key , key + n , l) - key;
        r = upper_bound(key , key + n , r) - key;
        int ll = l / B , rr = r / B;
        bitset<N> ret;
        if (ll == rr) {
            for (int i = l ; i < r ; ++ i)
                ret.set(val[i]);
        } else {
            ret |= w[ll + 1][rr - 1];
            int R = (ll + 1) * B , L = rr * B;
            for (int i = l ; i < R ; ++ i)
                ret.set(val[i]);
            for (int i = L ; i < r ; ++ i)
                ret.set(val[i]);
        }
        return ret;
    }
};
