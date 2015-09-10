int n , m;
int f[N] , match[N] , bel[N] , mark[N];
bool u[N] , InBlossom[N] , g[N][N];
int Q[N] , top , bot;

void BlossomContract(int x , int y) {
    memset(mark , 0 , sizeof(mark));
    memset(InBlossom , 0 , sizeof(InBlossom));
    #define pre f[match[i]]
    int lca , i;
    for (i = x ; i ; i = pre) i = bel[i] , mark[i] = 1;
    for (i = y ; i ; i = pre) {
        i = bel[i];
        if (mark[i]) {
            lca = i;
            break;
        }
    }
    for (i = x ; bel[i] != lca ; i = pre) {
        if (bel[pre] != lca) f[pre] = match[i];
        InBlossom[bel[i]] = 1;
        InBlossom[bel[match[i]]] = 1;
    }
    for (i = y ; bel[i] != lca ; i = pre) {
        if (bel[pre] != lca) f[pre] = match[i];
        InBlossom[bel[i]] = 1;
        InBlossom[bel[match[i]]] = 1;
    }
    #undef pre
    if (bel[x] != lca) f[x] = y;
    if (bel[y] != lca) f[y] = x;
    for (i = 1 ; i <= n ; ++ i)
        if (InBlossom[bel[i]]) {
            bel[i] = lca;
            if (!u[i]){
                Q[++ bot] = i;
                u[i] = 1;
            }
      }  
}

void Change(int z) {
    int x , y;
    while (z) {
        y = f[z] , x = match[y];
        match[y] = z , match[z] = y;
        z = x;
    }
}

void find(int st) {
    int i , x , y;
    memset(f , 0 , sizeof(f));
    memset(u , 0 , sizeof(u));
    for (i = 1 ; i <= n ; ++ i)
        bel[i] = i;
    top = 0 , bot = -1;
    Q[++ bot] = st , u[st] = 1;
    while (top <= bot) {
        x = Q[top ++];
        for (y = 1 ; y <= n ; ++ y)
            if (g[x][y] && bel[x] != bel[y] && match[x] != y)
                if (st == y || match[y] && f[match[y]])
                    BlossomContract(x , y);
                else if (!f[y]) {
                    f[y] = x;
                    if (match[y])
                        Q[++ bot] = match[y] , u[match[y]] = 1;
                    else {
                        Change(y);
                        return;
                    }
                }
    }
}

int main() {
    int i , j , x , y;
    scanf("%d%d" , &n ,&m);
    for (i = 0 ; i < m ; ++ i) {
        scanf("%d%d" , &x , &y);
        g[x][y] = g[y][x] = 1;
    }
    for (i = 1 ; i <= n ; ++ i)
        if (!match[i])
            find(i);
    int res = 0;
    for (i = 1 ; i <= n ; ++ i)
        res += !!match[i];
    printf("%d\n" , res / 2);
    for (i = 1 ; i <= n ; ++ i)
        printf("%d%c" , match[i] , " \n"[i == n]);
    return 0;
}
