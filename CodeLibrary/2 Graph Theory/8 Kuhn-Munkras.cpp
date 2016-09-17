int g[N][N] , lx[N] , ly[N] , match[N] , slack[N];
bool fx[N] , fy[N];
bool find(int x) {
    fx[x] = 1;
    for (int y = 0 ; y < n ; ++ y) {
        if (fy[y]) continue;
        if (lx[x] + ly[y] == g[x][y]) {
            fy[y] = 1;
            if (!~match[y] || find(match[y])) {
                match[y] = x;
                return 1;
            }
        } else {
            slack[y] = min(slack[y] , lx[x] + ly[y] - g[x][y]);
        }
    }
    return 0;
}
void update() {
    int delta = 1 << 30;
    for (int i = 0 ; i < n ; ++ i)
        if (!fy[i])
            delta = min(delta , slack[i]);
    for (int i = 0 ; i < n ; ++ i) {
        if (fx[i]) lx[i] -= delta;
        if (fy[i])
            ly[i] += delta;
        else
            slack[i] -= delta;
    }
}
int Kuhn_Munkras() {
    for (int i = 0 ; i < n ; ++ i) {
        match[i] = -1 , lx[i] = ly[i] = 0;
        for (int j = 0 ; j < n ; ++ j) {
            lx[i] = max(lx[i] , g[i][j]);
        }
    }
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j)
            slack[j] = 1 << 30;
        while (1) {
            for (int j = 0 ; j < n ; ++ j)
                fx[j] = fy[j] = 0;
            if (find(i))
                break;            
            update();
        }
    }
    int ans = 0;
    for (int i = 0 ; i < n ; ++ i)
        ans += g[match[i]][i];
    return ans;
}
