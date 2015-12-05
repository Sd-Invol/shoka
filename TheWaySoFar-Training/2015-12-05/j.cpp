#include <cstdio>
#include <map>

using namespace std;

typedef long long LL;

LL a, b;

LL ans, tans;

LL abs(LL x) {
	if (x > 0) return x;
	else return -x;
}

void work(LL x) {
	map<LL, LL> f;
	f[x] = 1;
	LL cnt = 1;
	LL tmp = x;
	while (1) {
		++cnt;
		LL y = a / x + b;
		if (y == 0) break;
		if (f[y] != 0) {
			if (cnt - f[y] > ans) {
				ans = cnt - f[y];
				tans = tmp;
			}
			break;
		}
		f[y] = cnt;
		if (a % y != 0) break;
		x = y;
	}
}

int main() {
	scanf("%lld%lld", &a, &b);
	for (LL i = 1; i * i <= abs(a); ++i)
		if (a % i == 0) {
			work(i);
			work(-i);
			work(abs(a) / i);
			work(-abs(a) / i);
		}
	printf("%lld\n", ans);
	if (ans != 0) printf("%lld\n", tans);
	return 0;
}

