#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m;
bitset<70> a[N];
int f[70][2];
bitset<71> c[70] , b[70];
LL power[40];
int check(int n , int m) {
    /*for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < m ; ++ j)
            printf("%d" , (int)b[i][j]);
        puts("");
    }
    puts("******************");*/
    int Rank = 0;
    for (int i = 0 ; i < m ; ++ i) {
        int pivot = Rank;
        while (pivot < n && !b[pivot][i])
            ++ pivot;
        if (pivot >= n)
            continue;
        swap(b[pivot] , b[Rank]);
        for (int j = 0 ; j < n ; ++ j)
            if (j != Rank && b[j][i])
                b[j] ^= b[Rank];
        ++ Rank;
    }
    if (b[Rank - 1][m - 1] && b[Rank - 1].count() == 1)
        return -1;
    return Rank;
}

void work() {
    int i , j , k , x , y , w;
    char str[100];
    power[0] = 1;
    for (i = 1 ; i <= 35 ; ++ i)
        power[i] = power[i - 1] * 3;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < n ; ++ i) {
        scanf("%s" , str);
        for (j = 0 ; str[j] ; ++ j)
            if (str[j] == '1')
                a[i].set(j);
    }
    int Rank = 0;
    for (i = 0 ; i < m ; ++ i) {
        int pivot = Rank;
        while (pivot < n && !a[pivot][i])
            ++ pivot;
        if (pivot >= n)
            continue;
        swap(a[pivot] , a[Rank]);
        for (j = 0 ; j < n ; ++ j)
            if (j != Rank && a[j][i])
                a[j] ^= a[Rank];
        ++ Rank;
    }
    n = Rank;
    /*for (i = 0 ; i < n ; ++ i) {
        for (j = 0 ; j < m ; ++ j)
            printf("%d" , (int)a[i][j]);
        puts("");
        }*/
    memset(f , -1 , sizeof(f));
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d",&x ,&y);
        if (x == -1)
            f[y][0] = i;
        else
            f[y][1] = i;
    }
    LL res = 0;
    int tot = 0;
    for (k = 35 ; k > 0 ; -- k) {
        if (!~f[k][0] && !~f[k][1])
            continue;
        if (~f[k][0] && ~f[k][1]) {
            x = f[k][0] , y = f[k][1];
            c[tot] &= 0;
            for (i = 0 ; i < n ; ++ i)
                if (a[i][y])
                    c[tot].set(i);
            c[tot ++].set(i);
            c[tot] &= 0;
            for (i = 0 ; i < n ; ++ i)
                if (a[i][x])
                    c[tot].set(i);
            c[tot ++].reset(i);
            for (i = 0 ; i < tot ; ++ i)
                b[i] = c[i];
            w = check(tot , n + 1);
            if (~w) {
                tot = w;
                for (i = 0 ; i < tot ; ++ i)
                    c[i] = b[i];
                res += power[k];
                continue;
            }
            tot -= 2;
            c[tot] &= 0;
            for (i = 0 ; i < n ; ++ i)
                if (a[i][y] ^ a[i][x])
                    c[tot].set(i);
            c[tot ++].reset(i);
            for (i = 0 ; i < tot ; ++ i)
                b[i] = c[i];
            w = check(tot , n + 1);
            if (~w) {
                tot = w;
                for (i = 0 ; i < tot ; ++ i)
                    c[i] = b[i];
                continue;
            }
            tot -= 1;
            res -= power[k];
        } else if (~f[k][0]) {
            x = f[k][0] , c[tot] &= 0;
            for (i = 0 ; i < n ; ++ i)
                if (a[i][x])
                    c[tot].set(i);
            c[tot ++].reset(i);
            for (i = 0 ; i < tot ; ++ i)
                b[i] = c[i];
            w = check(tot , n + 1);
            if (!~w) {
                -- tot;
                res -= power[k];
            } else {
                tot = w;
                for (i = 0 ; i < tot ; ++ i)
                    c[i] = b[i];
            } 
        } else {
            x = f[k][1] , c[tot] &= 0;
            for (i = 0 ; i < n ; ++ i)
                if (a[i][x])
                    c[tot].set(i);
            c[tot ++].set(i);
            for (i = 0 ; i < tot ; ++ i)
                b[i] = c[i];
            w = check(tot , n + 1);
            if (!~w)
                -- tot;
            else {
                tot = w;
                for (i = 0 ; i < tot ; ++ i)
                    c[i] = b[i];
                res += power[k];
            }            
        }
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
