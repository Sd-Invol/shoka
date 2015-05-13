#include <bits/stdc++.h>
using namespace std;
const int N = 105;

int n ;
vector<int> e[N];
int nxt[N][N] , bel[N] , newbel[N];
map< vector< vector<int> > , int > Hash;

void work() {
    int i , j , k , l , x , y;
    scanf("%d" , &n);
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &y);
        e[i].resize(y);
        for (j = 0 ; j < y ; ++ j) {
            scanf("%d" , &e[i][j]);            
        }
        for (j = 0 ; j < y ; ++ j)
            nxt[i][e[i][j]] = e[i][(j + 1) % y];
    }

    for (i = 1 ; i <= n ; ++ i) {
        bel[i] = e[i].size();
    }
    int size = n + 1;
    do {
        int newsize = 0;
        Hash.clear();            
        for (i = 1 ; i <= n ; ++ i) {
            vector< vector<int> > VV; 
            for (j = 0 ; j < e[i].size() ; ++ j) {
                vector<int> V;
                x = i , y = e[i][j];
                for (l = 0 ; l < 200 ; ++ l) {
                    V.push_back(bel[x]);
                    int tmp = x;
                    x = y;
                    y = nxt[y][tmp];
                }
                VV.push_back(V);
            }                        
            sort(VV.begin() , VV.end());
            /*printf("%d:\n" , i);
            for (j = 0 ; j < VV.size() ; ++ j)
                for (k = 0 ; k < VV[j].size() ; ++ k)
                printf("%d%c" , VV[j][k] , " \n"[k + 1 == VV[j].size()]);*/
            if (Hash.count(VV))
                newbel[i] = Hash[VV];
            else
                newbel[i] = Hash[VV] = newsize ++;
        }        
        if (newsize == size)
            break;        
        size = newsize;
        memcpy(bel , newbel , sizeof(bel));
    } while (1);
    int cnt = 0;
    for (i = 0 ; i < size ; ++ i) {
        vector<int> V;
        for (j = 1 ; j <= n ; ++ j)
            if (bel[j] == i)
                V.push_back(j);
        if (V.size() > 1) {
            ++ cnt;
            for (j = 0 ; j < V.size() ; ++ j)
                printf("%d%c" , V[j] , " \n"[j + 1 == V.size()]);
        }
    }
    if (!cnt)
        puts("none");
}

int main() {
    work();
    return 0;
}
