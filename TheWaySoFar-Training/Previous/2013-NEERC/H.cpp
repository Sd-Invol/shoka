#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 100005 , M = 4000005;
int n , a[N] , X[N];
int root[N] , MAGIC = 30;
int f[17][N];
int nodecnt , u[M][2] , sum[M];

int newnode(int q) {
    u[nodecnt][0] = u[nodecnt][1] = 0;
    sum[nodecnt] = sum[q] ; return nodecnt ++;
}

void insert(int p , int q , int x) {
    for (int i = MAGIC ; i >= 0 ; -- i) {
        int c = x >> i & 1;
        if (!u[p][c]){
            u[p][c] = newnode(u[q][c]);
            u[p][!c] = u[q][!c];
        }
        p = u[p][c] , q = u[q][c];
    }
    ++ sum[p];
}
int query(int p , int q , int x) {
    for (int i = MAGIC ; i >= 0 ; -- i) {
        int c = x >> i & 1;
        p = u[p][c] , q = u[q][c];
    }
    return sum[p] - sum[q];
}

inline int andsum(int l , int r) {
    int j = log2(r - l + 1);
    return f[j][l] & f[j][r - (1 << j) + 1];
}

void work() {
    int i , j , k , x , y;
    scanf("%d",&n);
    nodecnt = 0;
    newnode(0); sum[0] = 0;
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d",&a[i]);
    memset(root , 0 , sizeof(root));
    memset(f , 0 , sizeof(f));
    root[0] = newnode(0);
    insert(root[0] , 0 , 0);
    for (i = 1 ; i <= n ; ++ i) {
        X[i] = X[i - 1] ^ a[i];
        f[0][i] = a[i] , root[i] = newnode(0);
        insert(root[i] , root[i - 1] , X[i]);
    }
    //cout << query(root[3] , root[2] , 0) << endl;
    for (j = 1 ; 1 << j <= n ; ++ j)
        for (i = 1 ; i + (1 << j) - 1 <= n ; ++ i)
            f[j][i] = f[j - 1][i] & f[j - 1][i + (1 << j - 1)];
    long long res = 0;
    for (i = 1 ; i <= n ; ++ i) {
        x = i , y = a[i];
        while (x <= n) {
            int top = x , bot = n , mid;
            while (top < bot) {
                mid = top + bot + 1 >> 1;
                if (andsum(i , mid) < y)
                    bot = mid - 1;
                else
                    top = mid;
            }
            k = top; // [x , k];
            res += query(root[k] , root[x - 1] , X[i - 1] ^ y);
            x = k + 1 , y = andsum(i , x);
        }
    }
    cout << res << endl;
}

int main() {
    freopen("hack.in" , "r" , stdin);
    freopen("hack.out" , "w" , stdout);
    work();
    return 0;
}
