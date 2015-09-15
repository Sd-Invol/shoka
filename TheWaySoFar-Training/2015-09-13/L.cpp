#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
const int Q = 1e9 + 7;
typedef long long LL;
int n , X[N] , Y[N];
int power[N];
void work() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d" , &X[i] , &Y[i]);
    }

    int res1 = 0 , res2 = 0;
    int sum = 0;
    for (int i = 0 ; i < n ; ++ i) {
        sum += (LL)Y[i] * power[n - i - 1] % Q;
        sum %= Q;
    }
    for (int i = 0 ; i < n ; ++ i) {
        res1 += (LL)sum * X[i] % Q;
        res1 %= Q;
        sum += Q - (LL)power[n - 1] * Y[i] % Q;
        sum %= Q;
        sum *= 2 , sum %= Q;
        sum += Y[i] , sum %= Q;
    }
    for (int i = 0 ; i < n ; ++ i)
        swap(X[i] , Y[i]);
    sum = 0;
    for (int i = 0 ; i < n ; ++ i) {
        sum += (LL)Y[i] * power[n - i - 1] % Q;
        sum %= Q;
    }
    for (int i = 0 ; i < n ; ++ i) {
        //cout << sum << endl;
        res2 += (LL)sum * X[i] % Q;
        res2 %= Q;
        sum += Q - (LL)power[n - 1] * Y[i] % Q;
        sum %= Q;
        sum *= 2 , sum %= Q;
        sum += Y[i] , sum %= Q;
    }
    printf("%d\n" , (res1 - res2 + Q) % Q);
}


int main() {
    power[0] = 1;
    for (int i = 1 ; i < N ; ++ i)
        power[i] = power[i - 1] * 2 % Q;
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
