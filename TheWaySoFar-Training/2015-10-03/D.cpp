#include <cstdio>
#include <map>

using namespace std;

const int N = 1000005;

int x[N], k[N];
map<int, int> a;

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n + 1; ++i) scanf("%d", &x[i]);
	int foo = k;
	k = x[n + 1] / k;
	for (int i = 1; i <= n; ++i)
		++a[x[i] % k];
	int ans = 0;
	for (map<int, int>::iterator it = a.begin(); it != a.end(); ++it)
		if (it->second == foo) ans = 1;
	printf("%d\n", ans);
	return 0;
}

