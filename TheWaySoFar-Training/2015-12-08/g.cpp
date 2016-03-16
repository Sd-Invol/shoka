#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 250005;
struct Point {
    int x , y , c;
    bool operator < (const Point &R) const {
        if (x != R.x)
            return x < R.x;
        return y < R.y;
    }
    Point operator - (const Point &R) const {
        return (Point){x - R.x , y - R.y , -1};
    }
    Point operator + (const Point &R) const {
        return (Point){x + R.x , y + R.y , -1};
    }
    LL operator ^ (const Point &R) const {
        return (LL)x * R.y - (LL)y * R.x;
    }
    LL len() const {
        return (LL)x * x + (LL)y * y;
    }
};
LL res;
int cnt[N] , belong[N];

int cmp(const int &A , const int &B) {
    return cnt[A] > cnt[B];
}
Point S[N] , T[N] , P[N];
Point U[N] , V[N];
int convex(vector<int> &p , Point *s) {
    int m = 0;
    for (int i = 0 ; i < (int)p.size() ; ++ i) {
        while (m > 1 && ((s[m - 1] - s[m - 2]) ^ (P[p[i]] - s[m - 2])) <= 0)
            m --;
        s[m ++] = P[p[i]];
    }
    int tmp = m;
    for (int i = (int)p.size() - 2 ; i >= 0 ; -- i) {
        while (m > tmp && ((s[m - 1] - s[m - 2]) ^ (P[p[i]] - s[m - 2])) <= 0)
            m --;
        s[m ++] = P[p[i]];
    }
    if (m > 1) -- m;
    s[m] = s[0];
    return m;
}

void work(vector<int> &A , vector<int> &B) {
    int n = convex(A , S);
    int m = convex(B , T);
    for (int i = 0 ; i < m ; ++ i) {
        T[i].x = -T[i].x;
        T[i].y = -T[i].y;
    } T[m] = T[0];
    for (int i = 0 ; i < n ; ++ i) {
        U[i] = S[i + 1] - S[i];
        swap(U[i].x , U[i].y);
        U[i].y = -U[i].y;
    }
    for (int i = 0 ; i < m ; ++ i) {
        V[i] = T[i + 1] - T[i];
        swap(V[i].x , V[i].y);
        V[i].y = -V[i].y;
    }
    for (int i = 0 , j = 0 ; i < n ; ++ i) {
        while (!((U[i] ^ V[j]) >= 0 && (U[i] ^ V[(j + m - 1) % m]) <= 0))
            j = (j + 1) % m;
        res = max(res , (S[i] + T[j]).len());
        res = max(res , (S[i] + T[(j + m - 1) % m]).len());        
    }
    for (int i = 0 , j = 0 ; i < m ; ++ i) {
        while (!((V[i] ^ U[j]) >= 0 && (V[i] ^ U[(j + n - 1) % n]) <= 0))
            j = (j + 1) % n;
        res = max(res , (T[i] + S[j]).len());
        res = max(res , (T[i] + S[(j + n - 1) % n]).len());        
    }   
}

void divide(vector<int> &p , vector<int> &c) {
    if (c.size() <= 1)
        return;
    int sum[2] = {0 , 0};
    vector<int> pl , pr , cl , cr;
    for (int i = 0 ; i < (int)c.size() ; ++ i) {
        if (sum[0] < sum[1]) {
            belong[c[i]] = 0;
            sum[0] += cnt[c[i]];
            cl.push_back(c[i]);
        } else {
            belong[c[i]] = 1;
            sum[1] += cnt[c[i]];
            cr.push_back(c[i]);
        }
    }
    for (int i = 0 ; i < (int)p.size() ; ++ i) {
        if (belong[P[p[i]].c])
            pr.push_back(p[i]);
        else
            pl.push_back(p[i]);
    }
    work(pl , pr);
    divide(pl , cl);
    divide(pr , cr);    
}

int n;
int main() {
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d%d%d" , &P[i].x , &P[i].y , &P[i].c);
        -- P[i].c;
        ++ cnt[P[i].c];
    }
    sort(P , P + n);
    vector<int> p , c;
    for (int i = 0 ; i < n ; ++ i)
        p.push_back(i);
    for (int i = 0 ; i < n ; ++ i)
        if (cnt[i])
            c.push_back(i);
    sort(c.begin() , c.end() , cmp);
    divide(p , c);
    printf("%lld\n" , res);
    return 0;
}
