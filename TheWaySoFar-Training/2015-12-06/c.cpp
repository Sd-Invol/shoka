#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 50005; 

int n , m , pre[N] , mcnt;
struct edge {
    int x , next;
}e[N << 2];
int K;
vector<int> con[N];
int dfn[N] , low[N] , ncnt , size[N];
stack<int> S;
int tmp[N];
int f[N] , s[N] , loop;
int getf(int x) {
    return f[x] == x ? x : f[x] = getf(f[x]);
}
LL res;
void dfs(int x , int fa) {
    size[x] = 1;
    dfn[x] = low[x] = ++ ncnt;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (!dfn[y]) {
            S.push(i);
            dfs(y , i ^ 1);
            size[x] += size[y];
            low[x] = min(low[x] , low[y]);
            if (low[y] > dfn[x]) {
                res += (LL)size[y] * (n - size[y]) - 1;
            }
            if (low[y] >= dfn[x]) {
                ++ K;
                int j;
                do {
                    j = S.top() , S.pop();
                    if (tmp[e[j].x] != K) {
                        con[K].push_back(e[j].x);
                        tmp[e[j].x] = K;
                    }
                    if (tmp[e[j ^ 1].x] != K) {                        
                        con[K].push_back(e[j ^ 1].x);
                        tmp[e[j ^ 1].x] = K;
                    }
                } while (j != i);
                if (con[K].size() == 2) {
                    s[getf(con[K][1])] += s[getf(con[K][0])];
                    f[getf(con[K][0])] = getf(con[K][1]);
                } else
                    loop += con[K].size();
            }
        } else if (i != fa && dfn[y] < dfn[x])
            S.push(i) , low[x] = min(low[x] , dfn[y]);
    }
}

int main() {
    scanf("%d%d" , &n , &m);
    memset(pre , -1 , sizeof(pre));
    for (int i = 0 ; i < m ; ++ i) {
        int k , x , y;
        scanf("%d%d" , &k , &x);
        for (int j = 1 ; j < k ; ++ j) {
            scanf("%d" , &y);
            e[mcnt] = (edge) {y , pre[x]} , pre[x] = mcnt ++;
            e[mcnt] = (edge) {x , pre[y]} , pre[y] = mcnt ++;
            x = y;
        }
    }
    for (int i = 1 ; i <= n ; ++ i) {
        f[i] = i;
        s[i] = 1;
    }
    dfs(1 , -1);
    LL cnt = 0;
    for (int i = 1 ; i <= n ; ++ i)
        if (getf(i) == i) {
            cnt += (LL)s[i] * (s[i] - 1) / 2;
        }
    for (int i = 1 ; i <= K ; ++ i) {
        int R = con[i].size();
        if (R > 2) {
            LL now = cnt;
            int block = 0;
            for (int j = 0 ; j < R ; ++ j) {
                int x = getf(con[i][j]);
                now -= (LL)s[x] * (s[x] - 1) / 2;
                block += s[x];
            }
           now += (LL)block * (block - 1) / 2;
           res += (now - (mcnt / 2) + loop - R) * R;
        }
    }    
    printf("%lld\n" , res);
    return 0;
}
