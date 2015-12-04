#include <cstdio>

typedef long long LL;

int main() {
	LL x, y, a, b;
	scanf("%I64d%I64d", &x, &y);
	scanf("%I64d%I64d", &a, &b);
	LL fooa = x / a, foob = y / b;
	LL ans = fooa * foob;
	bool flag = 0;
	bool mark = 0;
	if (x % a != 0) {
		mark = 1;
		LL ta = a / (x % a);
		LL tmp = (foob + ta - 1) / ta;
		ans += tmp;
		if (tmp * ta != foob) flag = 1;
	}
	if (y % b != 0) {
		mark = 1;
		LL tb = b / (y % b);
		LL tmp = (fooa + tb - 1) / tb;
		ans += tmp;
		if (tmp * tb != fooa) flag = 1;
	}
	if (!flag && mark) ++ans;
	printf("%I64d\n", ans);
	return 0;
}