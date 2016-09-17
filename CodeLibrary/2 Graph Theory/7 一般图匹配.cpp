const int N = 505;

int S[N], Q[N], *Top = Q , idx;
int n, m;
int f[N] , pre[N] , nxt[N] , vis[N];
vector<int> e[N];
int getf(int x) {
    return x == f[x] ? x : f[x] = getf(f[x]);
}
int LCA(int x, int y) {
    idx ++;
    x = getf(x);
    y = getf(y);
    while (1) {
        if (x) {
            if (vis[x] == idx)
                return x;
            vis[x] = idx;
            x = getf(pre[nxt[x]]);
        }
        swap(x , y);
    }
}
void blossom(int x, int y, int l) {
    while (getf(x) != l) {
        pre[x] = y;
        if(S[nxt[x]] == 1) {
            *Top ++;
            S[*Top = nxt[x]] = 0;
        }
        f[x] = f[nxt[x]] = l;
        y = nxt[x];
        x = pre[y];
    }
}
void match(int x) {
    for (int i = 1 ; i <= n ; ++ i)
        f[i] = i;
    memset(S, -1, sizeof(S));
    memset(Q, 0, sizeof(Q));
    S[*(Top = Q + 1) = x] = 0;
    for(int *i = Q + 1 ; *i ; *i++) {
        for (auto &g : e[*i]) {
            if (S[g] == -1) {
                pre[g] = *i, S[g] = 1;
                if (!nxt[g]) {
                    for (int u = g, v = *i, lst ; v ; u = lst, v = pre[u])
                        lst = nxt[v], nxt[v] = u, nxt[u] = v;
                    return;
                }
                *Top++, S[*Top = nxt[g]] = 0;
            } else if(!S[g] && getf(g) != getf(*i)) {
                int l = LCA(g, *i);
                blossom(g, *i, l);
                blossom(*i, g, l);
            }
        }
    }
}
int main() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < m ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i = 1 ; i <= n ; ++ i) {
        if (!nxt[i]) {
            match(i);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) ans += nxt[i] != 0;
    printf("%d\n", ans / 2);
    for(int i = 1; i <= n; i++) printf("%d ", nxt[i]);
    putchar('\n');
    return 0;
}
