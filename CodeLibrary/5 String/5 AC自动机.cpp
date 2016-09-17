struct ACautomaton {
    int nodecnt;
    int u[N][26] , f[N];
    five val[N];
    int newnode() {
        val[nodecnt] = five();
        memset(u[nodecnt] , 0 , sizeof(u[nodecnt]));
        return nodecnt ++;
    }
    void clear() {
        nodecnt = 0;
        newnode();
    }
    void insert(char str[] , int id) {
        int x = 0;
        for (int i = 0 ; str[i] ; ++ i) {
            int c = str[i] - 'a';
            if (!u[x][c])
                u[x][c] = newnode();
            x = u[x][c];
        }
        val[x].insert(id);
    }
    int query(char *str) {
        int x = 0;
        for (int i = 0 ; str[i] ; ++ i) {
            int c = str[i] - 'a';
            x = u[x][c] , val[x].query();
        }
    }
    void getFail() {
        queue<int> Q;
        for (int i = 0 ; i < 26 ; ++ i)
            if (u[0][i]) {
                f[u[0][i]] = 0;
                Q.push(u[0][i]);
            }        
        while (!Q.empty()) {
            int x = Q.front() ; Q.pop();
            for (int i = 0 ; i < 26 ; ++ i) {
                int y = u[x][i];
                if (!y) {
                    u[x][i] = u[f[x]][i];
                } else {
                    Q.push(y);
                    f[y] = u[f[x]][i];
                    val[y].update(val[f[y]]);
                }
            }
        }
    }
}heap; 
