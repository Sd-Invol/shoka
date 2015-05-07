#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int a, m, p, q, r, s;

LL solve(LL L, LL R, int numm, vector<pair<int, LL> > &ver1) {
    vector<LL> ver;
    ver.resize(numm + 1);
    LL fac = 1;
    for (int i = 1; i <= numm; ++i) fac *= m;
    LL C = 0;
    LL ans = numm;
    for (int i = 0; i <= numm; ++i) {
        if (C >= L && C <= R) {
            ver[i] = 0;
        }
        else {
            LL p = (L - C) / fac;
            if (C + p * fac >= L) {
                C += p * fac;
                ver[i] = p;
            }
            else if (C + (p + 1) * fac <= R) {
                C += (p + 1) * fac;
                ver[i] = p + 1;
            }
            else {
                C += p * fac;
                ver[i] = p;
            }
        }
        fac /= m;
    }
    assert(L <= C && R >= C);
    for (int i = 0; i <= numm; ++i) ans += ver[i];
    vector<pair<int, LL> > ways;
    for (int i = 0; i < ver.size(); ++i) {
        if (i != 0) {
            if (!ways.empty() && ways.back().first == 2)
                ways.back().second++;
            else ways.push_back(make_pair(2, 1));
        }
        if (ver[i] != 0)
            ways.push_back(make_pair(1, ver[i]));
    }
    ver1 = ways;
    //printf("%d %lld %lld %lld %lld\n", numm, L, R, ans, C);
    return ans;
}

int main() {
    int ca = 0;
    while (scanf("%d%d%d%d%d%d", &a, &m, &p, &q, &r, &s), a || m || p || q || r || s) {
        int numm = 0;
        LL np = p, nq = q;
        vector<pair<int, LL> > ver;
        printf("Case %d:", ++ca);
        if (q > s) {
            puts(" impossible");
            continue;
        }
        LL ans = 1LL << 50;
        int flag = 0;
        while (1) {
            LL L1, R1;
            if (np >= r) L1 = 0;
            else L1 = (r - np + a - 1) / a;
            R1 = (s - np) / a;
            LL L2, R2;
            if (nq >= r) L2 = 0;
            else L2 = (r - nq + a - 1) / a;
            R2 = (s - nq) / a;
            LL L = max(L1, L2), R = min(R1, R2);
            if (L <= R) {
                vector<pair<int, LL> > ver1;
                LL ret = solve(L, R, numm, ver1);
                if (ret < ans) {
                    ans = ret;
                    ver = ver1;
                    flag = 1;
                }
                else if (ret == ans) {
                    int boo = 0;
                    for (int i = 0; i < ver.size(); ++i)
                        if (ver[i] != ver1[i]) {
                            if (ver[i].first != ver1[i].first) {
                                if (ver[i].first > ver1[i].first) boo = 1;
                            }
                            else {
                                if (ver[i].first == 1) {
                                    if (ver1[i].second > ver[i].second) boo = 1;
                                }
                                else {
                                    if (ver1[i].second < ver[i].second) boo = 1;
                                }
                            }
                            break;
                        }
                    if (boo) ver = ver1;
                }
            }
            ++numm;
            np *= m, nq *= m;
            if (nq > s || m == 1) break;
        }
        if (!flag) {
            puts(" impossible");
            continue;
        }
        else if (ans == 0) {
            puts(" empty");
            continue;
        }
        for (int i = 0; i < ver.size(); ++i)
            printf(" %lld%c", ver[i].second, (ver[i].first == 1) ? 'A' : 'M');
        puts("");
    }
    return 0;
}
