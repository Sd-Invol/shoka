#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stack>
#include <queue>
typedef long long LL;
using namespace std;
const int N = 100005;
const int Q = 1e9 + 7;

int n;
int a[N][3];
int p[N] , q[N];

int t[N] , sum[N] , c[N];

bool cmp(int x , int y) {
    if (p[x] != p[y])
        return p[x] < p[y];
    return q[x] < q[y];
}

void divide(int l , int r) {
    if (l >= r)
        return;
    int mid = l + r >> 1;
    int m = 0;
    for (int i = l ; i <= r ; ++ i) {
        t[m ++] = i;       
    }
    sort(t , t + m , cmp);
    for (int i = 0 ; i < m ; ++ i) {
        int x = t[i];
        if (x <= mid) {
            for (int j = q[x] ; j <= n ; j += j & -j)
                ++ c[j];
        } else {
            for (int j = q[x] ; j > 0 ; j -= j & -j)
                sum[x] += c[j];
        }
    }
    for (int i = 0 ; i < m ; ++ i) {
        if (t[i] <= mid) {
            for (int j = q[t[i]] ; j <= n ; j += j & -j)
                c[j] = 0;
        }
    }
    divide(l , mid);
    divide(mid + 1 , r);
}

int main() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i) {
        for (int j = 0 ; j < 3 ; ++ j)
            scanf("%d" , &a[i][j]);
    }
    LL res = n + (LL)n * (n - 1) / 2 + (LL)n * (n - 1) * (n - 2) / 6;
    for (int i = 1 ; i <= n ; ++ i) {
        p[a[i][0]] = a[i][1];
        q[a[i][0]] = a[i][2];
    }
    divide(1 , n);
    for (int i = 1 ; i <= n ; ++ i) {
        res -= sum[i];
        res += (LL)sum[i] * (sum[i] - 1);           
    }

    for (int k = 0 ; k < 3 ; ++ k) {
        for (int i = 1 ; i <= n ; ++ i) {
            p[a[i][k]] = a[i][(k + 1) % 3];
            c[i] = 0;
        }
        for (int i = 1 ; i <= n ; ++ i) {
            int x = p[i] , s = 0;
            for (int j = x ; j > 0 ; j -= j & -j)
                s += c[j];
            res -= (LL)s * (s - 1) / 2;
            for (int j = x ; j <= n ; j += j & -j)
                ++ c[j];
        }
    }
    
    cout << res << endl;
    return 0;
}
