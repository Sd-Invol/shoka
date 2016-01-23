#include <cstdio>

char a[5][5];

bool win() {
	for (int i = 0; i < 3; ++i) {
		bool flag = 1;
		for (int j = 0; j < 3; ++j)
			if (a[i][j] != 'x') {
				flag = 0;
				break;
			}
		if (flag) return true;
	}
	for (int j = 0; j < 3; ++j) {
		bool flag = 1;
		for (int i = 0; i < 3; ++i)
			if (a[i][j] != 'x') {
				flag = 0;
				break;
			}
		if (flag) return true;
	}
	if (a[0][0] == 'x' && a[1][1] == 'x' && a[2][2] == 'x') return true;
	if (a[2][0] == 'x' && a[1][1] == 'x' && a[0][2] == 'x') return true;
	return false;
}

void read() {
	scanf("%s%s%s", a[0], a[1], a[2]);
}

bool end() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (a[i][j] != 'x') return false;
	return true;
}

void print() {
	printf("%s\n%s\n%s\n", a[0], a[1], a[2]);
	fflush(stdout);
}

bool full() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (a[i][j] == '.') return false;
	return true;
}

bool recur(char player) {
	if (win() && player == 'o') return false;
	if (full() && player == 'o') return true;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			if (a[i][j] == '.') {
				a[i][j] = player;
				if (player == 'o') {
					if (!recur('x')) {
						a[i][j] = '.';
						return true;
					}
				} else {
					if (!recur('o')) {
						a[i][j] = '.';
						return true;
					}	
				}
				a[i][j] = '.';
			}
		}
	return false;
}

int main() {
	while (1) {
		read();
		if (end()) break;
		bool ans = 0;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j)
				if (a[i][j] == '.') {
					a[i][j] = 'x';
					if (!recur('o')) {
						print();
						ans = 1;
						break;
					}
					a[i][j] = '.';
				}
			if (ans) break;
		}
	}
	return 0;
}

