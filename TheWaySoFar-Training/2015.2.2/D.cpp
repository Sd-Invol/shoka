#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
const int Q = 1e9 + 7;
int phi[N] , sum[N];

void init() {
    int i , j;
    phi[1] = 1;
    for (i = 1 ; i < N ; ++ i)
        for (j = i + i ; j < N ; j += i)
            phi[j] -= phi[i];
    for (i = 1 ; i < N ; ++ i) {
        if (phi[i]) {
            phi[i] = (LL) i * i % Q * phi[i];
            phi[i] = (phi[i] + Q) % Q;            
        }
    }
    sum[0] = 0;
    for (i = 1 ; i < N ; ++ i) {
        sum[i] = sum[i - 1] + i;
        sum[i] %= Q;
    }
}
int T;
struct opt {
    int n , m , a , id;
    bool operator < (const opt& R) const {
        return a < R.a;
    }
}q[N];
int c[N] , ans[N];

void add(int x , int w) {
    while (x < N) {
        c[x] += w , c[x] %= Q;
        x += x & -x;        
    }
}
int get(int x) {
    int res = 0;
    while (x > 0) {
        res += c[x] , res %= Q;
        x -= x & -x;
    }
    return res;
}

void work() {
    int i , j , k , l , x , y;
    scanf("%d",&T);
    for (i = 0 ; i < T ; ++ i) {
        scanf("%d%d%d",&q[i].n , &q[i].m , &q[i].a);
        if (q[i].n > q[i].m)
            swap(q[i].n , q[i].m);
        q[i].id = i;
    }
    sort(q , q + T);
    for (i = 0 , j = 1 ; i < T ; ++ i) {
        while (j <= q[i].a) {
            for (k = 1 , l = j ; l < N ; ++ k , l += j)
                add(l , (LL)j * phi[k] % Q);
            ++ j;
        }
        int& res = ans[q[i].id];
        int n = q[i].n , m = q[i].m;
        for (k = 1 ; k <= n ; k = x + 1) {
            x = min(n / (n / k) , m / (m / k));
            y = (get(x) - get(k - 1) + Q) % Q;
            res += (LL) sum[n / k] * sum[m / k] % Q * y % Q;
            res %= Q;
        }
    }
    for (i = 0 ; i < T ; ++ i)
        printf("%d\n" , ans[i]);
}

int main() {
    init();
    work();    
    return 0;
}
