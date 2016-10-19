#include <vector>
#include <cmath>
#include <sstream>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int _N = 1e8;
const int GQ = 1e9 + 7;

bool _f[_N + 1];
vector<int> getPrime(int N) {
  memset(_f , 0 , sizeof(_f));
  _f[0] = _f[1] = 1;
  vector<int> prime;
  for (int i = 2 ; i <= N ; ++ i) {
    if (!_f[i]) {
      prime.push_back(i);
    }
    for (auto &y : prime) {
      int x = y * i;
      if (x > N) break;
      _f[x] = 1;
      if (i % y == 0) break;
    }
  }
  return prime;
}
bool isPrime(LL x) {
  for (int i = 2 ; (LL)i * i <= x ; ++ i) {
    if (x % i == 0) {
      return 0;
    }
  }
  return 1;
}

vector<LL> factorize(LL x) {
  vector<LL> factor;
  for (int i = 2 ; (LL)i * i <= x ; ++ i) {
    while (x % i == 0) {
      x /= i;
      factor.push_back(i);
    }
  }
  if (x > 1) {
    factor.push_back(x);
  }
  return factor;
}

LL power(LL A , LL B , LL Q = GQ) {
  int res = 1;
  while (B) {
    if (B & 1) {
      res = res * A % Q;
    }
    A = A * A % Q;
    B >>= 1;
  }
  return res;
}
LL getPhi(LL x) {
  LL y = x;
  for (int i = 2 ; (LL)i * i <= x ; ++ i) {
    if (x % i == 0) {
      y /= i , y *= i - 1;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) y /= x , y *= x - 1;
  return y;
}


int inverse(int x , int Q = GQ) {
  return x == 1 ? 1 : (LL)(Q - Q / x) * inverse(Q % x , Q) % Q;
}

template<typename T> void exgcd(T x , T y , T& a , T& b) {
  if (y == 0) {
    a = 1 , b = 0;
  } else {
    exgcd(y , x % y , b , a);
    b -= (x / y) * a;
  }
}

template<typename T> T modinverse(T x , T Q) {
  T a , b;
  exgcd(x , Q , a , b);
  //assert((LL)a * x + (LL)b * Q == 1);
  return (a % Q + Q) % Q;
}

pair<LL , LL> mergemodulo(pair<LL , LL> A , pair<LL , LL> B) {
  if (A.first < B.first) {
    swap(A , B);
  }
  LL a = A.first;
  LL b = (B.second - A.second % B.first + B.first) % B.first;
  LL c = B.first , d = __gcd(a , c);
  if (b % d != 0) {
    return make_pair(0 , 0);
  } else {
    a /= d , b /= d , c /= d;
    LL q = modinverse(a % c , c);
    b = b * q % c;
    LL mod = A.first * c;
    LL rest = (A.first * b + A.second) % mod;
    return make_pair(mod , rest);
  }
}

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        print(-x);
    }
    if (x > 9) {
        print(x / 10);
    }
    putchar(x % 10 + '0');
}

ostream& operator << (ostream& output, const __int128& v) {
  print(v);
  return output;
};


template <typename T> string print_array(const vector<T> &V) {
  ostringstream os;
  os << "{";
  for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter)
    os << '\"' << *iter << "\", ";
  os << "}";
  return os.str();
}

template <typename T> ostream& operator << (ostream& output, const vector<T>& v) {
  cout << print_array(v);
  return output;
};

template <typename T1, typename T2> string print_pair(const pair<T1 , T2> &V) {
  ostringstream os;
  os << "(" << V.first << ", " << V.second << ")";
  return os.str();
}

template <typename T1, typename T2> ostream& operator << (ostream& output, const pair<T1 , T2>& v) {
  cout << print_pair(v);
  return output;
};
