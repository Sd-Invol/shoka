#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , a[N];
const int INTMIN = -1.5e9;
const int INTMAX = 1.5e9;

struct opt {
    int mx , mn , delta;
    opt () {
        mx = INTMAX;
        mn = INTMIN;
        delta = 0;
    }    
    inline int f(int x) const {
        return min(mx , max(mn , x + delta));
    };
    void operator += (const opt& A) {
        this -> delta += A.delta;
        this -> mx = A.f(this -> mx);
        this -> mn = A.f(this -> mn);
    }
};

struct stree {
    opt f;
    int mx , mn;
}t[N << 1];
inline int id(int l , int r) { return l + r | l != r;}
#define MID int mid = l + r >> 1
#define THIS p , l , mid , r
#define Left l , mid
#define Right mid + 1 , r

void pushdown(int p , int l , int mid , int r) {
    if (t[p].f.delta == 0 && t[p].f.mx == INTMAX && t[p].f.mn == INTMIN)
        return;
    int L = id(Left) , R = id(Right);
    t[L].f += t[p].f;
    t[L].mn = t[p].f.f(t[L].mn) , t[L].mx = t[p].f.f(t[L].mx);
    t[R].f += t[p].f;
    t[R].mn = t[p].f.f(t[R].mn) , t[R].mx = t[p].f.f(t[R].mx);
    t[p].f = opt();
}
void pushup(int p , int l , int mid , int r) {
    int L = id(Left) , R = id(Right);
    t[p].mx = max(t[L].mx , t[R].mx);
    t[p].mn = min(t[L].mn , t[R].mn);    
}
void Build(int l , int r) {
    int p = id(l , r);
    t[p].f = opt();
    if (l == r)
        t[p].mx = t[p].mn = a[l];
    else {
        MID; Build(Left); Build(Right);
        pushup(THIS);
    }
}
void update(int l , int r , int top , int bot , const opt& w) {
    int p = id(l , r);
    if (top <= l && r <= bot) {
        t[p].f += w;
        t[p].mx = w.f(t[p].mx);
        t[p].mn = w.f(t[p].mn);        
        return;
    } MID; pushdown(THIS);
    if (top <= mid) update(Left , top , bot , w);
    if (bot > mid) update(Right , top , bot , w);
    pushup(THIS);
}
int Mx , Mn;
void query(int l , int r , int top , int bot) {
    int p = id(l , r);
    if (top <= l && r <= bot) {
        Mx = max(Mx , t[p].mx);
        Mn = min(Mn , t[p].mn);        
        return;
    } MID; pushdown(THIS);
    if (top <= mid) query(Left , top , bot);
    if (bot > mid) query(Right , top , bot);
}

void work() {
    int i , x , y , w;
    scanf("%d%d",&n,&m);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d" , &a[i]);
    Build(1 , n);
    while (m --) {
        scanf("%d%d%d",&i,&x,&y);
        if (i != 4) {
            scanf("%d",&w);
            opt W;
            if (i == 1)
                W.delta = w;
            if (i == 2)
                W.mx = w;
            if (i == 3)
                W.mn = w;
            update(1 , n , x , y , W);
        } else {
            Mx = INTMIN , Mn = INTMAX;
            query(1 , n , x , y);
            printf("%d %d\n" , Mn , Mx);
        }
    }
}

int main() {
    work();
    return 0;
}
