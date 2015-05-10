#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;

int b , s , n , K;
struct opt {
    int begin , end;
    LL cnt[13][13] , num;
    opt (int id = -1) {
        begin = end = id , num = !!~id;
        memset(cnt , 0 , sizeof(cnt));
    }
    opt operator + (const opt& R) const {
        if (!~begin) return R;
        if (!~R.end) return *this;
        opt res;
        res.begin = begin , res.end = R.end , res.num = num + R.num;
        for (int i = 0 ; i < K ; ++ i)
            for (int j = 0 ; j < K ; ++ j)
                res.cnt[i][j] = cnt[i][j] + R.cnt[i][j];
        if (~end && ~R.begin)
            ++ res.cnt[end][R.begin];
        return res;
    }
};
pair<int , int> pro[N];

void read() {
    int i , j , x;
    char str[20];
    scanf("%d%d" , &b , &s);
    while (~scanf("%s" , str)) {
        if (*str == 'V') {
            sscanf(str + 1 , "%d" , &x);
            K = max(K , x);
            pro[n ++] = make_pair(0 , x - 1);
        } else if (*str == 'R') {
            sscanf(str + 1 , "%d" , &x);
            pro[n ++] = make_pair(1 , x);
        } else {
            pro[n ++] = make_pair(2 , 0);
        }
    }
}
opt QwQ;
int bel[15] , mask , num[15];
LL res , cnt[13][13];

void dfs(int k , int setcnt) {
    if (setcnt >= b)
        return;
    if (k == K) {
        if (setcnt > 1) {
            int tmp[15];
            memcpy(tmp , num , sizeof(tmp));
            nth_element(tmp , tmp + 1 , tmp + setcnt);
            if (tmp[0] + tmp[1] <= s)
                return;
        }

        LL sum = !!QwQ.num;
        for (int i = 0 ; i < K ; ++ i)
            for (int j = 0 ; j < K ; ++ j)
                if (bel[i] != bel[j])
                    sum += cnt[i][j];
        res = min(res , sum);
    } else {
        if (mask >> k & 1) {
            dfs(k + 1 , setcnt);
        } else {
            for (int i = 0 ; i <= setcnt ; ++ i) {
                bel[k] = i;
                num[i] ++;
                if (num[i] <= s)
                    dfs(k + 1 , setcnt + (i == setcnt));
                num[i] --;
            }
        }
    }
}
int rep[N] , top;
opt S[N] ;

opt cal() {
    S[top = 1] = opt();
    for (int i = 0 ; i < n ; ++ i) {
        if (pro[i].first == 0) {
            if (~mask >> pro[i].second & 1)
                S[top] = S[top] + opt(pro[i].second);
        } else if (pro[i].first == 1) {
            S[++ top] = opt();
            rep[top] = pro[i].second;
        } else {
            int m = rep[top];
            opt& A = S[top --];
            while (m) {
                if (m & 1)
                    S[top] = S[top] + A;
                A = A + A , m >>= 1;
            }
        }
    }
    return S[top];
}

void work() {
    read();
    res = 1LL << 60;
    LL sum = cal().num;
    for (mask = 0 ; mask < 1 << K ; ++ mask) {
        if (__builtin_popcount(mask) != s)
            continue;
        memcpy(cnt , (QwQ = cal()).cnt , sizeof(cnt));
        /*for (int i = 0 ; i < K ; ++ i)
            for (int j = 0 ; j < K ; ++ j)
            printf("%lld%c" , cnt[i][j] , " \n"[j == 12]);*/
        dfs(0 , 0);
    }
    cout << res + sum << endl;
}

int main() {

    work();
    return 0;
}
