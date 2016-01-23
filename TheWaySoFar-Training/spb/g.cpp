#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;
const int N = 20;

int a[N] , b[N] , c[N] , d[N];
int P[N] , t[N] , w[N];
bool f[N];
vector< pair<int , int> > trans(int *A , int *B , int n) {
    for (int i = 0 ; i < n ; ++ i)
        t[B[i]] = i;
    for (int i = 0 ; i < n ; ++ i)
        w[i] = t[A[i]];
    for (int i = 0 ; i < n ; ++ i)
        t[i] = A[i];
    memset(f , 0 , sizeof(f));
    vector< pair<int , int> > res;

    for (int i = 0 ; i < n ; ++ i) {
        if (!f[i]) {
            vector<int> V;
            int x = i;
            while (!f[x]) {
                f[x] = 1;
                V.push_back(x);
                x = w[x];
            }
            while (V.size() > 1) {
                int y = V.back(); V.pop_back();
                int z = V.back(); V.pop_back();
                res.push_back(make_pair(z , y));
                swap(t[z] , t[y]);
                V.push_back(z);
            }            
        }
    }
    for (int i = 0 ; i < n ; ++ i)
        assert(t[i] == B[i]);
    return res;
}

int main() {
    for (int i = 0 ; i < 16 ; ++ i) {
        scanf("%d" , &c[i]);
        -- c[i];
        P[i] = i;
    }
    //random_shuffle(c , c + 16);
    for (int i = 0 ; i < 4 ; ++ i) {
        a[i] = b[i] = i;
    }
    int res = 1 << 30;
    vector< pair<int , int> > na , nb , nc;
    do {
        vector< pair<int , int> > A = trans(P , a , 4);
        do {            
            vector< pair<int , int> > B = trans(P , b , 4);
            for (int i = 0 ; i < 16 ; ++ i) {
                int x = i / 4 , y = i % 4;
                d[i] = c[a[x] * 4 + b[y]];
            }
            vector< pair<int , int> > C = trans(d , P , 16);

            int cnt = A.size() + B.size() + C.size();
            if (cnt < res) {
                res = cnt;
                na = A , nb = B , nc = C;
            }
            
        } while (next_permutation(b , b + 4));
        
    } while (next_permutation(a , a + 4));
    printf("%d\n" , res);
    for (int i = 0 ; i < na.size() ; ++ i) {
        int x = na[i].first , y = na[i].second;
        printf("%c-%c\n" , 'a' + x , 'a' + y);
        for (int j = 0 ; j < 4 ; ++ j)
            swap(c[x * 4 + j] , c[y * 4 + j]);
    }
    for (int i = 0 ; i < nb.size() ; ++ i) {
        int x = nb[i].first , y = nb[i].second;
        printf("%c-%c\n" , '1' + x , '1' + y);
        for (int j = 0 ; j < 4 ; ++ j)
            swap(c[j * 4 + x] , c[j * 4 + y]);
    }
    for (int i = 0 ; i < nc.size() ; ++ i) {
        int j , x , y;
        j = nc[i].first , x = j / 4 , y = j % 4;
        printf("%c%c-" , 'a' + x , '1' + y);
        j = nc[i].second , x = j / 4 , y = j % 4;
        printf("%c%c\n" , 'a' + x , '1' + y);
        swap(c[nc[i].first] , c[nc[i].second]);
    }
    for (int i = 0 ; i < 16 ; ++ i)
        assert(c[i] == i);
    
    return 0;
}

/*

02 00 15 09
14 04 10 08
12 05 06 01
03 11 07 13
 */
