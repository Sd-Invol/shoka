#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 10005, M = 100005;

struct edge {
	int v, next;
}G[M];

int link[N], mcnt, din[N], dout[N], p[N];
double a[N];

void addedge(int x, int y) {
	G[mcnt].v = y; G[mcnt].next = link[x]; link[x] = mcnt++;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d%d", &p[i], &x);
		a[i] = x;
	}
	memset(link, -1, sizeof(link));
	mcnt = 0;
	while (k--) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		++din[y];
		++dout[x];
	}
	int X, Y, Z;
	scanf("%d%d%d", &X, &Y, &Z);
	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (din[i] == 0) q.push(i);
	while (!q.empty()) {
		int e = q.front();
		q.pop();
		if (e == X) a[e] += Y;
		double tmp = 0;
		if (a[e] > p[e]) {
			double foo;
			foo = a[e] - p[e];
			a[e] = p[e];
			tmp = foo / dout[e];
		}
		for (int i = link[e]; i != -1; i = G[i].next) {
			a[G[i].v] += tmp;
			--din[G[i].v];
			if (din[G[i].v] == 0) q.push(G[i].v);
		}
	}
	printf("%.10f\n", a[Z]);
	return 0;
}