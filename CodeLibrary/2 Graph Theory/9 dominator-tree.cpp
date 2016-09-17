int n , m;
struct edge {
    int x , next;
} e[N << 5];
int mcnt;
int pre[N] , bre[N] , tree[N];
int mstamp , mvis[N];
int *prec, *succ;
vector<int> mord;
vector<int> buf[N];
int buf2[N];
int num[N] , fs[N], mins[N] , fa[N] , dom[N], sem[N];;
void dfs(int u) {
    mvis[u] = mstamp;
    num[u] = mord.size();
    mord.push_back(u);
    for (int i = succ[u] ; ~i ; i = e[i].next) {
        int v = e[i].x;
        if (mvis[v] != mstamp) {
            fa[v] = u;
            dfs(v);
        }
    }
}
int find(int u) {
    if (u != fs[u]) {
        int v = fs[u];
        fs[u] = find(fs[u]);
        if (mins[v] != -1 && num[sem[mins[v]]] < num[sem[mins[u]]]) {
            mins[u] = mins[v];
        }
    }
    return fs[u];
}
void merge(int u, int v) {
    fs[u] = v;
}
void mark(int source) { // prec = bre, succ = pre;
    mord.clear();
    ++mstamp;
    dfs(source);
    for (int i = 0; i < (int)mord.size(); ++i) {
        int u = mord[i];
        fs[u] = u;
        mins[u] = -1;
        buf2[u] = -1;
    }
    for (int i = (int)mord.size() - 1; i > 0; --i) {
        int u = mord[i], p = fa[u];
        sem[u] = p;
        for (int j = prec[u]; ~j ; j = e[j].next) {
            int v = e[j].x;
            if (mvis[v] != mstamp)
                continue;
            if (num[v] > num[u]) {
                find(v);
                v = sem[mins[v]];
            }
            if (num[v] < num[sem[u]]) {
                sem[u] = v;
            }
        }
        buf[sem[u]].push_back(u);
        mins[u] = u;
        merge(u, p);
        while (buf[p].size()) {
            int v = buf[p].back();
            buf[p].pop_back();
            find(v);
            if (sem[v] == sem[mins[v]]) {
                dom[v] = sem[v];
            } else {
                buf2[v] = mins[v];
            }
        }
    }
    dom[mord[0]] = mord[0];
    for (int i = 0; i < (int)mord.size(); ++i) {
        int u = mord[i];
        if (~buf2[u]) {
            dom[u] = dom[buf2[u]];
        }
        if (u != source) {
            //printf("%d dom %d\n" , dom[u] , u);
            //e[mcnt] = (edge) {u , tree[dom[u]]};
            //tree[dom[u]] = mcnt ++;
            res[dom[u]] = 1;
        }
    }
}
