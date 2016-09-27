#include <vector>
#include <sstream>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int _N = 1e8;
const int GQ = 1e9 + 7;

bool f[_N];
vector<int> getPrime(int N) {
  memset(f , 0 , sizeof(f));
  vector<int> prime;
  for (int i = 2 ; i <= N ; ++ i) {
    if (!f[i]) {
      prime.push_back(i);
    }
    for (auto &y : prime) {
      int x = y * i;
      if (x > N) break;
      f[x] = 1;
      if (i % y == 0) break;
    }
  }
  return prime;
}

vector<int> factorize(LL x) {
  vector<int> factor;
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

int power(int A , int B , int Q = GQ) {
  int res = 1;
  while (B) {
    if (B & 1) {
      res = (LL)res * A % Q;
    }
    A = (LL)A * A % Q;
  }
  return res;
}

int inverse(int x , int Q = GQ) {
  return x == 1 ? 1 : (LL)(Q - Q / x) * inverse(Q % x , Q) % Q;
}

void exgcd(int x , int y , int& a , int& b) {
  if (y == 0) {
    a = 1 , b = 0;
  } else {
    exgcd(y , x % y , b , a);
    b -= (x / y) * a;
  }
}

int modinverse(int x , int Q) {
  int a , b;
  exgcd(x , Q , a , b);
  assert((LL)a * x + (LL)b * Q == 1);
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
