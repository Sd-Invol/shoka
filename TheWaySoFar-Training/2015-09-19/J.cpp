#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <unordered_map>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 233333;
const int Q = 530600414;
LL cnt[N] , len[N] , res[N] , top[N] , bot[N];

void work() {
    cnt[1] = 1 , len[1] = 1 , res[1] = 0 , top[1] = 0 , bot[1] = 1;
    cnt[2] = 0 , len[2] = 2 , res[2] = 0 , top[2] = 0 , bot[2] = 0;
    for (int i = 3 ; i < N ; ++ i) {
        cnt[i] = (cnt[i - 2] + cnt[i - 1]) % Q;
        len[i] = (len[i - 2] + len[i - 1]) % Q;
        res[i] = (res[i - 2] + res[i - 1] + bot[i - 2] * cnt[i - 1] + top[i - 1] * cnt[i - 2]) % Q;
        top[i] = (top[i - 2] + top[i - 1] + cnt[i - 1] * len[i - 2]) % Q;
        bot[i] = (bot[i - 1] + bot[i - 2] + cnt[i - 2] * len[i - 1]) % Q;        
    }
    int T , ca = 0 , n;
    scanf("%d" , &T);
    while (T --) {
        scanf("%d" , &n);
        printf("Case #%d: %d\n" , ++ ca , (int)res[n]);
    }
}

int main() {
    work();    
    return 0;
}
