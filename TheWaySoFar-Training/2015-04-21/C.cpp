#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 500005;
int n , a[N] , L[N] , R[N];
int LOG[N] , c[N];
vector<int> oper;

bool check(int l , int r) {
    int cnt = 0;
    int size = r - l + 1;
    memset(c , 0 , size + 1 << 2);
    for (int i = l ; i <= r ; ++ i) {
        for (int j = a[i] - l + 1 ; j <= size ; j += j & -j)
            cnt += c[j];
        if (cnt + 1 > size)
            return 0;
        for (int j = a[i] - l + 1 ; j ; j -= j & -j)
            ++ c[j];
    }
    for (int i = l ; i <= r ; ++ i)
        c[a[i]] = i;
    for (int i = l ; i <= r ; ++ i) {
        while (c[i] > i) {
            int j = a[c[i] - 1];
            oper.push_back(c[i] - 1);
            swap(a[c[i] - 1] , a[c[i]]);
            swap(c[j] , c[i]);
        }
    }
    return 1;
}
#define MID int mid = l + r >> 1
#define Left l , mid
#define Right mid + 1 , r
inline int id(int l , int r) {
    return l + r | l != r;
}
pair<int , int> t[N << 1];


pair<int , int> operator + (const pair<int , int>& A , const pair<int , int>& B) {
    return make_pair(min(A.first , B.first) , max(A.second , B.second));
}
void build(int l , int r) {
    if (l == r) {
        t[id(l , r)] = make_pair(L[l] , R[l]);
    } else {
        MID;
        build(Left);
        build(Right);
        t[id(l , r)] = t[id(Left)] + t[id(Right)];
    }
}
void update(int l , int r , int x , pair<int , int> w) {
    if (l == r) {
        t[id(l , r)] = w;
    } else {
        MID;
        if (x <= mid)
            update(Left , x , w);
        else
            update(Right , x , w);        
        t[id(l , r)] = t[id(Left)] + t[id(Right)];
    }
}
pair<int , int> get(int l , int r , int top , int bot) {
    if (top <= l && r <= bot)
        return t[id(l , r)];
    else {
        MID;
        if (bot <= mid)
            return get(Left , top , bot);
        else if (top > mid)
            return get(Right , top , bot);
        else
            return get(Left , top , bot) + get(Right , top , bot);
    }
}


void work() {
    int i , j , x , y;
    for (i = 1 ; i <= n ; ++ i) {
        //a[i] = n - i + 1;
        scanf("%d" , &a[i]);
    }
    for (i = 1 ; i <= n ; ++ i) {
        L[i] = i , R[i] = a[i];
        if (L[i] > R[i])
            swap(L[i] , R[i]);
    }
    build(1 , n);
    int res = n , cnt = 0;
    oper.clear();
    for (i = 1 , j = 0; i <= n ; ++ i) {
        int l = L[i] , r = R[i];
        while (1) {
            pair<int , int> Range = get(1 , n , l , r);
            if (Range.second > i)
                break;
            if (Range.first <= j)
                break;
            if (make_pair(l , r) == Range) {
                if (check(l , r))
                    -- res;
                j = r;
                break;
            }
            l = Range.first , r = Range.second;
            update(1 , n , i , Range);            
        }
    }
    printf("%d %d " , res , (int)oper.size());
    for (i = 0 ; i < oper.size() ; ++ i)
        printf(" %d" , oper[i]);
    puts("");
}

int main() {
    freopen("iota.in" , "r" , stdin);
    freopen("iota.out" , "w" , stdout);
    for (int i = 0 ; 1 << i < N ; ++ i)
        LOG[1 << i] = i;
    for (int i = 2 ; i < N ; ++ i)
        if (!LOG[i])
            LOG[i] = LOG[i - 1];
    while (scanf("%d" , &n) , n)
        work();
    return 0;
}
