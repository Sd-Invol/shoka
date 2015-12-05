#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
const int N = 205;
int a[N] , pa[4][N] , s[4];
char name[4][40] = {
    "Takakamo Shizuno",
    "Atarashi Ako",
    "Matsumi Kuro",
    "Haramura Nodoka"
};
int End[] = {0,8,9,17,18,26,27,28,29,30,31,32,33};
int cnt[34];

bool dfs(int k) {
    if (k == 4)
        return 1;
    for (int i = 0 ; i < 34 ; ++ i) {
        if (cnt[i] >= 3) {
            cnt[i] -= 3;
            if (dfs(k + 1))
                return 1;
            cnt[i] += 3;            
        }
        if (i < 27 && i % 9 < 7) {
            if (cnt[i] && cnt[i + 1] && cnt[i + 2]) {
                -- cnt[i] , -- cnt[i + 1] , -- cnt[i + 2];
                if (dfs(k + 1))
                    return 1;
                ++ cnt[i] , ++ cnt[i + 1] , ++ cnt[i + 2];
            }
        }
    }
    return 0;
}

bool check(int *S , int n) {
    memset(cnt , 0 , sizeof(cnt));
    for (int i = 0 ; i < n ; ++ i)
        ++ cnt[S[i]];
    int d = 0;
    for (int i = 0 ; i < 34 ; ++ i)
        if (cnt[i] > 1)
            ++ d;
    if (d >= 7)
        return 1;
    int mx = 0; d = 0;
    for (int i = 0 ; i < 13 ; ++ i) {
        if (cnt[End[i]])
            ++ d;
        if (cnt[End[i]] > 1)
            mx = 1;
    }
    if (mx && d == 13)
        return 1;
    for (int i = 0 ; i < 34 ; ++ i) {
        if (cnt[i] >= 2) {
            cnt[i] -= 2;
            if (dfs(0))
                return 1;
            cnt[i] += 2;
        }
    }
    return 0;
}

void work() {
    s[0] = s[1] = s[2] = s[3] = 0;
    for (int i = 0 ; i < 136 ; ++ i) {
        char t[5];
        scanf("%s" , t);
        if (isdigit(*t)) {
            int x = *t - '1';
            if (*(t + 1) == 'N')
                a[i] = x;
            if (*(t + 1) == 'S')
                a[i] = x + 9;
            if (*(t + 1) == 'B')
                a[i] = x + 18;
        } else {
            if (!strcmp(t , "EH")) a[i] = 27;
            if (!strcmp(t , "SH")) a[i] = 28;
            if (!strcmp(t , "WH")) a[i] = 29;
            if (!strcmp(t , "NH")) a[i] = 30;
            if (!strcmp(t , "rH")) a[i] = 31;
            if (!strcmp(t , "wH")) a[i] = 32;
            if (!strcmp(t , "gH")) a[i] = 33;
        }
        if (i < 48) {
            int w = i / 4 % 4;
            //printf("%d\n" , w);
            pa[w][s[w] ++] = a[i];
        } else {            
            int w = i % 4;            
            //printf("%d\n" , w);
            pa[w][s[w] ++] = a[i];
        }
    }
    pair<int , int> res(1 << 30 , -1);
    for (int i = 0 ; i < 4 ; ++ i) {
        int l = 14 , r = 35 , m;
        while (l < r) {
            m = l + r >> 1;
            if (check(pa[i] , m))
                r = m;
            else
                l = m + 1;
        }
        res = min(res , make_pair(r , i));
    }
    static int ca = 0;
    printf("For round %d, " , ++ ca);
    if (res.first <= 34)
        printf("%s wins at turn %d.\n" , name[res.second] , res.first - 13);
    else
        printf("a Draw Hand occurs.\n");
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}