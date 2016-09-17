void decode(LL x , int *p , int *c , int &g) {
    for (int i = 0 ; i <= m ; ++ i) {
        c[i] = x & 1 , x >>= 1;
        p[i] = x & 15 , x >>= 4;
    }
    g = x , x >>= 2;
}
void encode(LL& x , int *p , int *c , int g) {
    x = 0; x <<= 2 , x |= g;
    for (int i = m ; i >= 0 ; -- i) {
        x <<= 4 , x |= p[i];
        x <<= 1 , x |= c[i];
    }
}
void normalize(int *p) {
    int cnt = 0;
    for (int i = 0 ; i <= m ; ++ i) {
        p[i] = -p[i];
    }
    for (int i = 0 ; i <= m ; ++ i) {
        if (p[i] < 0) {
            ++ cnt;
            for (int j = m ; j >= i ; -- j)
                if (p[j] == p[i])
                    p[j] = cnt;
        }
    }
}
void change(int *p , int x , int y) {
    for (int i = 0 ; i <= m ; ++ i)
        if (p[i] == x)
            p[i] = y;
}
void work() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%s" , s[i]);
    }
    for (int i = 0 ; i <= n * (m + 1) ; ++ i)
        C[i].clear() , pre[i].clear();
    int cur = 0 , nxt = 1;
    f[cur].clear();
    f[cur][0] = 1;
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < m ; ++ j) {
            f[nxt].clear();

            for (auto &it : f[cur]) {
                LL k = it.first;
                LL w = it.second;
                static int p[10] , c[10];
                int g;
                decode(k , p , c , g);
                int ng = g;
                if (i && j) {
                    int cnt = 0 , oth = 0;
                    for (int l = 0 ; l <= m ; ++ l) {
                        if (p[l] == p[j])
                            ++ cnt;
                        else if (c[l] == c[j])
                            ++ oth;
                    }
                    if (cnt == 1) {
                        if (oth) continue;
                        if (c[j] == 0) {
                            if (ng & 1)
                                continue;
                            else
                                ng |= 1;
                        } else {
                            if (ng & 2)
                                continue;
                            else
                                ng |= 2;
                        }
                    }
                }
                if (s[i][j] != '#' && (~ng & 1) && (!j || !i || c[j - 1] || c[j] || c[j + 1])) {
                    int nc = 10;
                    if (j && !c[j - 1])
                        change(p , p[j - 1] , nc);
                    if (i && !c[j + 1])
                        change(p , p[j + 1] , nc);
                    p[j] = nc , c[j] = 0;
                    normalize(p);
                    LL K;
                    encode(K , p , c , ng);
                    f[nxt][K] += w;
                    pre[nxt][K] = k;
                    C[nxt][K] = 0;
                }
                decode(k , p , c , g);                    
                if (s[i][j] != 'o' && (~ng & 2) && (!j || !i || !c[j - 1] || !c[j] || !c[j + 1])) {
                    int nc = 10;
                    if (j && c[j - 1])
                        change(p , p[j - 1] , nc);
                    if (i && c[j + 1])
                        change(p , p[j + 1] , nc);
                    p[j] = nc , c[j] = 1;
                    normalize(p);
                    LL K;
                    encode(K , p , c , ng);
                    f[nxt][K] += w;                    
                    pre[nxt][K] = k;
                    C[nxt][K] = 1;
                }
            }
            ++ cur , ++ nxt;
        }
        f[nxt].clear();
        for (auto &it : f[cur]) {
            LL k = it.first;
            LL w = it.second;
            static int p[10] , c[10];
            int g;
            decode(k , p , c , g);
            int ng = g;
            if (i) {
                int cnt = 0 , oth = 0;
                for (int l = 0 ; l <= m ; ++ l) {
                    if (p[l] == p[m])
                        ++ cnt;
                    else if (c[l] == c[m])
                        ++ oth;
                }
                if (cnt == 1) {
                    if (oth) continue;
                    if (c[m] == 0) {
                        if (ng & 1)
                            continue;
                        else
                            ng |= 1;
                    } else {
                        if (ng & 2)
                            continue;
                        else
                            ng |= 2;
                    }
                }
            }
            for (int l = m ; l > 0 ; -- l) {
                p[l] = p[l - 1];
                c[l] = c[l - 1];
            }
            p[0] = c[0] = 0;
            normalize(p);
            LL K;
            encode(K , p , c , ng);
            f[nxt][K] += w;            
            pre[nxt][K] = k;
        }
        ++ cur , ++ nxt;
    }
    LL ans = 0 , K = -1;
    for (auto &it : f[cur]) {
        LL k = it.first;
        LL w = it.second;
        static int p[10] , c[10];
        int g;
        decode(k , p , c , g);
        int cnt = 0;
        for (int i = 0 ; i <= m ; ++ i) {
            if (p[i] > 0) {
                ++ cnt;
                for (int j = m ; j >= i ; -- j)
                    if (p[j] == p[i])
                        p[j] = -p[j];
            }
        }
        if (cnt <= 2) {
            ans += w;
            K = k;
        }
    }
    printf("%lld\n" , ans);
}
/****************************************************/
inline int getpos(int x , int k) {
    return x >> k + k & 3;
}
inline int setpos(int x , int k , int v) {
    return (x & ~(3 << k + k)) | (v << k + k);
}

void work() {
    int res = -1 << 30;
    for (int i = 0 ; i < n ; ++ i)
        for (int j = 0 ; j < m ; ++ j) {
            scanf("%d" , &a[i][j]);
            res = max(res , a[i][j]);
        }
    int cur = 0 , nxt = 1;
    f[cur].clear();
    f[cur][0] = 0;
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < m ; ++ j) {
            f[nxt].clear();

            for (int it = 0 ; it < f[cur].mcnt ; ++ it) {
                int k = f[cur].e[it].key;
                int w = f[cur].e[it].val;
                int L = getpos(k , j);
                int U = getpos(k , j + 1);
                int num = getpos(k , m + 1);
                //printf("%d %d %d %d : %d\n" , i , j , k , num , w);
                if (!L && !U)
                    f[nxt][k] = max(f[nxt][k] , w);
                w += a[i][j];
                if (!L && !U) {
                    if (j + 1 < m) {
                        int K = setpos(k , j , 1);
                        K = setpos(K , j + 1 , 2);
                        f[nxt][K] = max(f[nxt][K] , w);
                    }                    
                    if (num < 2) {
                        int K = setpos(k , m + 1 , num + 1);
                        K = setpos(K , j , 3);
                        f[nxt][K] = max(f[nxt][K] , w);
                        if (j + 1 < m) {
                            int K = setpos(k , m + 1 , num + 1);
                            K = setpos(K , j + 1 , 3);
                            f[nxt][K] = max(f[nxt][K] , w);
                        }
                    }
                } else {
                    static int match[N];
                    static int S[N];
                    int top = 0;
                    for (int l = 0 ; l <= m ; ++ l) {
                        int x = getpos(k , l);
                        if (x == 1)
                            S[top ++] = l;
                        if (x == 2) {
                            -- top;
                            match[S[top]] = l;
                            match[l] = S[top];
                        }
                    }
                    if (L && !U) {
                        if (num < 2) {
                            int K = setpos(k , m + 1 , num + 1);
                            K = setpos(K , j , 0);
                            if (L != 3) K = setpos(K , match[j] , 3);
                            f[nxt][K] = max(f[nxt][K] , w);                            
                        }
                        if (j + 1 < m) {
                            int K = setpos(k , j , U);
                            K = setpos(K , j + 1 , L);
                            f[nxt][K] = max(f[nxt][K] , w);
                        }
                        f[nxt][k] = max(f[nxt][k] , w);    
                    }
                    if (!L && U) {
                        if (num < 2) {
                            int K = setpos(k , m + 1 , num + 1);
                            K = setpos(K , j + 1 , 0);
                            if (U != 3) K = setpos(K , match[j + 1] , 3);
                            f[nxt][K] = max(f[nxt][K] , w);                            
                        }
                        if (j + 1 < m) {
                            f[nxt][k] = max(f[nxt][k] , w);    
                        }
                        int K = setpos(k , j , U);
                        K = setpos(K , j + 1 , L);
                        f[nxt][K] = max(f[nxt][K] , w);                        
                    }
                    if (L && U) {
                        int K = setpos(k , j , 0);
                        K = setpos(K , j + 1 , 0);
                        if (L == 3 || U == 3) {
                            if (L != 3)
                                K = setpos(K , match[j] , 3);
                            if (U != 3)
                                K = setpos(K , match[j + 1] , 3);
                            f[nxt][K] = max(f[nxt][K] , w);
                        } else {
                            if (L == U) {
                                if (L == 1 && U == 1) {
                                    K = setpos(K , match[j + 1] , 1);
                                }
                                if (L == 2 && U == 2) {
                                    K = setpos(K , match[j] , 2);
                                }
                                f[nxt][K] = max(f[nxt][K] , w);                                
                            } else if (L == 2 && U == 1) {
                                f[nxt][K] = max(f[nxt][K] , w);                        
                            }
                        }
                    }
                }
            }
            swap(cur , nxt);
        }
        f[nxt].clear();
        for (int it = 0 ; it < f[cur].mcnt ; ++ it) {
            int k = f[cur].e[it].key;
            int w = f[cur].e[it].val;
            int num = getpos(k , m + 1);
            k = setpos(k , m + 1 , 0) << 2;
            f[nxt][setpos(k , m + 1 , num)] = w;
        }
        swap(cur , nxt);
    }
    res = max(res , f[cur][2 << m + m + 2]);
    cout << res << endl;        
}
