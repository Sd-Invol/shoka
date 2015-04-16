#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
int n , a[N] , b[N];
int f[N][2] , c[N];

struct opt {
    int x , y , id;
    bool operator < (const opt& R) const {
        return make_pair(x , y) < make_pair(R.x , R.y);
    }
    bool operator <= (const opt& R) const {
        return make_pair(x , y) <= make_pair(R.x , R.y);
    }
};
vector<opt> A , B;

void work() {
    int i , j , k , x , y;
    char str[10];
    scanf("%d" , &n);
    memset(f , 0xC0 , sizeof(f));
    memset(c , 0xC0 , sizeof(c));
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%s%d%d" , str , &x , &y);
        if (*str == 'B') {
            x = i - 1 - x;
            y = i - 1 - y;
        }
        a[i] = x , b[i] = y;
        
        if (a[i] <= i - 1) f[i][0] = 1;
        if (b[i] <= i - 1) f[i][1] = 1;
        if (a[i] >= 0 && a[i] < i) {
            A.push_back((opt){i - a[i] , a[i] , i});
            B.push_back((opt){i - a[i] , a[i] + 1 , i});
        }
        if (b[i] >= 0 && b[i] < i) {
            A.push_back((opt){i - b[i] , b[i] , -i});
            B.push_back((opt){i - b[i] + 1 , b[i] , -i});
        }
    }
    sort(A.begin() , A.end());
    sort(B.begin() , B.end());
    for (i = 0 , j = 0; i < A.size() ; ++ i) {
        while (j < B.size() && B[j] <= A[i]) {
            if (B[j].id > 0) {
                x = B[j].id;
                for (k = a[x] + 1 ; k <= n ; k += ~k & k + 1)
                    c[k] = max(c[k] , f[x][0]);
            } else {
                x = -B[j].id;
                for (k = b[x] ; k <= n ; k += ~k & k + 1)
                    c[k] = max(c[k] , f[x][1]);                
            }            
            ++ j;
        }
        if (A[i].id > 0) {
            x = A[i].id;           
            for (k = a[x] ; k >= 0 ; k -= ~k & k + 1)
                f[x][0] = max(f[x][0] , c[k] + 1);
        } else {
            x = -A[i].id;
            for (k = b[x] ; k >= 0 ; k -= ~k & k + 1)
                f[x][1] = max(f[x][1] , c[k] + 1);
        }
    }
    int res = 0;
    for (i = 1 ; i <= n ; ++ i) {
        res = max(res , f[i][0]);
        res = max(res , f[i][1]);
    }
    cout << res << endl;
}

int main() {
    work();
    return 0;
}
