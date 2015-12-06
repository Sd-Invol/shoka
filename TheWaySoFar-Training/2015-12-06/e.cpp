#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 105;
int n , K , s[N];
int a[N][N] , p[N];

int main() {
    freopen("easy.in" , "r" , stdin);
    freopen("easy.out" , "w" , stdout);

    scanf("%d%d" , &n , &K);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , &s[i]);
        for (int j = 0 ; j < s[i] ; ++ j)
            scanf("%d" , &a[i][j]);
        a[i][s[i]] = 50;
    }

    int sum = 0 , num = 0;
    int step = 0 , now = 0;
    while (num < K) {
        if (p[now] < s[now]) {
            if (a[now][p[now]] >= sum) {
                sum += a[now][p[now]];
                ++ p[now];
                now = (now + 1) % n;
                step = 0;
                ++ num;
            } else {
                ++ p[now];
                now = (now + 1) % n;
                ++ step;
            }
        } else {
            if (a[now][p[now]] >= sum) {
                sum += a[now][p[now]];
                now = (now + 1) % n;
                step = 0;
                ++ num;
            } else {
                now = (now + 1) % n;
                ++ step;
            }        
        }
        if (step >= n * K + 5)
            break;
    }
    sum += (K - num) * 50;
    printf("%d\n" , sum);
    return 0;
}

