struct PalinTree {
    char str[N];
    int n;
    int u[N][26];
    int len[N] , f[N] , cnt[N];
    int nodecnt , root;
    void init() {
        scanf("%s" , str);
        n = strlen(str);
        nodecnt = 2;
        len[1] = -1 , len[2] = 0;
        f[1] = 0 , f[2] = 1;
        memset(u[1] , 0 , sizeof(u[1]));
        memset(u[2] , 0 , sizeof(u[2]));
        root = 1;
        for (int i = 0 ; i < n ; ++ i)
            extend(i , str[i] - 'a');
    }
    void extend(int i , int c) {
        int p = root;
        while (str[i - 1 - len[p]] != str[i])
            p = f[p];
        int& pp = u[p][c];
        if (!pp) {
            pp = ++ nodecnt;
            len[pp] = len[p] + 2;
            cnt[pp] = 0;
            memset(u[pp] , 0 , sizeof(u[pp]));
            int q = f[p];
            while (q && str[i - 1 - len[q]] != str[i])
                q = f[q];
            f[pp] = q ? u[q][c] : 2;
        }
        ++ cnt[pp];
        root = pp;
    }
}
