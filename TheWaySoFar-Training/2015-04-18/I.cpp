#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;

int n , c[N + N];
LL res;

int main() {
    int i , x , L = 0 , d = 0;
    scanf("%d" , &n);
    for (i = 1 ; i <= n ; ++ i)
        scanf("%d%d" , &c[i + i - 1] , &c[i + i]);
    puts("BFS");
    int top = 0 , bot = -1;
    c[++ bot] = -1;
    while (top <= bot) {
        while (c[top] > 0)
            ++ top;
        x = -c[top ++];
        printf("%d\n" , x);
        if (x == L) {
            ++ d;
            L = 0;
        }
        res += d;
        if (c[x + x - 1] > 0) {
            while (c[bot + 1] > 0)
                ++ bot;
            c[++ bot] = -c[x + x - 1];
            if (!L) L = c[x + x - 1]; 
        }
        if (c[x + x] > 0) {
            while (c[bot + 1] > 0)
                ++ bot;
            c[++ bot] = -c[x + x];
            if (!L) L = c[x + x]; 
        }        
    }
    printf("%lld\n" , res);    
    return 0;
}
