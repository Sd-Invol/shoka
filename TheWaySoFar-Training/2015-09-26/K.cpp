#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int N = 200005;
int Q , k1 , b1 , k2 , ca;
int inverse(int x) {
    return x == 1 ? x : (LL)(Q - Q / x) * inverse(Q % x) % Q;
}

int power(int A , int B) {
    if (B < 0) {
        A = inverse(A);
        B = -B;
    }
    int res = 1;
    while (B) {
        if (B & 1)
            res = (LL) res * A % Q;
        A = (LL)A * A % Q , B >>= 1;
    }
    return res;
}

void work() {
    k1 %= Q - 1;
    k2 %= Q - 1;
    b1 %= Q - 1;
    vector< pair<int , int > > V;
    unordered_map< LL , vector<int> > Hash;
    for (int i = 1 ; i < Q ; ++ i) {
        int x = power(i , b1);
        int y = power(i , k1);
        Hash[(LL)x * Q + y].push_back(i);
    }
    for (int i = 1 ; i < Q ; ++ i) {
        int x = power(i , 1 - k2);
        int y = power(i , k2);
        x = (Q - x) % Q;
        LL w = (LL) x * Q + y;
        if (Hash.count(w))
            for (auto &it : Hash[w])
                V.push_back(make_pair(it , i));
    }
    sort(V.begin() , V.end());
    V.resize(unique(V.begin() , V.end()) - V.begin());
    printf("Case #%d:\n" , ++ ca);
    if (V.empty())
        puts("-1");
    else {
        for (int i = 0 ; i < V.size() ; ++ i)
            printf("%d %d\n" , V[i].first , V[i].second);
    }

}

int main() {
    while (~scanf("%d%d%d%d" , &Q , &k1 , &b1 , &k2))
        work();
    return 0;
}