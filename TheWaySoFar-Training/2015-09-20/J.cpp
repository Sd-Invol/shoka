#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <bitset>
using namespace std;
typedef long long LL;
const int N = 50000;
int n , m , Q;
int p[N][5];
pair<int , int> q[5][N];
bitset<50000> mask[5][256];
int val[5][256];
void work() {
    scanf("%d%d" , &n , &m);
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < 5 ; ++ j) {
            scanf("%d" , &p[i][j]);
        }
    }
    int M = sqrt(n);
    int B = (n + M - 1) / M;
    for (int k = 0 ; k < 5 ; ++ k) {
        for (int i = 0 ; i < n ; ++ i)
            q[k][i] = make_pair(p[i][k] , i);
        sort(q[k] , q[k] + n);
        for (int j = 0 ; j < B ; ++ j) {
            int L = j * M;
            int R = min(n , L + M);
            if (j > 0) 
                mask[k][j] = mask[k][j - 1];
            else
                mask[k][j].reset();
            for (int i = L ; i < R ; ++ i)
                mask[k][j].set(q[k][i].second);            
            val[k][j] = q[k][R - 1].first;
        }        
    }
    int pre = 0;
    scanf("%d" , &Q);
    while (Q --) {
        bitset<50000> res;
        int a[5];
        for (int k = 0 ; k < 5 ; ++ k) {
            scanf("%d" , &a[k]);
            a[k] ^= pre;
        }
        for (int k = 0 ; k < 5 ; ++ k) {
            int x = a[k];
            bitset<50000> tmp;
            for (int j = B - 1 ; j >= -1 ; -- j) {
                if (!~j || val[k][j] <= x) {
                    if (~j)
                        tmp = mask[k][j];
                    j = (j + 1) * M;
                    while (j < n && q[k][j].first <= x) {
                        tmp.set(q[k][j].second);
                        ++ j;
                    }
                    break;
                }
            }            
            if (k == 0)
                res = tmp;
            else
                res &= tmp;
        }     
        int cnt = res.count();        
        printf("%d\n" , cnt);
        pre = cnt;
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();    
    return 0;
}
