#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 10005;

int mark[1005];

vector<pair<int, int> > ver[N];

int n, k, f[N];

void work(int id, int x, int a, int b, int c) {
	memset(mark, -1, sizeof(mark));
	mark[x] = 0;
	int cnt = 0;
	while (1) {
		++cnt;
		int y = (a * x + b) % c;
		if (mark[y] != -1) {
			break;
		}
		mark[y] = cnt;
		x = y;
	}
	cnt = 0;
	for (int i = 999; i >= 0; --i)
		if (mark[i] != -1) {
			++cnt;
			if (cnt == 1) {
				ver[id].push_back(make_pair(i, mark[i]));
				continue;
			}
			if (ver[id][0].first % k == i % k) {
				--cnt;
				continue;
			}
			ver[id].push_back(make_pair(i, mark[i]));
			if (cnt == 2) break;
		}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		int x, a, b, c;
		scanf("%d%d%d%d", &x, &a, &b, &c);
		work(i, x, a, b, c);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += ver[i][0].first;
		f[i] = ver[i][0].second;
	}
	if (ans % k == 0) {
		int tmp = 1e9, tt;
		for (int i = 1; i <= n; ++i) {
			if (ver[i].size() > 1) {
				if (ver[i][0].first - ver[i][1].first < tmp) {
					tmp = ver[i][0].first - ver[i][1].first;
					tt = i;
				}
			}
		}
		if (tmp == 1e9) {
			puts("-1");
		} else {
			printf("%d\n", ans - tmp);
			for (int i = 1; i <= n; ++i) {
				if (i == tt) printf("%d", ver[i][1].second);
				else
				printf("%d", ver[i][0].second);
				if (i == n) puts("");
				else printf(" ");
			}
		}
	} else {
		printf("%d\n", ans);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", f[i], " \n"[i == n]);
	}
	return 0;
}

