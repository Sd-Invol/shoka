#include <cstdio>

const int N = 1000005;

int p[N];

typedef long long LL;

bool check(int x) {
	int tmp = x, foo = 0;
	while (tmp) {
		foo *= 10;
		foo += tmp % 10;
		tmp /= 10;
	}
	if (p[x] == 0 && p[foo] == 0 && foo != x) return true;
	return false;
}

int main() {
	p[1] = 1;
	for (int i = 2; i <= 1000000; ++i) {
		if (p[i] == 0) {
			for (LL j = (LL)i * i; j <= 1000000; j += i) {
				p[j] = 1;
			}
		}
	}
	int n;
	scanf("%d", &n);
	int cnt = 0, ans = -1;
	for (int i = 1; i <= 1000000; ++i)
		if (check(i)) {
			++cnt;
			if (cnt == n) {
				ans = i;
				break;
			}
		}
	printf("%d\n", ans);
	return 0;
}

