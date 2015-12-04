#include <cstdio>
#include <cmath>

int main() {
	int n;
	while (~scanf("%d", &n)) {
		bool flag = 1;
		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			if (x == 0) continue;
			int d = sqrt(x);
			if (d * d != x) {
				flag = 0;
			}
		}
		if (flag) puts("Yes");
		else puts("No");
	}
	return 0;
}