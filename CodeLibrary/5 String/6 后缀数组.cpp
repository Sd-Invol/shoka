int sa[N] , t1[N] , t2[N] , c[N];
int Rank[N] , height[N];
void buildsa(char *s , int n , int m) {
    int i , k , p , a1 , a2 , *x = t1 , *y = t2;
    memset(c , 0 , m << 2);
    for (i = 0 ; i < n ; ++ i) ++ c[x[i] = s[i]];
    for (i = 1 ; i < m ; ++ i) c[i] += c[i - 1];
    for (i = n - 1 ; i >= 0 ; -- i) sa[-- c[x[i]]] = i;
    for (k = 1 , p = 0; k < n ; k <<= 1 , p = 0) {
        for (i = n - k ; i < n ; ++ i) y[p ++] = i;
        for (i = 0 ; i < n ; ++ i) if (sa[i] >= k) y[p ++] = sa[i] - k;
        memset(c , 0 , m << 2);
        for (i = 0 ; i < n ; ++ i) ++ c[x[y[i]]];
        for (i = 1 ; i < m ; ++ i) c[i] += c[i - 1];
        for (i = n - 1 ; i >= 0 ; -- i) sa[-- c[x[y[i]]]] = y[i];
        swap(x , y) , p = 1 , x[sa[0]] = 0;
        for (i = 1 ; i < n ; ++ i) {
            a1 = sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1;
            a2 = sa[i] + k < n ? y[sa[i] + k] : -1;
            x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && a1 == a2) ? p - 1 : p ++;
        }
        if (p >= n) break; m = p;
    }
    for (i = 0 ; i < n ; ++ i) Rank[sa[i]] = i;
    for (i = 0 , k = 0; i < n ; ++ i) {
        if (k) -- k; if (!Rank[i]) continue;
        int j = sa[Rank[i] - 1];
        while (s[i + k] == s[j + k]) ++ k;
        height[Rank[i]] = k;
    }
}
/******Suffix array for Trie *****/
int f[18][N] , s[N] , dep[N];
int sa[N] , t1[N] , t2[N] , c[N];
int Rank[18][N] , rnk[N];
inline int LCP(int x , int y) {
    int len = 0;
    for (int i = 17 ; i >= 0 ; -- i)
        if (Rank[i][x] && Rank[i][x] == Rank[i][y]) {
            len += 1 << i;
            x = f[i][x];
            y = f[i][y];
        }
    return len;
}
void buildsa(int *s , int n , int m) {
    int i , j , k , p , a1 , a2;
    int *x = t1 , *y = t2;
    memset(c , 0 , m + 1 << 2);
    for (i = 1 ; i <= n ; ++ i) ++ c[x[i] = s[i]];
    for (i = 1 ; i <= m ; ++ i) c[i] += c[i - 1];
    for (i = n ; i >= 1 ; -- i) sa[c[x[i]] --] = i;
    for (k = 1 , j = 0 , p = 0; k < n ; k <<= 1 , ++ j) {
        memset(c , 0 , m + 1 << 2);
        for (i = 1 ; i <= n ; ++ i) Rank[j][i] = x[i];
        for (i = 1 ; i <= n ; ++ i) ++ c[x[f[j][i]]];
        for (i = 1 ; i <= m ; ++ i) c[i] += c[i - 1];
        for (i = n ; i >= 1 ; -- i) y[c[x[f[j][i]]] --] = i;
        memset(c , 0 , m + 1 << 2);
        for (i = 1 ; i <= n ; ++ i) ++ c[x[y[i]]];
        for (i = 1 ; i <= m ; ++ i) c[i] += c[i - 1];
        for (i = n ; i >= 1 ; -- i) sa[c[x[y[i]]] --] = y[i];
        swap(x , y) , p = 1 , x[sa[1]] = 1;
        for (i = 2 ; i <= n ; ++ i) {
            a1 = y[f[j][sa[i - 1]]];
            a2 = y[f[j][sa[i]]];
            x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && a1 == a2) ? p : ++ p;
        }
        m = p;
    }
    for (i = 1 ; i <= n ; ++ i) rnk[sa[i]] = i;
}
