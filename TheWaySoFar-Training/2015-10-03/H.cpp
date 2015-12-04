#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
const int N = 25;
const int M = 1000;
typedef long long LL;
using namespace std;
int n , K;
double p[N];
vector<int> e[N];
map<vector<int> , int> Hash;
vector<int> cnt[M];
void dfs(int k , int U , int s , vector<int>& V) {
    if (s > n)
        return;
    if (s == n) {
        Hash[V] = K;
        cnt[K] = V;
        ++ K;
        return;
    }
    for (int i = U ; i > 0 ; -- i) {
        V.push_back(i);
        dfs(k + 1 , i , s + i , V);
        V.pop_back();
    }
}
double f[M][N] , a[N][N];
int main() {
    scanf("%d" , &n);
    vector<int> V;
    dfs(0 , n , 0 , V);
    for (int i = 0 ; i < n ; ++ i)
        scanf("%lf" , &p[i]);
    for (int i = 0 ; i < n ; ++ i) {
        int j , x;
        scanf("%d" , &j);
        while (j --) {
            scanf("%d" , &x);
            -- x;
            e[i].push_back(x);
        }
    }
    
    for (int l = 1 ; l < K ; ++ l) {
        V = cnt[l];
        static int bel[N];
        int L = 0;
        memset(bel , -1 , sizeof(bel));
        int S = n * (n - 1) / 2;
        for (int i = 0 ; i < V.size() ; ++ i)
            for (int j = 0 ; j < V[i] ; ++ j)
                bel[L ++] = i; 
        // for (int i = 0 ; i < n ; ++ i) {
        //    printf("%d%c" , bel[i] , " \n"[i + 1 == n]);
        //}
        memset(a , 0 , sizeof(a));
        int R = n , C = n + 1;
        for (int x = 0 ; x < n ; ++ x) {
            -- a[x][x] , -- a[x][n];
            double P = (1 - p[x]) / e[x].size();
            for (auto &y : e[x]) {
                a[x][y] += P;
            }
            P = p[x] / e[x].size() / S;            
            for (int X = 0 ; X < n ; ++ X) {
                for (int Y = X + 1 ; Y < n ; ++ Y) {
                    //if (X == Y) continue;
                    if (bel[X] == bel[Y]) {
                        for (auto &y : e[x])
                            a[x][y] += P;                        
                    } else {
                        vector<int> W = V;
                        W[bel[X]] += W[bel[Y]];
                        swap(W[bel[Y]] , W.back());
                        W.pop_back();
                        sort(W.begin() , W.end() , greater<int>());
                        int j = Hash[W];
                        //printf("%d\n" , j);
                        for (auto &y : e[x]) {
                            // if (j)
                                a[x][n] -= P * f[j][y];
                                //else
                                //    a[x][n] -= P * (f[j][y] - 1);
                        }
                    }
                }
            }           
        }
        int Rank = 0;
        for (int i = 0 ; i < C ; ++ i) {
            int pivot = Rank;
            for (int x = Rank + 1 ; x < R ; ++ x)
                if (fabs(a[x][i]) > fabs(a[pivot][i]))
                    pivot = x;
            if (fabs(a[pivot][i]) < 1e-8)
                continue;
            for (int j = 0 ; j < C ; ++ j)
                swap(a[Rank][j] , a[pivot][j]);
            double tmp = a[Rank][i];
            for (int j = 0 ; j < C ; ++ j)
                a[Rank][j] /= tmp;
            for (int j = 0 ; j < R ; ++ j) {
                if (j == Rank || fabs(a[j][i]) < 1e-8)
                    continue;
                double tmp = a[j][i];
                for (int k = 0 ; k < C ; ++ k)
                    a[j][k] -= tmp * a[i][k];
            }
            ++ Rank;
        }
        // printf("%d\n" , l);
        for (int i = 0 ; i < n ; ++ i) {
            f[l][i] = a[i][n];
            //    printf("%f %f\n" , a[i][i] , a[i][n]);
        }
    }
    
    printf("%.10f\n" , f[K - 1][0]);
    return 0;
}
