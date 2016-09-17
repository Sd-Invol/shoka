int root , last , nodecnt;
int u[N << 1][26] , val[N << 1] , f[N << 1];
inline int newnode(int _val) {
    ++ nodecnt;
    memset(u[nodecnt] , 0 , sizeof(u[nodecnt]));
    val[nodecnt] = _val , f[nodecnt] = 0;
    return nodecnt;
}
void extend(int c) {
    int p = last , np = newnode(val[p] + 1);
    while (p && u[p][c] == 0)
        u[p][c] = np , p = f[p];
    if (p == 0)
        f[np] = root;
    else {
        int q = u[p][c];
        if (val[p] + 1 == val[q]) {
            f[np] = q;
        } else {
            int nq = newnode(val[p] + 1);
            memcpy(u[nq] , u[q] , sizeof(u[q]));
            f[nq] = f[q];
            f[q] = f[np] = nq;
            while (p && u[p][c] == q)
                u[p][c] = nq , p = f[p];
        }
    }
    last = np;
}
void work() {
    nodecnt = 0;
    root = last = newnode(0);
}

