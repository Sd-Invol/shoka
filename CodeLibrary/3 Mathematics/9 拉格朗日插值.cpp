for (int i = 0 ; i < n ; ++ i)
    val[i] = cal(i);
for (int i = 0 ; i < n ; ++ i) {
    int cur = 0 , nxt = 1;
    memset(f[cur] , 0 , sizeof(f[cur]));
    f[cur][0] = 1;
    for (int j = 0 ; j < n ; ++ j) {
        if (i != j) {
            x = inverse((i - j + Q) % Q);
            y = (LL)(Q - j) * x % Q;
            //printf("%d %d : %d %d\n" , i , j , x , y);
            memset(f[nxt] , 0 , sizeof(f[nxt]));
            for (int k = 0 ; k < n ; ++ k) {
                if (f[cur][k]) {
                    f[nxt][k] += (LL)f[cur][k] * y % Q;
                    f[nxt][k] %= Q;
                    f[nxt][k + 1] += (LL)f[cur][k] * x % Q;
                    f[nxt][k + 1] %= Q;
                }
            }
            swap(cur , nxt);
        }
    }
    for (int j = 0 ; j < n ; ++ j)
        L[i][j] = f[cur][j];
}
memset(res , 0 , sizeof(res));
for (int i = 0 ; i < n ; ++ i)
    for (int x = 0 ; x < n ; ++ x) {
        res[x] += (LL)L[i][x] * val[i] % Q;
        res[x] %= Q;
    }
/******************************************/
// 特殊的，一个K阶多项式已知前K+1项求第n项 O(Klogn)
// 例: 求前n个自然数的K次方和，多项式是K+1阶
scanf("%d%d" , &n , &K);
for (int i = 1 ; i <= K + 1 ; ++ i) {
    f[i] = (f[i - 1] + power(i , K)) % Q;
}
if (n <= K + 1) {
    printf("%d\n" , f[n]);
    return;
}
int A = 1 , B = 1;
for (int i = 0 ; i <= K + 1; ++ i)
    A = (LL)A * (n - i) % Q;
for (int i = 1 ; i <= K + 1; ++ i)
    B = (LL)B * (Q - i) % Q;
int res = 0;
for (int i = 0 ; i <= K + 1; ++ i) {
    int C = (LL)A * inverse((LL)(n - i) * B % Q) % Q;
    res += (LL)f[i] * C % Q , res %= Q;
    if (i == K + 1) break;
    B = (LL)B * (i + 1) % Q * inverse(Q - (K + 1 - i)) % Q;
}
printf("%d\n" , res);
