#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 6005;
int n;
bitset<6000> a[N];
char str[N];

void work() {
    int i , j , k , l , x;
    for (i = 0 ; i < n ; ++ i) {
        scanf("%s" , str);
        a[i].reset();
        for (j = 0 , k = 0; str[j] ; ++ j) {
            x = str[j] - '0';
            for (l = 0 ; l < 6 && k < n ; ++ k , ++ l) {
                if (x & 1)
                    a[i].set(k);
                x >>= 1;
            }
        }
    }
    int Rank = 0;
    for (i = 0 ; i < n && Rank < 30 ; ++ i) {
        int pivot = Rank;
        while (pivot < n && !a[pivot][i])
            ++ pivot;
        if (pivot >= n) continue;
        swap(a[Rank] , a[pivot]);
        for (k = 0 ; k < n ; ++ k) {
            if (k != Rank && a[k][i])
                a[k] ^= a[Rank];            
        }
        ++ Rank;
    }
    printf("%.15f\n" , 0.5 * (1 - pow(2 , -Rank)));
}

int main() {
    freopen("prob.in" , "r" , stdin);
    freopen("prob.out" , "w" , stdout);
    
    while (~scanf("%d" , &n))
        work();
    return 0;
}
