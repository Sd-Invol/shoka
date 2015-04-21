#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m;
char str[N] , s[N];
int f[17][N] , dep[N] , cnt[N] , fa[N];

int sa[N] , t1[N] , t2[N] , c[N];
int Rank[17][N] , rnk[N];

inline int get(int x , int k) {
    while (k) {
        x = f[__builtin_ctz(k & -k)][x];
        k &= (k - 1);
    }
    return x;
}
inline int LCP(int x , int y) {
    int len = 0;
    for (int i = 16 ; i >= 0 ; -- i)
        if (Rank[i][x] && Rank[i][x] == Rank[i][y]) {
            len += 1 << i;
            x = f[i][x];
            y = f[i][y];
        }
    return len;
}
void buildsa(char *s , int n , int m) {
    int i , j , k , p , a1 , a2 , *x = t1 , *y = t2;
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
        // y -> the later k-length substring order
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

void work() {
    int i , j , x , y;
    scanf("%s" , str);
    //strcpy(str , "aaa--bb-c");
    //strcpy(str , "aba-caba");
    m = strlen(str);
    x = 0;
    for (i = 0 ; i < m ; ++ i) {
        if (str[i] == '-')
            x = f[0][x];
        else {
            f[0][++ n] = x;
            s[n] = str[i] , dep[n] = dep[x] + 1;
            x = n;
        }
    }
    for (j = 1 ; 1 << j < n ; ++ j)
        for (i = 1 ; i <= n ; ++ i)
            f[j][i] = f[j - 1][f[j - 1][i]];
    buildsa(s , n , 128);
    /*for (i = 1 ; i <= n ; ++ i) {
        x = sa[i];
        while (x) {
            putchar(s[x]);
            x = f[0][x];
        }
        puts("");
    }
    for (j = 0 ; 1 << j < n ; ++ j) {
        for (i = 1 ; i <= n ; ++ i)
            printf("%d%c" , Rank[j][i] , " \n"[i == n]);
    }*/
    set<int> Hash;
    x = n = 0;
    LL res = 0;
    for (i = 0 ; i < m ; ++ i) {
        if (str[i] == '-') {
            res -= cnt[x];
            Hash.erase(rnk[x]);
            x = f[0][x];
        } else {
            ++ n;
            auto it = Hash.lower_bound(rnk[n]);
            if (it != Hash.end())
                cnt[n] = max(cnt[n] , LCP(n , sa[*it]));
            if (it != Hash.begin())
                cnt[n] = max(cnt[n] , LCP(sa[*(-- it)] , n));
            cnt[n] = dep[n] - cnt[n];
            res += cnt[n];
            //printf("%d : %d %d\n" , n , dep[n] , cnt[n]);
            x = n;
            Hash.insert(rnk[x]);
        }
        printf("%lld\n" , res);
    }
}

int main() {
    work();
    return 0;
}
