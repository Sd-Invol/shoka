#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int INF = ~0u >> 1, M = 505;

struct edge {
	int v, next;
}G[M * M];

int num, res, ans, co[M], X[M * M], Y[M * M], d[M], mat[M][M], mcnt, link[M];

void addedge(int x, int y) {
	G[mcnt].v = y; G[mcnt].next = link[x]; link[x] = mcnt++;
}

void dfs(int x) {
	if (x == num + 1) {
		ans = min(ans, res);
		return;
	}
	int tmp = 0;
	for (int i = 1; i <= num; ++i) {
		if (!co[i] && d[i] > d[tmp]) {
			tmp = i;
		}
	}
	if (tmp == 0) {
		ans = min(ans, res);
		return;
	} else {
		++co[tmp];
		++res;
		for (int i = link[tmp]; i != -1; i = G[i].next) 
			if (!co[G[i].v]) {
				--d[G[i].v];
				--d[tmp];
			}
		dfs(x + 1);
		for (int i = link[tmp]; i != -1; i = G[i].next)
			if (!co[G[i].v]) {
				++d[G[i].v];
				++d[tmp];
			}
		--co[tmp];
		--res;
		for (int i = link[tmp]; i != -1; i = G[i].next) {
			++co[G[i].v];
			if (co[G[i].v] == 1) {
				for (int j = link[G[i].v]; j != -1; j = G[j].next) {
					if (!co[G[j].v]) {
					       --d[G[j].v];
					       --d[G[i].v];
				       }
			       }
				++res;
			}
		}
		dfs(x + 1);
		for (int i = link[tmp]; i != -1; i = G[i].next) {
			--co[G[i].v];
			if (co[G[i].v] == 0) {
				for (int j = link[G[i].v]; j != -1; j = G[j].next) {
					if (!co[G[j].v]) {
						++d[G[j].v];
						++d[G[i].v];
					}
				}
			--res;
			}
		}
	}
}

int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		memset(co, 0, sizeof(co));
		res = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &X[i], &Y[i]);
			if (X[i] > Y[i]) swap(X[i], Y[i]);
		}
		memset(d, 0, sizeof(d));
		num = min(n, 30);
		mcnt = 0;
		memset(link, -1, sizeof(link));
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < m; ++i) {
			if (X[i] == Y[i] && co[X[i]] == 0 && mat[X[i]][Y[i]] == 0) {
				co[X[i]] = 1;
				++res;
			}
		}
		for (int i = 0; i < m; ++i) {
			if (co[X[i]] == 0 && co[Y[i]] == 0 && mat[X[i]][Y[i]] == 0)  {
				mat[X[i]][Y[i]] = 1;
				mat[Y[i]][X[i]] = 1;
				addedge(X[i], Y[i]);
				addedge(Y[i], X[i]);
				++d[X[i]];
				++d[Y[i]];
			}
		}
		ans = INF;
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}