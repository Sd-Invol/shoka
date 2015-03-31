#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2014;
int n;
int d[N][N] , bel[N];
bool f[N + N];
int id[N + N] , s[N];

struct opt {
    int x , y;
    int a , b;
    bool operator < (const opt& R) const {
        return (LL)a * R.b > (LL)R.a * b;
    }
};
priority_queue<opt> Q;

int main() {
    int i , j , k;
    scanf("%d" , &n);
    for (i = 0 ; i < n ; ++ i) {
        id[i] = i , bel[i] = i , s[i] = 1;
        for (j = 0 ; j < n ; ++ j) {
            scanf("%1d" , &d[i][j]);
            if (i != j)
                Q.push((opt) {i , j , d[i][j] , 1});
        }
    }
    int num = n;
    for (int T = 1 ; T < n ; ++ T) {
        opt t = Q.top(); Q.pop();
        if (f[t.x] || f[t.y]) {-- T; continue;}
        int x = t.x , y = t.y , z = num ++;
        f[x] = f[y] = 1;
        printf("%d %d %.10f\n" , x + 1 , y + 1 , 1.0 * t.a / t.b);
        x = id[x] , y = id[y];
        id[num - 1] = x , bel[x] = num - 1;
        s[x] += s[y];
        for (i = 0 ; i < n ; ++ i) {
            d[x][i] += d[y][i];
            d[i][x] += d[i][y];
            if (i != x) {
                Q.push((opt) {num - 1 , bel[i] , d[x][i] , s[x] * s[i]});
                Q.push((opt) {bel[i] , num - 1  , d[x][i] , s[x] * s[i]});
            }
        }
    }
    return 0;
}
