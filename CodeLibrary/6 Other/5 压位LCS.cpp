typedef unsigned long long LL;
const int N = 1005;
const int B = 64;
const int M = (N + B - 1) / B + 5;
int n , m;
char s[N] , t[N];
LL c[26][M];
LL f[2][M] , X[M];

void work() {
    n = strlen(s);
    m = strlen(t);
    memset(c , 0 , sizeof(c));
    for (int i = 0 ; i < n ; ++ i)
        c[s[i] - 'a'][i >> 6] |= 1ULL << (i & 63);
    int L = (n + B - 1) / B;
    int cur = 0 , nxt = 1;
    memset(f , 0 , sizeof(f));
    for (int i = 0 ; i < m ; ++ i) {
        int id = t[i] - 'a';
        for (int j = 0 ; j < L ; ++ j)
            X[j] = f[cur][j] | c[id][j];
        for (int j = 0 , x = 1 ; j < L ; ++ j) {
            int y = f[cur][j] >> 63 & 1;
            f[cur][j] <<= 1 , f[cur][j] |= x;
            x = y;
        }
        memcpy(f[nxt] , X , sizeof(X));
        for (int j = 0 , x = 0; j < L ; ++ j) {
            if (f[nxt][j] < x + f[cur][j]) {
                f[nxt][j] -= x + f[cur][j];    
                x = 1;
            } else {
                f[nxt][j] -= x + f[cur][j];
                x = 0;
            }            
            f[nxt][j] ^= X[j];
            f[nxt][j] &= X[j];
        }        
        swap(cur , nxt);
    }
    int ans = 0;
    for (int i = 0 ; i < n ; ++ i)
        if (f[cur][i >> 6] >> (i & 63) & 1)
            ++ ans;
    printf("%d\n" , ans);
}
