int m , n;
bool f[N];
int prime[N] , tot;
int mu[N] , phi[N];
void init(int n) {
    int i , j , x;
    mu[1] = 1;
    for (i = 2 ; i <= n ; ++ i) {
        if (!f[i]) {
            prime[tot ++] = i ;
            phi[i] = i - 1 , h[i] = 1;
            mu[i] = -1;
        }
        for (j = 0 ; j < tot ; ++ j) {
            x = i * prime[j];
            if (x > n) break;
            f[x] = 1 ;
            if (i % prime[j] == 0) {
                phi[x] = phi[i] * prime[j];
                mu[x] = 0;
                break;
            } else {
                phi[x] = phi[i] * (prime[j] - 1) ;
                mu[x] = -mu[i];
            }
        }
    }
}
LL solve(int n , int m) {
    LL ans = 0;
    if (n > m) swap(n , m);
    for (int i = 1 , x ; i <= n ; i = x + 1) {
        x = min(n / (n / i) , m / (m / i));
        ans += (LL) (sum[x] - sum[i - 1]) * (n / i) * (m / i);
    }
    return ans;
}
