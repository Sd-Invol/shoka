#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL limit = 1e18;

vector<int> ver;
int a[100];
int n;
const double eps = 1e-10;


int h[7][20] = {
    {1},
    {2},
    {3,4},
    {4,6,10},
    {5,6,8,9,14,21},
    {6,8,10,14,44,52},
    {7,8,9,10,12,15,22,33,39,52,55,68,102,114,138}
};
int len[] = {1,1,2,3,6,6,15};
LL res;
LL X;
int www;
vector< pair<LL , int> > V;
void dfs1(int K, int cnt, LL lc , int *ver) {
    if (lc > X) return;
    if (K == len[n]) {
        if (!cnt) return;
        if (n < 6) {
            if (cnt & 1) 
                res += X / lc;
            else
                res -= X / lc;
        } else {
            if (cnt & 1)
                V.push_back(make_pair(lc , 1));
            else
                V.push_back(make_pair(lc , -1));                
        }
        return ;
    }
    if (lc % ver[K] == 0)
        return;
    dfs1(K + 1, cnt, lc , ver);
    LL tmp = __gcd(lc, (LL)ver[K]);
    if (lc / tmp > X / ver[K] + 1) return ;
    dfs1(K + 1, cnt + 1, lc / tmp * ver[K] , ver);
}
vector< pair<LL , int> > W;
    
LL calc(LL x , int *ver) {
    if (n < 6) {
        X = x;
        res = 0;
        dfs1(0 , 0 ,1 , ver);
    } else {
        res = 0;
        for (int i = 0 ; i < W.size() ; ++ i) {
            if (x < W[i].first)
                break;
            res += x / W[i].first * W[i].second;
        }
    }
    return res;
}
int main() {
    n = 6;
    X = 1e18;
    dfs1(0 , 0 , 1 , h[n]);
    sort(V.begin() , V.end());
    for (int i = 0 ; i < V.size() ; ++ i) {
        int j = i , s = 0;
        while (j < V.size() && V[j].first == V[i].first) {
            s += V[j ++].second;
        }
        W.push_back(make_pair(V[i].first , s));
        i = j - 1;
    }
    cout << W.size() << endl;
    int T;
    scanf("%d", &T);
    while (T--) {
        LL L, R;
        scanf("%lld%lld%d", &L, &R, &n);
        -- n;
        printf("%lld\n", calc(R , h[n]) - calc(L - 1 , h[n]));
        //cout << www << endl;
    }
    return 0;
}
