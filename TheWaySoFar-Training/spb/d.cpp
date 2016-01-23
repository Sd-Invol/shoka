#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1e6 + 5;
const int M = 1e6 + 5;

int a[N];
int prime[M], bo[N];
vector<int> seq[M];
pair<int, int> queue[N];

void updata(pair<int, int> &x, pair<int, int> y) {
    if (x.second - x.first < y.second - y.first) {
        x = y;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i < M; ++i)
        if (!prime[i]) {
            for (int j = i; j < M; j += i) {
                prime[j] = i;
            }
        }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        for (int j = a[i]; j != 1; j /= prime[j]) {
            seq[prime[j]].push_back(i);
        }
    }
    pair<int, int> ans = make_pair(0, 0);
    for (int i = 2; i < M; ++i) {
        if (seq[i].empty()) continue;
        sort(seq[i].begin(), seq[i].end());
        seq[i].erase(unique(seq[i].begin(), seq[i].end()), seq[i].end());
        int m = seq[i].size();
        for (int j = m - 1, p = -(1 << 30); j >= 0; --j) {
            int t = j + 1;
            t = t - (seq[i][j] - t);
            if (t <= p) bo[j] = 0;
            else {
                bo[j] = 1;
                p = t;
            }
        }
        int head = 1, tail = 0;
        for (int j = 0; j < m; ++j) {
            int pre = j - (seq[i][j] - 1 - j);
            if (head > tail || queue[tail].first > pre)
                queue[++tail] = make_pair(pre, j);
            if (!bo[j]) continue;
            ++pre;
            while (head <= tail && pre - queue[head].first < 0) ++head;
            if (head > tail) continue;
            int id = queue[head].second;
            pre -= queue[head].first;
            int L = seq[i][id], R = seq[i][j];
            int Lnum = 0, Rnum = 0;
            if (id > 0) Lnum = seq[i][id] - seq[i][id - 1] - 1;
            else Lnum = seq[i][id] - 1;
            if (j + 1 < m) Rnum = seqi][j + 1] - seq[i][j] - 1;
            else Rnum = n - seq[i][j];
            int tmp = min(pre, Lnum);
            L -= tmp;
            pre -= tmp;
            tmp = min(Rnum, pre);
            pre -= tmp;
            R += tmp;
            updata(ans, make_pair(L, R));
        }
    }
    
    printf("%d %d\n", ans.first, ans.second);
    return 0;
}
