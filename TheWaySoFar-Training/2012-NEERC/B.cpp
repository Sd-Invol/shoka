#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 101;

int n , m;
int a[20] , cnt;
pair<int , int> res;

void dfs(int k , int mask , int sum) {
    if (sum > m)
        return;
    if (k < n) {
        dfs(k + 1 , mask | (1 << k) , sum + a[k]);
        dfs(k + 1 , mask , sum);
    } else {
        res = max(res , make_pair(sum , mask));
    }
}

void work() {

    int i , j , x , y , z;
    scanf("%d%d",&n,&m);
    scanf("%d",&x);
    puts("accept");
    fflush(stdout);
    while (x) {
        scanf("%d",&y);
        if (y < x) {
            puts("accept");
            x = y;
        } else {
            puts("decline");
        }
        fflush(stdout);
    }
    while (cnt < n) {
        scanf("%d",&y);
        if (y > x) {
            a[cnt ++] = y - x;
            if (cnt == n) {
                dfs(0 , 0 , 0);
                if (y == res.first) {
                    puts("stop");
                    return;
                } else {
                    puts("accept");
                    x = y;
                }
            } else {
                puts("accept");
                x = y;
            }
        } else {
            puts("decline");
        }
        fflush(stdout);
    }
    j = (1 << n) - 1;
    while (x > res.first) {
        scanf("%d",&y);
        if (y == res.first) {
            puts("stop");
            fflush(stdout);
            return;
        }
        if (y < x) {
            z = x - y;
            for (i = 0 ; i < n ; ++ i)
                if (a[i] == z && (~res.second >> i & 1) && (j >> i & 1)) {
                    j ^= (1 << i);
                    break;
                }
            if (i < n) {
                puts("accept");
                x = y;
            }  else
                puts("decline");
        } else {
            puts("decline");
        }
        fflush(stdout);
    }
}

int main() {
    work();
    return 0;
}
