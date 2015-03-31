#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n , m , Q , pre[N] , mcnt;
struct edge {
    int x , w , next;
}e[N << 2];
int tmp[N];

void build(vector<int>& child , int x , int l , int r) {
    if (l == r) {
        int y = e[child[l]].x;
        e[mcnt] = (edge) {y , e[child[l]].w , tmp[x]} , tmp[x] = mcnt ++;
        e[mcnt] = (edge) {x , e[child[l]].w , tmp[y]} , tmp[y] = mcnt ++;
    } else {
        int mid = l + r >> 1;
        int rt = ++ n ;
        e[mcnt] = (edge) {x , 0 , tmp[n]} , tmp[n] = mcnt ++;
        e[mcnt] = (edge) {n , 0 , tmp[x]} , tmp[x] = mcnt ++;
        if (l <= mid) build(child , rt , l , mid);
        if (mid < r) build(child , rt , mid + 1 , r);
    }
}

void rebuild(int x , int fa) {
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            rebuild(y , x);
        }
    }
    vector<int> child;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (y != fa) {
            child.push_back(i);
        }
    }
    if (!child.empty())
        build(child , x , 0 , child.size() - 1);
}
int s[N] , size;
bool f[N];
pair<int , int> Find(int x , int fa , int cnt) {
    s[x] = 1;
    pair<int , int> res = make_pair(1 << 30 , -1);
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!f[i >> 1] && y != fa) {
            res = min(res , Find(y , x , cnt));
            s[x] += s[y];
            res = min(res , make_pair(max(s[y] , cnt - s[y]) , i));
        }
    }
    return res;
}
vector< pair<int , int> > b[N];
vector< int > D[N << 1];
vector< pair<int , int> > c[N << 1];
void Getdis(int x , int fa , int d , int id) {
    b[x].push_back(make_pair(id , d));
    D[id].push_back(d);
    ++ size;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        if (!f[i >> 1]) {
            int y = e[i].x;
            if (y != fa)
                Getdis(y , x , d + e[i].w , id);
        }
    }
}
pair<int , int> ans[N];

void divide(int x , int cnt) {
    if (cnt <= 1) return;

    int k = Find(x , 0 , cnt).second;
    f[k >> 1] = 1;

    size = 0;
    Getdis(e[k].x , 0 , 0 , k);
    sort(D[k].begin() , D[k].end());
    D[k].resize(unique(D[k].begin() , D[k].end()) - D[k].begin());
    c[k].resize(D[k].size());
    s[e[k].x] = size;

    size = 0 , k ^= 1;
    Getdis(e[k].x , 0 , 0 , k);
    sort(D[k].begin() , D[k].end());
    D[k].resize(unique(D[k].begin() , D[k].end()) - D[k].begin());
    c[k].resize(D[k].size());
    s[e[k].x] = size;

    divide(e[k].x , s[e[k].x]);
    divide(e[k ^ 1].x , s[e[k ^ 1].x]);
}

int main() {
    int i , j , k , x , y , z;
    scanf("%d",&n);
    memset(pre , -1 , sizeof(pre)) , mcnt = n * 6;
    for (i = 1 ; i < n ; ++ i) {
        scanf("%d%d%d",&x,&y,&z);
        e[mcnt] = (edge) {y , z , pre[x]} , pre[x] = mcnt ++;
        e[mcnt] = (edge) {x , z , pre[y]} , pre[y] = mcnt ++;
    }
    mcnt = 0;
    memset(tmp , -1 , sizeof(tmp));
    rebuild(1 , 0);
    memcpy(pre , tmp , sizeof(tmp));
    divide(1 , n);

    scanf("%d" , &m);
    for (int t = 1 ; t <= m ; ++ t) {
        scanf("%d",&i);
        if (i == 1) {
            scanf("%d%d%d",&x,&y,&z);
            ans[x] = make_pair(t , z);
            for (auto it : b[x]) {
                k = it.first ^ 1;
                j = upper_bound(D[k].begin() , D[k].end() , y - it.second - e[k].w) - D[k].begin() - 1;
                while (j >= 0) {
                    c[k][j] = max(c[k][j] , ans[x]);
                    j -= ~j & j + 1;
                }
            }
        } else {
            scanf("%d",&x);
            pair<int , int> res = ans[x];
            for (auto it : b[x]) {
                k = it.first;
                j = lower_bound(D[k].begin() , D[k].end() , it.second) - D[k].begin();
                while (j < c[k].size()) {
                    res = max(res , c[k][j]);
                    j += ~j & j + 1;
                }
            }
            printf("%d\n" , res.second);
        }
    }

    return 0;
}
