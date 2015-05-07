#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100005;
const int M = 1000000;
int n , ca;
pair<int , int> a[N];
inline int id(int l , int r) {
    return l + r | l != r;
}
#define MID int mid = l + r >> 1
#define Left l , mid
#define Right mid + 1 , r
#define THIS p , l , mid , r
struct stree {
    int m , f;
}t[4000005];
inline void pushdown(int p , int l , int mid , int r) {
    if (t[p].f) {
        int L = id(Left) , R = id(Right);
        t[L].f += t[p].f , t[L].m += t[p].f;
        t[R].f += t[p].f , t[R].m += t[p].f;
        t[p].f = 0;
    }
}
inline void pushup(int p , int l , int mid , int r) {
    t[p].m = min(t[id(Left)].m , t[id(Right)].m);
}
void update(int l , int r , int top , int bot , int w) {
    int p = id(l , r);
    if (top <= l && r <= bot) {
        t[p].f += w , t[p].m += w;
        return;
    } MID; pushdown(THIS);
    if (top <= mid) update(Left , top , bot , w);
    if (bot > mid) update(Right , top , bot , w);
    pushup(THIS);
}
int query(int l , int r , int top , int bot) {
    int p = id(l , r);
    if (top <= l && r <= bot)
        return t[p].m;
    MID; pushdown(THIS);
    if (bot <= mid) return query(Left , top , bot);
    if (top > mid) return query(Right , top , bot);
    return min(query(Left , top , bot) , query(Right , top , bot));
}

vector< pair<int , int> > V;

bool check(int R) {
    memset(t , 0 , sizeof(t));
    V.clear();

    for (int i = 1 ; i <= n ; ++ i) {
        int x = a[i].first;
        V.push_back(make_pair(x - R , i));
        V.push_back(make_pair(x + R + 1 , -i));
    }
    sort(V.begin() , V.end());
    for (int i = -R , j = 0 ; i <= R ; ++ i) {
        int k = j;
        while (j < V.size() && V[j].first <= i) {
            int x = V[j].second;
            if (x > 0) {
                int l = max(0 , a[x].second - R + M);
                int r = min(M + M , a[x].second + R + M);
                update(0 , M + M , l , r , 1);
            } else {
                x = -x;
                int l = max(0 , a[x].second - R + M);
                int r = min(M + M , a[x].second + R + M);
                update(0 , M + M , l , r , -1);
            }
            ++ j;
        }
        if (k != j && !query(0 , M + M , -R + M , R + M))
            return 1;
    }
    return 0;
}

void work() {
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d" , &a[i].first , &a[i].second);
    }
    int l = 0 , r = M + 5 , m;
    while (l < r) {
        m = l + r >> 1;
        if (!check(m))
            r = m;
        else
            l = m + 1;
    }
    printf("Case %d: " , ++ ca);
    if (!n || r > M)
        puts("never");
    else
        printf("%d\n" , r);
}

int main() {
    while (scanf("%d" , &n) , ~n)
        work();
    return 0;
}
