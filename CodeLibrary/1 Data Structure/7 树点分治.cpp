pair<int , int> Find(int x , int fa , int cnt) {
    s[x] = 1; int m = 0;
    pair<int , int> res = make_pair(1 << 30 , -1);
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (!f[e[i].x] && e[i].x != fa) {
            res = min(res , Find(e[i].x , x , cnt));
            m = max(s[e[i].x] , m);
            s[x] += s[e[i].x];
        }
    m = max(m , cnt - s[x]);
    return min(res , make_pair(m , x));
}
void Getdis(int x , int fa , LL d) {
    S[size ++] = d;
    ans += hash[sub(w , d)];
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y] && y != fa)
            Getdis(y , x , add(d , a[y]));
    }
}
void divide(int x , int cnt) {
    x = Find(x , 0 , cnt).second;
    f[x] = 1 , w = sub(0 , a[x]) , hash.clear();
    ++ hash[0]; if (w == 0) ++ ans;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y]) {
            Getdis(y , x , a[y]);
            s[y] = size;
            while (size)
                ++ hash[S[-- size]];
        }
    }
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[y])
            divide(y , s[y]);
    }
}
