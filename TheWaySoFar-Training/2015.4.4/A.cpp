#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
const int Q = 120586241;
LL p[N];
int n , B;
int a[N] , d[N] , D , s[N];
vector<int> c[N];
void work() {
    int i , j;
    scanf("%d%d",&n,&B);
    memset(s , 0 , B << 2);
    for (i = 0 ; i < n ; ++ i)
        scanf("%d" , &a[i]) , -- a[i];
    for (i = 0 ; i < B ; ++ i) {
        D = 0;
        for (j = i ; j < n ; j += B)
            d[D ++] = a[j];
        sort(d , d + D);
        for (j = i ; j < n ; j += B)
            a[j] = lower_bound(d , d + D , a[j]) - d;
    }
    for (i = 0 ; i < n ; ++ i)
        ++ s[i % B];
    for (i = 0 ; i < B ; ++ i)
        c[i].clear() , c[i].resize(s[i]);
    for (i = 0 ; i < n ; ++ i) {
        p[i] = s[i % B];
        if (s[i % B] == 2) 
            break;
        -- s[i % B];
    }
    int e = i; 
    for (i = e - 1 ; i >= 0 ; -- i)
        p[i] *= p[i + 1] , p[i] %= Q;
    LL res = 1;
    for (i = 0 ; i <= e ; ++ i) {       
        int x = a[i] , y = x , k = i % B;
        for (j = x ; j >= 0 ; j -= ~j & j + 1)
            y -= c[k][j];
        res += p[i + 1] * y % Q , res %= Q;
        for (j = x ; j < c[k].size() ; j += ~j & j + 1)
            c[k][j] ++;        
    }
    cout << res << endl;
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}