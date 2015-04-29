#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;

int n , m , K , D;
int L[N] , R[N] , ncnt;
struct Trie {
    int cnt;
    int u[N][26];
    int insert(char *s) {
        int x = 1;
        for (int i = 0 ; s[i] ; ++ i) {
            int c = s[i] - 'a';
            if (!u[x][c])
                u[x][c] = ++ cnt;
            x = u[x][c];
        }
        return x;
    }
    void dfs(int x) {
        L[x] = ++ ncnt;
        for (int i = 0 ; i < 26 ; ++ i)
            if (u[x][i])
                dfs(u[x][i]);
        R[x] = ncnt;
    }
}T[3];
char str[N];
int a[N][3] , f[N][3];
int q[N][3] , res[N];
pair<int , int> w[N][3];
struct opt {
    int x , id;
    bool type;
    bool operator < (const opt& R) const {
        return make_pair(x , type) < make_pair(R.x , R.type);
    }
}V[N + N] , W[N + N];
int c[N];
void solve(int L , int R) {
    if (L >= R) return;
    int mid = L + R >> 1;
    solve(L , mid);
    solve(mid + 1 , R);

    int wcnt = 0;
    for (int i = L ; i <= mid ; ++ i)
        if (!V[i].type)
            W[wcnt ++] = (opt) {a[V[i].id][1] , V[i].id , 0};
    for (int i = mid + 1 ; i <= R ; ++ i)
        if (V[i].type) {
            W[wcnt ++] = (opt) {w[abs(V[i].id)][1].first - 1 , -V[i].id , 1};
            W[wcnt ++] = (opt) {w[abs(V[i].id)][1].second , V[i].id , 1};
        }
    sort(W , W + wcnt);

    for (int i = 0 ; i < wcnt ; ++ i) {
        if (!W[i].type) {
            for (int j = a[W[i].id][2] ; j <= D ; j += j & -j)
                ++ c[j];
        } else {
            int &ret = res[abs(W[i].id)]; 
            if (W[i].id > 0) {
                for (int j = w[W[i].id][2].second ; j > 0 ; j -= j & -j)
                    ret += c[j];
                for (int j = w[W[i].id][2].first - 1 ; j > 0 ; j -= j & -j)
                    ret -= c[j];                
            } else {
                for (int j = w[-W[i].id][2].second ; j > 0 ; j -= j & -j)
                    ret -= c[j];
                for (int j = w[-W[i].id][2].first - 1 ; j > 0 ; j -= j & -j)
                    ret += c[j];                            
            }
        }
    }
    for (int i = 0 ; i < wcnt ; ++ i) {
        if (!W[i].type) {
            for (int j = a[W[i].id][2] ; j <= D ; j += j & -j)
                -- c[j];
        }
    }
}


int main() {
    int i , j , k ,  x , y , z;
    scanf("%d%d",&n,&K);
    T[0].cnt = T[1].cnt = T[2].cnt = 1;
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 0 ; j < K ; ++ j) {
            scanf("%s" , str);
            a[i][j] = T[j].insert(str);
        }
        for ( ; j < 3 ; ++ j) a[i][j] = 1;
    }
    scanf("%d" , &m);
    int Q[3] = {1 , 1 , 1};
    for (i = 1 ; i <= m ; ++ i) {
        scanf("%d%s"  ,&j , str);
        -- j;
        if (*str == '-') {
            Q[j] = f[Q[j]][j];
        } else {
            scanf("%s" , str);
            int &node = T[j].u[Q[j]][*str - 'a'];
            if (!node)
                node = ++ T[j].cnt;
            f[node][j] = Q[j] , Q[j] = node;
        }
        memcpy(q[i] , Q , sizeof(Q));
    }
    D = T[2].cnt;
    for (j = 0 ; j < 3 ; ++ j) {
        ncnt = 0;
        T[j].dfs(1);
        for (i = 1 ; i <= n ; ++ i)
            a[i][j] = L[a[i][j]];
        for (i = 1 ; i <= m ; ++ i)
            w[i][j] = make_pair(L[q[i][j]] , R[q[i][j]]);     
    }
    int vcnt = 0;
    for (i = 1 ; i <= n ; ++ i)
        V[vcnt ++] = (opt) {a[i][0] , i , 0};
    for (i = 1 ; i <= m ; ++ i) {
        V[vcnt ++] = (opt) {w[i][0].first - 1 , -i , 1};
        V[vcnt ++] = (opt) {w[i][0].second , i , 1};
    }
    sort(V , V + vcnt);
    solve(0 , vcnt - 1);
    for (i = 1 ; i <= m ; ++ i)
        printf("%d\n" , res[i]);
    return 0;
}
