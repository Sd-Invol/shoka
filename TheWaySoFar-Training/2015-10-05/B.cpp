#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int N = 3005;

char d[N][3];
int x[N], y[N], b[N], c[N], mat[N][N];

int main() {
	int n;
	scanf("%d", &n);
	int numb = 0, numc = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%s", &x[i], &y[i], d[i]);
		b[numb++] = x[i];
		c[numc++] = y[i];
	}
	sort(b, b + numb);
	numb = unique(b, b + numb) - b;
	sort(c, c + numc);
	numc = unique(c, c + numc) - c;
	for (int i = 1; i <= n; ++i) {
		x[i] = lower_bound(b, b + numb, x[i]) - b;
		y[i] = lower_bound(c, c + numc, y[i]) - c;
		mat[x[i]][y[i]] = i;
	}
	set<int> tx[N], ty[N];
	for (int i = 1; i <= n; ++i) {
		tx[x[i]].insert(y[i]);
		ty[y[i]].insert(x[i]);
	}
	int ans = 0;
	for (int k = 1; k <= n; ++k) {
		set<int> sx[N], sy[N];
		for (int i = 0; i <= numb; ++i) sx[i] = tx[i];
		for (int i = 0; i <= numc; ++i) sy[i] = ty[i];
		int ax = x[k], ay = y[k], bx, by, foo = k;
		set<int>::iterator it;
		it = sx[ax].lower_bound(ay);
		sx[ax].erase(it);
		it = sy[ay].lower_bound(ax);
		sy[ay].erase(it);
		int res = 1;
		while (1) {
			bool mark = 0;
			if (d[foo][0] == 'v') {
				it =  sx[ax].upper_bound(ay);
				if (it != sx[ax].end()) {
					bx = ax;
					by = *it;
					foo = mat[bx][by];
					sx[ax].erase(it);
					it = sy[by].lower_bound(bx);
					sy[by].erase(it);
					mark = 1;
				}
			} else if (d[foo][0] == '^') {
				it = sx[ax].upper_bound(ay);
				if (it != sx[ax].begin()) {
					--it;
					bx = ax;
					by = *it;
					foo = mat[bx][by];
					sx[ax].erase(it);
					it = sy[by].lower_bound(bx);
					sy[by].erase(it);
					mark = 1;
				}
			} else if (d[foo][0] == '>') {
				it = sy[ay].upper_bound(ax);
				if (it != sy[ay].end()) {
					by = ay;
					bx = *it;
					foo = mat[bx][by];
					sy[ay].erase(it);
					it = sx[bx].lower_bound(by);
					sx[bx].erase(it);
					mark = 1;
				}
			} else {
				it = sy[ay].upper_bound(ax);
				if (it != sy[ay].begin()) {
					--it;
					by = ay;
					bx = *it;
					foo = mat[bx][by];
					sy[ay].erase(it);
					it = sx[bx].lower_bound(by);
					sx[bx].erase(it);
					mark = 1;
				}
			}
			if (mark) ++res;
			else break;
			swap(ax, bx);
			swap(ay, by);
		}
		ans = max(ans, res);
	}
	printf("%d\n", ans);
	return 0;
}

