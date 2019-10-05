int n, m, source, sink, pre[N], mcnt, cur[N], d[N], h[N];
bool f[N];
int maxflow, ans;
struct arc {
    int x, f, c, next;
} e[M];

void addarc(int x , int y , int z , int c) {
    e[mcnt] = (arc) {y , z , c , pre[x]} , pre[x] = mcnt ++;
    e[mcnt] = (arc) {x , 0 ,-c , pre[y]} , pre[y] = mcnt ++;
}

bool Dijkstra() {
    priority_queue< pair<int , int> > pq;
    memset(d , 0x3f , sizeof(d));
    pq.push(make_pair(-(d[sink] = 0) , sink));
    while (!pq.empty()) {
        int x = pq.top().second;
        int w = -pq.top().first; 
        pq.pop();
        if (w > d[x]) continue;
        for (int i = pre[x] ; ~i ; i = e[i].next) {
            int y = e[i].x, z = e[i ^ 1].c + h[x] - h[y];
            if (e[i ^ 1].f && d[x] + z < d[y]) {
                d[y] = d[x] + z;
                pq.push(make_pair(-d[y] , y));
            }
        }
    }
    return d[source] != 0x3f3f3f3f;
}
int dfs(int x , int flow = 1 << 30) {
    if (x == sink) {
        maxflow += flow;
        ans += h[source] * flow;
        return flow;
    } 
    f[x] = 1;
    int sum = 0;
    for (int &i = cur[x] ; ~i ; i = e[i].next) {
        int y = e[i].x;
        if (e[i].f && !f[y] && h[x] == e[i].c + h[y]) {
            int u = dfs(y , min(flow , e[i].f));
            e[i].f -= u , e[i ^ 1].f += u;
            flow -= u , sum += u;
            if (!flow) break;
        }
    }
    f[x] = 0;
    return sum;
}
void MincostMaxflow() {
    // memset(h , 0 , sizeof(h));
    queue<int> Q;
    memset(f , 0 , sizeof(f));
    memset(h , 0x3f , sizeof(h));
    h[sink] = 0 , f[sink] = 1 , Q.push(sink);
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
        for (int i = 0 ; i <= n ; ++ i) {
            if (d[i] != 0x3f3f3f3f) {
                h[i] += d[i];
            }
        }
        do {
            fill(f , f + n + 1, 0);
            copy(pre , pre + n + 1 , cur);
        } while (dfs(source));
    } 
}