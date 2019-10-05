int pre[N] , mcnt , s , t;
struct arc {
    int x , f , next;
} e[M];
void addarc(int x ,int y ,int z) {
    e[mcnt] = (arc) {y , z , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 , pre[y]} , pre[y] = mcnt ++;
}
int d[N] , cur[N] , q[N];
bool bfs() {
    memset(d , -1 , sizeof(d));
    int top = 0 , bot = -1;
    q[++ bot] = t , d[t] = 1;
    while (top != bot + 1) {
        int x = q[top ++];
        for (int i = pre[x] ; ~i ;i = e[i].next) {
            int y = e[i].x;
            if (!~d[y] && e[i ^ 1].f) {
                d[y] = d[x] + 1 , q[++ bot] = y;
                if (y == s) return 1;
            }
        }
    }
    return 0;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == t || !flow) return flow;
    int sum = 0;
    for (int& i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x, u;
        if (d[x] == d[y] + 1 && (u = DFS(y , min(flow , e[i].f)))) {
            e[i].f -= u , e[i ^ 1].f += u;
            sum += u , flow -= u;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
int dinic() {
    int ans = 0;
    while (bfs()) {
        memcpy(cur , pre , sizeof(cur));
        ans += dfs(s);
    }
    return ans;
}
