#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;

const int N = 1000005;

struct edge {
	int v, next;
}G[N];

int link[N], mcnt, d[N], a[N], fa[N];
LL res[N];

void addedge(int x, int y) {
	G[mcnt].v = y; G[mcnt].next = link[x]; link[x] = mcnt++;
}

int main() {
	int n;
	scanf("%d", &n);
	mcnt = 0;
	memset(link, -1, sizeof(link));
	memset(fa, -1, sizeof(fa));
	for (int i = 0; i < n; ++i) {
		int u;
		scanf("%d%d", &a[i], &u);
		if (u != -1) {
			addedge(u, i);
			++d[u];
		}
		fa[i] = u;
	}
	LL ans = 0;
	queue<int> q;
	for (int i = 0; i < n; ++i)
		if (d[i] == 0) q.push(i);
	while (!q.empty()) {
		int e = q.front();
		q.pop();
		vector<LL> foo;
		res[e] = 0;
		for (int i = link[e]; i != -1; i = G[i].next) {
			a[e] += a[G[i].v];
			foo.push_back(a[G[i].v]);
		}
		sort(foo.begin(), foo.end());
		int sz = foo.size();
		for (int i = 0; i < sz; ++i)
			res[e] += (LL)(sz - i - 1) * foo[i];
		if (fa[e] != -1) {
			--d[fa[e]];
			if (d[fa[e]] == 0) q.push(fa[e]);
		}
	}
	for (int i = 0; i < n; ++i) ans += res[i];
	printf("%lld\n", ans);
	return 0;
}