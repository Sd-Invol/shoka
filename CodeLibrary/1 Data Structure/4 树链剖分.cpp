int size[N] , heavy[N] , tid[N] , Top[N] , ncnt , dep[N] , Fa[N];
void FindHE(int x , int fa , int Dep) {
    heavy[x] = 0 , size[x] = 1 , dep[x] = Dep , Fa[x] = fa;
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (e[i].x != fa) {
            int y = e[i].x;
            FindHE(y , x , Dep + 1);
            size[x] += size[y];
            if (!heavy[x] || size[y] > size[heavy[x]])
                heavy[x] = y;
        }
}
void ConnectHE(int x , int anc) {
    tid[x] = ++ ncnt , Top[x] = anc;
    update(1 , n , ncnt , a[x]);
    if (heavy[x])
        ConnectHE(heavy[x] , anc);
    for (int i = pre[x] ; ~i ; i = e[i].next)
        if (e[i].x != Fa[x] && e[i].x != heavy[x])
            ConnectHE(e[i].x , e[i].x);
}
int query(int x , int y) {
    int ans = -1 << 30;
    while (Top[x] != Top[y]) {
        if (dep[Top[x]] < dep[Top[y]])
            swap(x , y);
        ans = max(ans , query(1 , n , tid[Top[x]] , tid[x]));
        x = Fa[Top[x]];
    }
    if (dep[x] > dep[y]) swap(x , y);
    ans = max(ans , query(1 , n , tid[x] , tid[y]));
    return ans; //如果权在边上就不考虑左边的点了
}
int LCA(int x , int y) {
    while (Top[x] != Top[y]) {
        if (dep[Top[x]] < dep[Top[y]])
            swap(x , y);
        x = Fa[Top[x]];
    }
    if (dep[x] > dep[y]) swap(x , y);
    return x;
}
