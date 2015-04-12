#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

typedef long long LL;
const int N = 1e6 + 5;

int bo[N];

vector<pair<LL, int> > prime;

void multi(LL &p, LL a, LL n) {
    if (p > n / a) p = n + 1;
    else p = p * a;
}

LL a, n;

void mul(LL &ans, LL x, LL t) {
    while (t) {
        multi(ans, x, n);
        --t;
    }
}

LL gett() {
    for (int i = prime.size() - 1; i >= 0; --i) {
        LL ans = 1;
        for (int j = 0; j < i; ++j) {
            mul(ans, prime[j].first, prime[j].second);
        }
        mul(ans, prime[i].first, prime[i].second + 1);
        for (int j = i + 1; j < prime.size(); ++j)
            mul(ans, prime[j].first, 1);
        if (ans <= n) return ans;
    }
    return -1;
}

int main() {
    scanf("%lld%lld", &a, &n);
    if (a == 1) {
        puts("-1");
        return 0;
    }
    LL p = a, ans = 1;
    int flag = 0;
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            for (int j = i * 2; j < N; j += i) bo[j] = 1;
            if (a % i == 0) {
                int num = 0;
                while (a % i == 0) {
                    a /= i;
                    ++num;
                }
                prime.push_back(make_pair(i, num));
            }
        }
    
  
    if (a != 1) {
        LL S = sqrt(a) - 1;
        while (S * S < a) ++S;
        if (S * S != a) prime.push_back(make_pair(a, 1));
        else prime.push_back(make_pair(S, 2));
    }
    printf("%lld\n", gett());
    return 0;
}
