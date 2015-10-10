#include <cstdio>
#include <cmath>
#include <cstdlib>

const double eps = 1e-15;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		double k;
		scanf("%lf", &k);
		if (k < eps) {
			puts("-1");
			continue;
		}
		if (fabs(k - 0.5) < eps) {
			printf("1002\n");
			continue;
		}
		double x = 0.25;
		int ans = 4;
		bool flag = 1;
		for (int i = 1; i <= 500; ++i) {
			if (fabs(k - x) < eps) {
				flag = 0;
				break;
				//continue;
			}
			if (k - x > eps) {
				k -= x;
				ans += 4;
			}
			else {
				break;
			}
			k *= 2.0;
			//x /= 2.0;
//			if (x < eps) break;
		}
		if (flag) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
}
