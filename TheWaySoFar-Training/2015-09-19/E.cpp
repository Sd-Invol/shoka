#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 400005;
int n , m , ca;

inline int id(int l , int r) {
    return l + r | l != r;
}
struct data {
    int len;
    LL s , a , b;
    void add(int w) {
        s += (LL)w * len;
        a += (LL)w * len * (len + 1) / 2;
        b += (LL)w * len * (len + 1) / 2;        
    }
};
data operator + (const data& A , const data& B) {
    data C;
    C.len = A.len + B.len;
    C.s = A.s + B.s;
    C.a = A.a + A.s * B.len + B.a;
    C.b = B.b + B.s * A.len + A.b;
    return C;
}
struct stree {
    int f;
    data v;
    void add(int w) {
        f += w;
        v.add(w);
    }
    void clear(int l) {
        f = 0;
        v.len = l;
        v.s = v.a = v.b = 0;
    }
}tt[2][N << 1];
stree *t;
#define MID int mid = (l + r) >> 1
#define THIS p , l , mid , r
#define Left l , mid
#define Right mid + 1 , r
void pushdown(int p , int l , int mid , int r) {
    if (t[p].f) {
        int L = id(Left) , R = id(Right);
        t[L].add(t[p].f);
        t[R].add(t[p].f);
        t[p].f = 0;
    }
}
void pushup(int p , int l , int mid , int r) {
    int L = id(Left) , R = id(Right);
    t[p].v = t[L].v + t[R].v;
}
void add(int l , int r , int top , int bot) {
    int p = id(l , r);
    if (top <= l && r <= bot) 
        return t[p].add(1);        
    MID; pushdown(THIS);
    if (top <= mid) add(Left , top , bot);
    if (bot > mid) add(Right , top , bot);
    pushup(THIS);
}
void clear(int l , int r) {
    int p = id(l , r); t[p].clear(r - l + 1);
    if (l == r) return; MID;
    clear(Left) , clear(Right);
}
data get(int l , int r , int top , int bot) {
    int p = id(l , r);
    if (top <= l && r <= bot)
        return t[p].v;
    MID; pushdown(THIS);
    if (bot <= mid) return get(Left , top , bot);
    if (top > mid) return get(Right , top , bot);
    return get(Left , top , bot) + get(Right , top , bot);
}


void work() {
    printf("Case #%d:\n" , ++ ca);
    scanf("%d%d" , &n , &m);
    t = tt[0] , clear(1 , n + n);
    t = tt[1] , clear(1 , n + n);

    while (m --) {
        int i;
        scanf("%d" , &i);
        if (i < 3) {
            int L , R;
            scanf("%d%d" , &L , &R);
            if (i == 1) {
                t = tt[0];
                add(1 , n + n , L , R);
            } else {
                t = tt[1];
                add(1 , n + n , L + n , R + n);
            }
        } else {
            int x1 , x2 , y1 , y2;
            scanf("%d%d%d%d" , &x1 , &x2 , &y1 , &y2);
            LL res = 0; data d;
            int len = min(x2 - x1 , y2 - y1);            
            t = tt[0];
            if (len) {
                d = get(1 , n + n , x1 + y1 , x1 + y1 + len - 1);
                res += d.b;
                d = get(1 , n + n , x2 + y2 - len + 1 , x2 + y2);
                res += d.a;
            }
            d = get(1 , n + n , x1 + y1 + len , x2 + y2 - len);
            res += d.s * (1 + len);
            t = tt[1];
            if (len) {
                d = get(1 , n + n , x1 - y2 + n , x1 - y2 + len - 1 + n);
                res += d.b;
                d = get(1 , n + n , x2 - y1 - len + 1 + n , x2 - y1 + n);
                res += d.a;
            }
            d = get(1 , n + n , x1 - y2 + len + n , x2 - y1 - len + n);
            res += d.s * (1 + len);            
            printf("%lld\n" , res);
        }        
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
