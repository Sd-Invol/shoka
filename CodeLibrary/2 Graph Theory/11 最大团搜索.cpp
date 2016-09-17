int n , mc[N] , list[N][N] , len[N] , ans;
bool g[N][N] , found;

void dfs(int size) {
    int i , j , k;
    if (!len[size]) {
        if (size > ans)
            ans = size , found = 1;
        return;
    }
    for (k = 0 ; k < len[size] && !found ; ++ k) {
        if (size + len[size] - k <= ans)
            break;
        i = list[size][k];
        if (size + mc[i] <= ans)
            break;
        for (j = k + 1 , len[size + 1] = 0 ; j < len[size] ; ++ j)
            if (g[i][list[size][j]])
                list[size + 1][len[size + 1] ++] = list[size][j];
        dfs(size + 1);
    }
}
void max_cluster() {
    int i , j;
    mc[n] = ans = 1;
    for (i = n - 1 ; i ; -- i) {
        found = 0 , len[1] = 0;
        for (j = i + 1 ; j <= n ; ++ j)
            if (g[i][j])
                list[1][len[1] ++] = j;
        dfs(1);
        mc[i] = ans;
    }
}
void work() {
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= n ; ++ j)
            scanf("%d",&g[i][j]);
    max_cluster();
    cout << ans << endl;
}
/**************************************/
// 极大团枚举 O(3^{n/3})
int trail_zero(ULL s) {
    return s ? __builtin_ctzll(s) : 64;
}
bool BronKerbosch(const vector<ULL> &g, ULL cur, ULL allow, ULL forbid) {
    if (allow == 0 && forbid == 0) {
        for (int i = 0; i < n; ++ i) {
            printf("%d" , (int) (cur >> i & 1));
        }
        puts("");
        return false;
    }
    if (allow == 0) return false;
    int pivot = trail_zero(allow | forbid);
    ULL z = allow & ~g[pivot];
    for (size_t u = trail_zero(z); u < g.size(); u += trail_zero(z >> (u + 1)) + 1) {
        if (BronKerbosch(g, cur | (1ULL << u), allow & g[u], forbid & g[u])) return true;
        allow ^= 1ULL << u; forbid |= 1ULL << u;
    }
    return false;
}
//BronKerbosch(g , 0 , (1ULL << n) - 1 , 0);
