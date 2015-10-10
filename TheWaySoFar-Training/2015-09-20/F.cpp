#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <ctime>
using namespace std;
typedef long long LL;
const int N = 100005;
int n , m;

int root[N];
const int M = 2000000;
int c[M][2] , val[M] , cnt;
int newnode(int q = 0) {
    ++ cnt;
    c[cnt][0] = c[cnt][1] = 0;
    val[cnt] = val[q];
    return cnt;
}
void insert(int &p , int q , int l , int r , int x , int w) {
    if (!p) p = newnode(q);
    val[p] = max(val[p] , w);
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) {
        c[p][1] = c[q][1];
        insert(c[p][0] , c[q][0] , l , mid , x , w);
    } else {
        c[p][0] = c[q][0];
        insert(c[p][1] , c[q][1] , mid + 1 , r , x , w);
    }
}
int res = 0;
void get(int p , int l , int r , int top , int bot) {
    if (!p) return;
    if (top <= l && r <= bot) {
        res = max(res , val[p]);
        return;
    }
    int mid = l + r >> 1;
    if (top <= mid) get(c[p][0] , l , mid , top , bot);
    if (bot > mid) get(c[p][1] , mid + 1 , r , top , bot);
}
struct Tree {
    int n;
    int pre[N] , mcnt;
    struct edge {
        int x , next;
    }e[N];
    void addedge(int x , int y) {
        e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
    }

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
        tid[x] = ++ ncnt , Top[x] = anc;
        if (heavy[x])
            ConnectHE(heavy[x] , anc);
        for (int i = pre[x] ; ~i ; i = e[i].next)
            if (e[i].x != Fa[x] && e[i].x != heavy[x])
                ConnectHE(e[i].x , e[i].x);
    }
}A , B;

void dfs(int x , int fa) {
    root[x] = 0;
    insert(root[x] , root[fa] , 1 , n , B.tid[x] , x);
    for (int i = A.pre[x] ; ~i ; i = A.e[i].next) {
        int y = A.e[i].x;
        if (y != fa) {
            dfs(y , x);
        }
    }
}

void work() {
    memset(A.pre , -1 , sizeof(A.pre));
    A.mcnt = 0;
    for (int i = 2 ; i <= n ; ++ i) {
        int x;
        scanf("%d" , &x);
        A.addedge(x , i);
    }
    memset(B.pre , -1 , sizeof(B.pre));
    B.mcnt = 0;
    for (int i = 2 ; i <= n ; ++ i) {
        int x;
        scanf("%d" , &x);
        B.addedge(x , i);
    }
    A.ncnt = B.ncnt = 0;
    B.FindHE(1 , 0 , 0);
    B.ConnectHE(1 , 1);
    A.FindHE(1 , 0 , 0);
    cnt = 0;
    dfs(1 , 0);
    int pre = 0 ;
    while (m --) {
        int x , y , z;
        scanf("%d%d" , &x , &y);
        x += pre , y += pre;
        x %= n , x ++;
        y %= n , y ++;
        res = 0; z = y;
        while (y) {
            get(root[x] , 1 , n , B.tid[B.Top[y]] , B.tid[y]);
            y = B.Fa[B.Top[y]];
        }
        // cout << z << endl;
        printf("%d %d %d\n" , res , A.dep[x] - A.dep[res] + 1 , B.dep[z] - B.dep[res] + 1);
        pre = res;
    }

}

int main() {
    while (~scanf("%d%d" , &n , &m))
        work();
    return 0;
}
