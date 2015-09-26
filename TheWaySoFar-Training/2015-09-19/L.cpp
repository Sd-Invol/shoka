#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 5e6 + 5;
int n , a[N] , A , B , ca;

void RD(int& x) {
    x = 0; char c = getchar(); int sign = 1;
    if (c == '-') sign = -1 , c = getchar();
    for ( ;!isdigit(c) ; c = getchar()); x = c - '0';
    for (c = getchar() ; isdigit(c) ; c = getchar()) x = x * 10 + c - '0';
    x *= sign;
}
bool f[N];

void work() {
    scanf("%d%d%d" , &n , &A , &B);
    vector<int> V;
    for (int i = 0 ; i < n ; ++ i)
        RD(a[i]) , f[i] = 0;
    int x = -1 , y = -1;
    for (int i = 0 ; i < n ; ++ i) {
        if (f[i]) continue;
        if (!~x || a[i] > a[x]) {
            y = x;
            x = i;
        } else if (!~y || a[i] > a[y])
            y = i;
    }
    if (~x) V.push_back(x) , f[x] = 1;
    if (~y) V.push_back(y) , f[y] = 1;
    x = -1 , y = -1;
    for (int i = 0 ; i < n ; ++ i) {
        if (f[i]) continue;
        if (!~x || a[i] < a[x]) {
            y = x;
            x = i;
        } else if (!~y || a[i] < a[y])
            y = i;
    }
    if (~x) V.push_back(x) , f[x] = 1;
    if (~y) V.push_back(y) , f[y] = 1;
    x = -1 , y = -1;
    for (int i = 0 ; i < n ; ++ i) {
        if (a[i] > 0 || f[i]) continue;
        if (!~x || a[i] > a[x]) {
            y = x;
            x = i;
        } else if (!~y || a[i] > a[y])
            y = i;
    }
    if (~x) V.push_back(x) , f[x] = 1;
    if (~y) V.push_back(y) , f[y] = 1;
    x = -1 , y = -1;
    for (int i = 0 ; i < n ; ++ i) {
        if (a[i] < 0 || f[i]) continue;
        if (!~x || a[i] < a[x]) {
            y = x;
            x = i;
        } else if (!~y || a[i] < a[y])
            y = i;
    }
    if (~x) V.push_back(x) , f[x] = 1;
    if (~y) V.push_back(y) , f[y] = 1;
    
    
    LL res = -1LL << 60;
    for (int i = 0 ; i < V.size() ; ++ i)
        for (int j = 0 ; j < V.size() ; ++ j) {
            int x = V[i] , y = V[j];
            if (x != y) {
                res = max(res , (LL)A * a[x] * a[x] + (LL)B * a[y]);
            }
        }
    printf("Case #%d: %lld\n" , ++ ca , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
