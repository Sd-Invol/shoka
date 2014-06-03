#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cmath>
#pragma comment(linker, "/STACK:16777216")
using namespace std;
typedef long long LL;
#define N 200005
int ca;
int n , m , a[N];
template <class T> struct Treap {
    int nodecnt , prior[N];
    int cnt[N] , size[N] , c[N][2];
    T key[N] , GCD[N];
    void clear() {
        nodecnt = 1;
        prior[0] = -1 << 30;
    }
    Treap () {
        clear();
    }
    inline void pushup(int p) {
        size[p] = size[c[p][0]] + size[c[p][1]] + cnt[p];
        GCD[p] = __gcd(__gcd(GCD[c[p][0]] , GCD[c[p][1]]) , key[p]);
    }
    inline void rotate (int& x , int t) {
        int y = c[x][t];
        c[x][t] = c[y][!t] , c[y][!t] = x;
        pushup(x) , pushup(y) , x = y;
    }
    inline void newnode(int& p , T w) {
        p = nodecnt ++;
        key[p] = GCD[p] = w , cnt[p] = size[p] = 1;
        prior[p] = rand() , c[p][0] = c[p][1] = 0;
    }
    void insert(int& p , T w) {
        if (!p) {
            newnode(p , w);
            return;
        }
        if (key[p] == w)
            ++ cnt[p];
        else {
            int t = key[p] < w;
            insert(c[p][t] , w);
            if (prior[c[p][t]] > prior[p])
                rotate(p , t);
        }
        pushup(p);
    }
    void erase(int& p , T w) {
        if (!p) return;
        if (key[p] == w) {
            if (!-- cnt[p]) {
                if (!c[p][0] && !c[p][1])
                    p = 0;
                else {
                    rotate(p , prior[c[p][0]] < prior[c[p][1]]);
                    erase(p , w);
                }
            }
        } else
            erase(c[p][key[p] < w] , w);
        pushup(p);
    }
};
Treap<int> T;
int root[N >> 1] , id[N];

void work() {
    printf("Case #%d:\n" , ++ ca);
    int i , j , x , y , z;
    scanf("%d%d",&n,&m);
    T.clear();
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        root[i] = 0 , id[i] = i;
        T.insert(root[i] , a[i]);
    }
    while (m --) {
        //scanf("%d")


    }

}

int main()
{
    freopen("~input.txt" , "r" , stdin);
    int _; scanf("%d",&_); while (_ --)
        work();
    return 0;
}
