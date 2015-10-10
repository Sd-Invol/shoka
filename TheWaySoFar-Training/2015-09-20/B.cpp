#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>
#include <set>
#include <queue>
using namespace std;
typedef long long LL;
const int N = 20005;
int n , m;
char str[N];
char sl[N] , sr[N];
int tl , tr , tc , dir , len;
char cb[N];
char paste[N];
void work() {
    scanf("%d%s" , &m , str);
    n = strlen(str);
    bool mode = 0; // 0 insert 1 overw
    bool copy = 0;
    len = 0;
    // dir 0 -> left , 1 -> right
    tl = 0 , tr = 0 , tc = 0;
    for (int i = 0 ; i < n ; ++ i) {
        if (copy) {
            if (str[i] != 'L' && str[i] != 'R' && str[i] != 'D') {
                if (dir == 0) {
                    for (int k = 0 ; k < tc ; ++ k) {
                        sr[tr ++] = cb[k];
                    }
                } else {
                    for (int k = 0 ; k < tc ; ++ k) {
                        sl[tl ++] = cb[k];
                    }
                }
                if (str[i] != 'C')
                    copy = 0 , tc = 0;
            }
        }

        if (islower(str[i])) {
            if (!mode) {
                if (tl + tr < m)
                    sl[tl ++] = str[i];
            } else {
                if (tr) {
                    -- tr;
                    sl[tl ++] = str[i];
                } else {
                    if (tl + tr < m)
                        sl[tl ++] = str[i];            
                }
            }
        } else if (str[i] == 'L') {
            if (copy) {
                if (tl) {
                    if (!tc || dir == 0) {
                        -- tl;
                        if (tc == 0)
                            dir = 0;
                        cb[tc ++] = sl[tl];
                    } else {
                        -- tc;
                        sr[tr ++] = cb[tc];
                    }
                } else {
                    if (dir == 1 && tc) {
                        -- tc;
                        sr[tr ++] = cb[tc];
                    }
                }
            } else {
                if (tl) {
                    -- tl;
                    sr[tr ++] = sl[tl];
                }
            }
        } else if (str[i] == 'R') {
            if (copy) {
                if (tr) {
                    if (!tc || dir == 1) {
                        -- tr;
                        if (tc == 0)
                            dir = 1;
                        cb[tc ++] = sr[tr];
                    } else {
                        -- tc;
                        sl[tl ++] = cb[tc];
                    }
                } else {
                    if (dir == 0 && tc) {
                        -- tc;
                        sl[tl ++] = cb[tc];
                    }
                }
            } else {
                if (tr) {
                    -- tr;
                    sl[tl ++] = sr[tr];
                }
            }
        } else if (str[i] == 'B') {
            if (tl) {
                -- tl;
            }
        } else if (str[i] == 'D') {
            if (copy) {
                tc = 0;
                copy = 0;
            } else {
                if (tr) {
                    -- tr;
                }
            }
        } else if (str[i] == 'S') {
            mode ^= 1;
        } else if (str[i] == 'C') {
            if (!copy) {
                tc = 0;
                dir = 0;
                copy = 1;
            } else {
                len = tc;
                if (dir) {
                    for (int k = 0 ; k < len ; ++ k)
                        paste[k] = cb[k];
                } else {
                    for (int k = 0 ; k < len ; ++ k)
                        paste[k] = cb[len - k - 1];
                }
                copy = 0;
            }
        } else if (str[i] == 'V') {
            if (!mode) {
                if (tl + tr + len <= m) {
                    for (int k = 0 ; k < len ; ++ k)
                        sl[tl ++] = paste[k];
                }
            } else {
                int delta = min(tr , len);
                if (tl + tr - delta + len <= m) {
                    while (delta --)
                        -- tr;
                    for (int k = 0 ; k < len ; ++ k)
                        sl[tl ++] = paste[k];
                }
            }
        } else {
            while (1);
        }

    }
    if (copy) {
        if (dir == 0) {
            for (int k = 0 ; k < tc ; ++ k) {
                sr[tr ++] = cb[k];
            }
        } else {
            for (int k = 0 ; k < tc ; ++ k) {
                sl[tl ++] = cb[k];
            }
        }
    }
    
    if (tl + tr == 0)
        puts("NOTHING");
    else {
        for (int i = 0 ; i < tl ; ++ i)
            putchar(sl[i]);
        for (int i = tr - 1 ; i >= 0 ; -- i)
            putchar(sr[i]);
        puts("");
    }
}


int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
