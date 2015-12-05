#include <cstdio>
#include <algorithm>
using namespace std;
int n , m , k;
int a[10][10];

int main() {
    scanf("%d%d%d" , &n , &m , &k);
    int w , e;
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &w , &e);
        a[w][e] = a[e][w] = 1;
    }
    int cnt = 0;
    for (int i = 0 ; i <= 6 ; ++ i)
        if (!a[i][e])
            ++ cnt;
    if (!cnt && m && k)
        puts("YES");
    else
        puts("NO");
    return 0;
}
