#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
int bo[N], prime[N], r, phi;

typedef long long LL;
int P;

int power(int a, LL n) {
    if (n < 0) return 0;
    int ans = 1, z = a % P;
    while (n > 0) {
        if (n & 1) ans = (LL)ans * z % P;
        n >>= 1;
        z = (LL)z * z % P;
    }
    return ans;
}

vector<int> getprime(int P) {
    vector<int> ans;
    for (int i = 0; (LL)prime[i] * prime[i] <= (LL)P; ++i)
        if (P % prime[i] == 0) {
            ans.push_back(prime[i]);
            while (P % prime[i] == 0) P /= prime[i];
        }
    if (P > 1) ans.push_back(P);
    return ans;
}

LL tree[N * 4], mark[N * 4];

void exgcd(int a, int b, LL &X, LL &Y) {
    if (b == 0) {
        X = 1, Y = 0;
        return ;
    }
    exgcd(b, a % b, Y, X);
    Y -= (a / b) * X;
}

int inverse(int x) {
    return power(x, phi - 1);
}

void build(int k, int m, int n) {
    tree[k] = 1;
    mark[k] = 1;
    if (m == n) return ;
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    build(z1, m, mid);
    build(z2, mid + 1, n);
    //tree[k] = (LL)tree[z1] * tree[z2] % P;
}


void pushdown(int k, int m, int n) {
    if (mark[k] != 1) {
        int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
        tree[z1] = (LL)tree[z1] * power(mark[k], mid - m + 1) % P;
        tree[z2] = (LL)tree[z2] * power(mark[k], n - mid) % P;
        mark[z1] = (LL)mark[z1] * mark[k] % P;
        mark[z2] = (LL)mark[z2] * mark[k] % P;
        mark[k] = 1;
    }
}

void modify(int k, int m, int n, int l, int r, int x) {
    if (m > r || n < l) return ;
    if (m >= l && n <= r) {
        tree[k] = (LL)tree[k] * power(x, n - m + 1) % P;
        mark[k] = (LL)mark[k] * x % P; 
        return ;
    }
    pushdown(k, m, n);
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    modify(z1, m, mid, l, r, x);
    modify(z2, mid + 1, n, l, r, x);
    tree[k] = (LL)tree[z1] * tree[z2] % P;
}

int query(int k, int m, int n, int l, int r) {
    if (m > r || n < l) return 1;
    if (m >= l && n <= r) return tree[k];
    pushdown(k, m, n);
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    return (LL)query(z1, m, mid, l, r) *
        query(z2, mid + 1, n, l, r) % P;
}
struct CHU_2_BIT {
    int n;
    LL B[N] , C[N];
    void init(int size) {
        n = size;
        memset(B , 0 , (n + 1) << 3);
        memset(C , 0 , (n + 1) << 3);
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
}f[30];

int main() {
    int T;
    r = 0;
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            prime[r++] = i;
            for (int j = i + i; j < N; j += i)
                bo[j] = 1;
        }
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d%d", &n, &P);
        vector<int> ver = getprime(P);
        phi = P;
       
        for (int i = 0; i < ver.size(); ++i) {
            f[i].init(n);
            phi = phi / ver[i] * (ver[i] - 1);
        }
        build(1, 1, n);
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            if (x == 0) {
                modify(1, 1, n, i, i, 0);
                continue;
            }
            for (int j = 0; j < ver.size(); ++j)
                if (x % ver[j] == 0) {
                    int num = 0;
                    while (x % ver[j] == 0) {
                        ++num;
                        x /= ver[j];
                    }
                    f[j].add(i , i , num);
                }
            x %= P;
            modify(1, 1, n, i, i, x);
        }
        int m;
        static int ca = 0;
        printf("Case #%d:\n", ++ca);
        scanf("%d", &m);
        while (m--) {
            int ch;
            while (ch = getchar(), !isalpha(ch));
            if (ch == 'M') {
                int L, R, x;
                scanf("%d%d%d", &L, &R, &x);
                if (x == 0) {
                    modify(1, 1, n, L, R, 0);
                }
                else {
                    for (int j = 0; j < ver.size(); ++j)
                        if (x % ver[j] == 0) {
                            int num = 0;
                            while (x % ver[j] == 0) {
                                ++num;
                                x /= ver[j];
                            }
                            f[j].add(L , R , num);
                        }
                    x %= P;
                    modify(1, 1, n, L, R, x);
                }
            }
            else if (ch == 'D') {
                int L, R, x;
                scanf("%d%d%d", &L, &R, &x);
                for (int j = 0; j < ver.size(); ++j)
                    if (x % ver[j] == 0) {
                        int num = 0;
                        while (x % ver[j] == 0) {
                            ++num;
                            x /= ver[j];
                        }
                        f[j].add(L , R , -num);
                    }
                x = inverse(x % P);
                modify(1, 1, n, L, R, x);
            }
            else {
                int L, R;
                scanf("%d%d", &L, &R);
                
                int ans = query(1, 1, n, L, R);
                //cout << ans << endl;
                for (int j = 0; j < ver.size(); ++j) {
                    LL num = f[j].sum(L, R);
                    // cout << ver[j] << ' ' << num << endl;
                    ans = (LL)ans * power(ver[j], num) % P;
                }
                printf("%d\n", ans % P);
            }
        }
    }
    return 0;
}