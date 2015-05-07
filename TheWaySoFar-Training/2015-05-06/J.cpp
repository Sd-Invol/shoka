#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n , m , ca;
pair<int , int> a[N];
int f[2005];

void init() {
    int i , j , k;
    n = 0;
    for (i = 2 , j = 1 ; ; ++ i) {
        j += i * i;
        if (j > 1000000)
            break;
        a[n ++] = make_pair(j , i);
    }
    for (i = 3 , j = 1 ; ; i += 2) {
        j += i * i;
        if (j > 1000000)
            break;
        a[n ++] = make_pair(j , -i);
    }
    for (i = 4 , j = 4 ; ; i += 2) {
        j += i * i;
        if (j > 1000000)
            break;
        a[n ++] = make_pair(j , -i);
    }
    sort(a , a + n);
    reverse(a , a + n);
    memset(f , 0x3F , sizeof(f));
    f[0] = 0;
    for (i = 0 ; i < n ; ++ i) {
        int x = a[i].first;
        for (j = 2000 ; j >= x ; -- j) {
            f[j] = min(f[j] , f[j - x] + 1);
        }
    }
}
int lev;
vector<int> V;

bool dfs(int k , int s , int pre) {
    if (k > lev) return 0;
    if (s == 0)
        return 1;
    if (k == lev) return 0;
    for (int i = pre ; i < n ; ++ i) {
        if (s >= a[i].first) {
            V.push_back(a[i].second);
            if (dfs(k + 1 , s - a[i].first , i + 1))
                return 1;
            V.pop_back();
        }
    }
    return 0;
}

void work() {
    int i , j , beg;
    printf("Case %d:" , ++ ca);
    if (m <= 2000) {
        if (f[m] > 10000) {
            puts(" impossible");
            return;
        } else {
            beg = f[m];
        }
    } else
        beg = 1;
    V.clear();
    for ( ; ; ++ beg) {
        lev = beg;
        if (dfs(0 , m , 0)) {
            for (int i = 0 ; i < V.size() ; ++ i) {
                if (V[i] < 0)
                    printf(" %dL" , -V[i]);
                else
                    printf(" %dH" , V[i]);
            }
            putchar('\n');
            break;
        }
    }
}

int main() {
    init();
    while (scanf("%d" , &m) , m)
        work();
    return 0;
}
