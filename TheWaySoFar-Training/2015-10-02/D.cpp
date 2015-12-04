#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
const int N = 200005;
typedef long long LL;
using namespace std;
const int null = 2147483647;
struct status {
    int l , r , s , sum;
    status () {
        l = r = s = sum = null;
    }
    status rev() {
        status res = *this;
        swap(res.l , res.r);
        return res;
    }
    void set(int v , int len) {
        sum = v * len;
        l = r = s = max(v , sum);
    }
};
status operator + (const status& A , const status& B) {
    if (A.l == null) return B;
    if (B.l == null) return A;
    status C;
    C.sum = A.sum + B.sum;
    C.l = max(A.l , A.sum + B.l);
    C.r = max(B.r , B.sum + A.r);
    C.s = max(max(A.s , B.s) , A.r + B.l);
    return C;
}
struct stree {
    status a;
    int f;
}t[N << 1];
inline int id(int l , int r) {
    return l + r | l != r;
}
#define MID int mid = l + r >> 1
#define THIS p , l , mid , r
#define Left l , mid
#define Right mid + 1 , r
void pushdown(int p , int l , int mid , int r) {
    if (t[p].f != null) {
        int L = id(Left) , R = id(Right);
        t[L].a.set(t[p].f , mid - l + 1);
        t[L].f = t[p].f;
        t[R].a.set(t[p].f , r - mid);
        t[R].f = t[p].f;
        t[p].f = null;
    }
}
void pushup(int p , int l , int mid , int r) {
    int L = id(Left) , R = id(Right);
    t[p].a = t[L].a + t[R].a;
}
void set(int l , int r , int top , int bot , int w) {
    if (top > bot) return;
    int p = id(l , r);
    if (top <= l && r <= bot) {
        t[p].f = w;
        t[p].a.set(w , r - l + 1);
        return;
    } MID; pushdown(THIS);
    if (top <= mid) set(Left , top , bot , w);
    if (bot > mid) set(Right , top , bot , w);
    pushup(THIS);
}
status get(int l , int r , int top , int bot) {
    if (top > bot) return status();
    int p = id(l , r);
    if (top <= l && r <= bot)
        return t[p].a;
    MID; pushdown(THIS);
    if (bot <= mid) return get(Left , top , bot);
    if (top > mid) return get(Right , top , bot);
    return get(Left , top , bot) + get(Right , top , bot);
}
int A[N];
void build(int l , int r) {
    int p = id(l , r);
    t[p].f = null;
    if (l == r) {
        t[p].a.set(A[l] , 1);
    } else {
        MID;
        build(Left);
        build(Right);
        pushup(THIS);
    }
}

int n , m , pre[N] , mcnt , a[N];
struct edge {
    int x , next;
} e[N << 1];


int size[N] , heavy[N] , tid[N] , Top[N] , ncnt , dep[N] , Fa[N];
void FindHE(int x , int fa , int Dep) {
    heavy[x] = 0 , size[x] = 1 , dep[x] = Dep , Fa[x] = fa;
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (e[i].x != fa) {
            int y = e[i].x;
            FindHE(y , x , Dep + 1);
            size[x] += size[y];
            if (!heavy[x] || size[y] > size[heavy[x]])
                heavy[x] = y;
        }
}
void ConnectHE(int x , int anc) {
    tid[x] = ++ ncnt , Top[x] = anc , A[ncnt] = a[x];
    if (heavy[x])
        ConnectHE(heavy[x] , anc);
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (e[i].x != Fa[x] && e[i].x != heavy[x])
            ConnectHE(e[i].x , e[i].x);
}
void query(int i , int x , int y , int w) {
    if (i == 1) {
        while (Top[x] != Top[y]) {
            if (dep[Top[x]] < dep[Top[y]])
                swap(x , y);
            set(1 , n , tid[Top[x]] , tid[x] , w);
            x = Fa[Top[x]];
        }
        if (dep[x] > dep[y]) swap(x , y);
        set(1 , n , tid[x] , tid[y] , w);
    } else {
        status L , R;
        while (Top[x] != Top[y]) {
            if (dep[Top[x]] > dep[Top[y]]) {
                L = L + get(1 , n , tid[Top[x]] , tid[x]).rev();
                x = Fa[Top[x]];
            } else {
                R = get(1 , n , tid[Top[y]] , tid[y]) + R;
                y = Fa[Top[y]];
            }
        }
        if (dep[x] > dep[y])
            L = L + get(1 , n , tid[y] , tid[x]).rev() + R;
        else
            L = L + get(1 , n , tid[x] , tid[y]) + R;
        printf("%d\n" , L.s);
    }
}

int degree[N];

void bfs() {
    queue<int> que;
    memset(size, 0, sizeof(size));
    memset(heavy, 0, sizeof(heavy));
    memset(Fa, 0, sizeof(Fa));
    memset(dep, 0, sizeof(dep));
    memset(tid, 0, sizeof(tid));
    memset(Top, 0, sizeof(Top));
    for (int i = 1; i <= n; ++i)
        if (degree[i] == 1) {
            que.push(i);
        }
    while (!que.empty()) {
        int x = que.front(); que.pop();
        size[x]++;
        for (int k = pre[x]; k != -1; k = e[k].next)
            if (degree[e[k].x] > 1) {
                int y = e[k].x;
                Fa[x] = y;
                size[y] += size[x];
                if (heavy[y] == 0 || size[heavy[y]] < size[x])
                    heavy[y] = x;
                if (--degree[y] == 1) que.push(y);
            }
    }
    que.push(1);
    tid[1] = 1;
    Top[1] = 1;
    dep[1] = 1;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int S = tid[x];
        if (heavy[x] != 0) {
            Top[heavy[x]] = Top[x];
            tid[heavy[x]] = S + 1;
            S += size[heavy[x]];
            dep[heavy[x]] = dep[x] + 1;
            que.push(heavy[x]);
        }
        for (int k = pre[x]; k != -1; k = e[k].next) {
            int y = e[k].x;
            if (tid[y] > 0) continue;
            Top[y] = y;
            dep[y] = dep[x] + 1;
            tid[y] = S + 1;
            S += size[y];
            que.push(y);
        }
    }
    for (int i = 1; i <= n; ++i)
        A[tid[i]] = a[i];
}

int RD() {
    int ch;
    while (ch = getchar(), ch != '-' && !isdigit(ch));
    int k = 1, x = 0;
    if (ch == '-') k =-1;
    else x = ch - '0';
    while (ch = getchar(), isdigit(ch))
        x = x * 10 + ch - '0';
    return x * k;
}

void work() {
    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; ++ i) {
        //  scanf("%d" , &a[i]);
        a[i] = RD();
    }
    memset(pre , -1 , sizeof(pre));
    mcnt = 0;
    memset(degree, 0, sizeof(degree));
    ++degree[1];
    for (int i = 1 ; i < n ; ++ i) {
        int x = RD(), y = RD();
        // scanf("%d%d", &x , &y);
        ++degree[x];
        ++degree[y];
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
    }
    bfs();
    build(1 , n);
    while (m --) {
        int i , x , y , z;
        i = RD();
        x = RD();
        y = RD();
        z = RD();
// scanf("%d%d%d%d" , &i , &x , &y , &z);
        query(i , x , y , z);
    }
}

int main() {
    work();
    return 0;
}