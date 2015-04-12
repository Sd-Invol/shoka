#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
int n , m , res;
int p[N] , q[N] , t[N];

struct SplayTree {
    int type[N] , f[N] , c[N][2] , s[N];
    void pushup(int x) {
        s[x] = s[c[x][0]] + 1 + s[c[x][1]];
    }
    void rotate(int x) {
        int t = type[x] , y = f[x] , z = c[x][!t] ;
        type[x] = type[y] , f[x] = f[y];
        if (~type[x]) c[f[x]][type[x]] = x;
        type[y] = !t , f[y] = x , c[x][!t] = y;
        if (z) type[z] = t , f[z] = y;
        c[y][t] = z , pushup(y);
    }
    void splay(int x) {
        while (~type[x]) {
            int y = f[x];
            (type[y] == type[x]) ?
                rotate(y) : rotate(x);
            if (~type[x])
                rotate(x);
        }
        pushup(x);
    }
    int getKth(int x , int k) {
        while (x) {
            if (s[c[x][0]] + 1 == k)
                return x;
            if (k <= s[c[x][0]])
                x = c[x][0];
            else
                k -= s[c[x][0]] + 1 , x = c[x][1];
        }
        return x;
    }
    void merge(int x ,int y) {
        //printf("+%d %d\n" , x , y);
        splay(x);
        splay(y);            
        assert(!c[x][1]);
        assert(!c[y][0]);            
        c[x][1] = y;
        type[y] = 1;
        f[y] = x;
        res -= s[x] >> 1;
        res -= s[y] >> 1;        
        s[x] += s[y];
        res += s[x] >> 1;
    }
    void split(int x , int y) {
        //printf("-%d %d\n" , x , y);
        splay(x);
        res -= s[x] >> 1;
        type[c[x][1]] = -1;
        f[c[x][1]] = 0;
        s[x] -= s[c[x][1]];
        splay(y);
        type[c[y][0]] = 1;
        f[c[y][0]] = x;
        c[x][1] = c[y][0];
        s[y] -= s[c[y][0]];
        s[x] += s[c[y][0]];
        c[y][0] = 0;
        res += s[x] >> 1;
        res += s[y] >> 1;
    }
};
SplayTree T;

int main () {
    int i , j , x , y;
    scanf("%d" ,&n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &p[i]);
        q[p[i]] = i;
    }
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d" , &t[i]);    

    for (i = 1 ; i <= n ; ++ i) {
        T.type[i] = -1;
        T.s[i] = 1;
        T.f[i] = T.c[i][0] = T.c[i][1] = 0;
    }
    
    for (i = 1 ; i <= n ; ++ i)
        if (t[i] > t[q[i]])
            T.merge(i , p[i]);
    printf("%d\n" , res);
    scanf("%d" , &m);
    while (m --) {
        scanf("%d%d" , &x , &y);
        if (t[x] > t[q[x]] && y < t[q[x]])
            T.split(x , p[x]);
        x = p[x];
        if (t[x] > t[q[x]] && t[x] < y)
            T.split(x , p[x]);
        x = q[x];
        if (t[x] < t[q[x]] && y > t[q[x]])
            T.merge(x , p[x]);
        x = p[x];        
        if (t[x] < t[q[x]] && t[x] > y)
            T.merge(x , p[x]);
        t[q[x]] = y;
        printf("%d\n" , res);
    }
    return 0;
}

/*
2 4 1 7 5 6 3

7
2 3 4 5 6 7 1
3 1 7 2 5 6 4
0
 */
