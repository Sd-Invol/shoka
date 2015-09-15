#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 1005;

int n , a[N] , b[N];
int l[N] , r[N] , f[N];

void work() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
        b[a[i]] = i;
        l[i] = r[i] = f[i] = 0;
    }
    for (int i = 2 ; i <= n ; ++ i) {
        int x = 1 , y;
        while (1) {
            y = x;
            if (a[i] < a[x])
                x = l[x];
            else
                x = r[x];
            if (!x)
                break;
        }
        f[i] = y;
        if (a[i] < a[y]) {
            l[y] = i;
        } else {
            r[y] = i;
        }
    }
    int m;
    scanf("%d" , &m);
    for (int i = 0 ; i < m ; ++ i) {
        int x;
        scanf("%d" , &x);
        x = b[x];
        vector<char> res;
        while (x != 1) {
            if (l[f[x]] == x)
                res.push_back('E');
            else
                res.push_back('W');
            x = f[x];
        }
        for (int i = (int)res.size() - 1 ; i >= 0 ; -- i)
            putchar(res[i]);
        puts("");
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
