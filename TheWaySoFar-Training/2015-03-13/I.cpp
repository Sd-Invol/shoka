#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
const int M = 100005;
const int Node = 4000005;
int n , m , Q;
struct edge {
    int x , y , w;
    bool operator < (const edge& R) const {
        return w < R.w;
    }
}e[M];
vector< pair<int , int> > E[N]; 
pair<int , int> mx[N];
int F[N];

bool dfs(int x , int fa , int anc) {
    if (x == anc) return 1;
    for (auto it : E[x]) {
        int y = it.first , z = it.second;
        if (y != fa) {
            mx[y] = max(mx[x] , make_pair(z , y));
            F[y] = x;
            if (dfs(y , x , anc))
                return 1;
        }
    }
    return 0;
}
int cut(int x , int y) {
    for (auto it = E[x].begin() ; it != E[x].end() ; ++ it) {
        if (it -> first == y) {
            swap(*it , E[x].back());
            E[x].pop_back();
            break;
        }
    }
    swap(x , y);
    for (auto it = E[x].begin() ; it != E[x].end() ; ++ it) {
        if (it -> first == y) {
            int tmp = it -> second;
            swap(*it , E[x].back());
            E[x].pop_back();
            return tmp;
        }
    }    
}
int w[M];

int cnt;
int u[Node][2] , root[M];
LL s[Node];

void insert(int& p , int q , int l , int r , int x , int w) {
    if (!p)
        p = ++ cnt , s[p] = s[q] , u[p][0] = u[p][1] = 0;
    s[p] += w; if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid)
        insert(u[p][0] , u[q][0] , l , mid , x , w);
    else
        insert(u[p][1] , u[q][1] , mid + 1 , r , x , w);
}
void rebuild(int p , int q) {
    if (u[p][0]) rebuild(u[p][0] , u[q][0]); else u[p][0] = u[q][0];
    if (u[p][1]) rebuild(u[p][1] , u[q][1]); else u[p][1] = u[q][1];
}

LL res;
void query(int p , int l , int r , int top , int bot) {
    if (!p) return;
    if (top <= l && r <= bot) {
        res += s[p];  return;
    } int mid = l + r >> 1;
    if (top <= mid) query(u[p][0] , l , mid , top , bot);
    if (bot > mid) query(u[p][1] , mid + 1 , r , top , bot);
}


void work () {
    int i , j , x , y , z;
    scanf("%d%d",&n,&m);
    for (i = 0 ; i < m ; ++ i) 
        scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);        
    sort(e , e + m);
    for (i = 0 ; i < m ; ++ i)
        w[i] = e[i].w , e[i].w = i;
    for (i = 1 ; i <= n ; ++ i)
        E[i].clear();
    root[m] = 0 , cnt = 0;
    for (i = m - 1 ; i >= 0 ; -- i) {
        root[i] = 0;
        x = e[i].x , y = e[i].y;
        mx[x] = make_pair(0 , x);
        if (dfs(x , x , y)) {
            j = cut(mx[y].second , F[mx[y].second]);
            insert(root[i] , root[i + 1] , 0 , m - 1 , j , -w[j]);
        }
        E[x].push_back(make_pair(y , e[i].w));
        E[y].push_back(make_pair(x , e[i].w));
        insert(root[i] , root[i + 1] , 0 , m - 1 , i , w[i]);
        rebuild(root[i] , root[i + 1]);
    }
    scanf("%d" , &Q);
    LL L , R; res = 0;
    while (Q --) {
        scanf("%lld%lld",&L,&R);
        i = L - res , j = R - res;
        //printf("%d %d\n" , i , j);
        x = lower_bound(w , w + m , i) - w;
        y = upper_bound(w , w + m , j) - w - 1;
        //printf("%d %d\n" , x , y);
        res = 0;
        query(root[x] , 0 , m - 1 , x , y);
        printf("%lld\n" , res);
    }
    //for (i = 0 ; i < m ; ++ i)
    //    cout << s[root[i]] << endl;
}

int main () {
    int _;
    scanf("%d",&_);
    while (_ --)
        work();
    return 0;
}
