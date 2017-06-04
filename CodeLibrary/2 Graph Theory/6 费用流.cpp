int S , T , pre[N] , mcnt;
struct arc {
    int x , f , c , next;
} e[M];

void addarc(int x , int y , int z , int c) {
    e[mcnt] = (arc) {y , z , c , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 ,-c , pre[y]} , pre[y] = mcnt ++;
}

int maxflow , ans , d[N] , h[N];
bool f[N];
bool Dijkstra() {
    priority_queue< pair<int , int> > Q;
    memset(d , 0x3f , sizeof(d));
    d[T] = 0; Q.push(make_pair(-d[T] , T));
    while (!Q.empty()) {
        int x = Q.top().second , w = -Q.top().first; Q.pop();
        if (w > d[x]) continue;
        if (x == S) {
            for (int i = 0 ; i <= T ; ++ i) {
                h[i] = min(h[i] + d[i] , INF);
            }
            return 1;
        }
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x , z = e[i ^ 1].c + h[x] - h[y];
            if (e[i ^ 1].f && d[x] + z < d[y]) {
                d[y] = d[x] + z;
                Q.push(make_pair(-d[y] , y));
            }
        }
    }
    return 0;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == T) {
        maxflow += flow , ans += h[S] * flow;
        return flow;
    } f[x] = 1; int sum = 0 , u;
    for (int i = pre[x] ; ~i ; i = e[i].next) {
        int y = e[i].x , u;
        if (e[i].f && !f[y] && h[x] == e[i].c + h[y]) {
            u = dfs(y , min(flow , e[i].f));
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , sum += u;
            if (!flow) break;
        }
    }
    return sum;
}
void MincostMaxflow() {
    //memset(h , 0 , sizeof(h));
    queue<int> Q;// 无负权边可选
    memset(f , 0 , sizeof(f));
    memset(h , 0x3f , sizeof(h));
    h[T] = 0 , f[T] = 1 , Q.push(T);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop() , f[x] = 0;
        for (int i = pre[x] ; ~i ; i = e[i].next){
            int y = e[i].x , z = e[i ^ 1].c;
            if (e[i ^ 1].f && h[y] > h[x] + z){
                h[y] = h[x] + z;
                if (!f[y]) {
                    Q.push(y);
                    f[y] = 1;
                }
            }
        }
    }
    maxflow = 0 , ans = 0;
    while (Dijkstra()) {
        do {
            memset(f , 0 , sizeof(f));
        } while (dfs(S));
    } // while (Dijkstra());
}
