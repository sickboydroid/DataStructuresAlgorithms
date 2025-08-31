#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#ifdef SICKBOY
#include "./libs/head.h"
#else
static const auto beforeMain = []() -> int {
  ios::sync_with_stdio(0);
  cin.tie(0);
  return 0;
}();
#endif

template <class C, class T>
constexpr bool has(const C& c, const T& e) {
  return c.find(e) != c.end();
}

using ull = unsigned long long;
using ll = long long;
using ui32 = unsigned;
using i32 = int;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using pii = array<int, 2>;
using pll = array<ll, 2>;
using tiii = array<int, 3>;
using tlll = array<ll, 3>;
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define nl "\n"
#define popcount __builtin_popcount
#define popcountll __builtin_popcountll
#define pb push_back
#define eb emplace_back
#define mp(x, y) (pii{(x), (y)})
const int MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 2e9;
const ll LINF = 9e18;
/************************************/

pii dio(int a, int b) {
  bool hasSwapped = false;
  if (a > b)
    swap(a, b), hasSwapped = true;

  if (a == 1) {
    if (hasSwapped)
      return {0, 1};
    return {1, 0};
  }
  vector<pii> coffs;
  while (true) {
    int q = b / a;
    int r = b % a;
    b = a, a = r;
    coffs.pb({1, -q});
    if (a == 1)
      break;
  }

  for (int i = sz(coffs) - 1; i >= 1; i--) {
    auto& c = coffs[i];
    auto& p = coffs[i - 1];
    p[0] *= c[1], p[1] *= c[1];
    c[1] = c[0] + p[1];
    c[0] = p[0];
    p = c;
  }

  if (hasSwapped)
    return {coffs[0][0], coffs[0][1]};
  return {coffs[0][1], coffs[0][0]};
}

pii solve(int a, int b, int c) {
  int signA = a >= 0 ? 1 : -1;
  int signB = b >= 0 ? 1 : -1;
  a = abs(a);
  b = abs(b);
  int g = gcd(a, b);
  if ((c % g) != 0) {
    cout << "gcd(a, b) | c for solution to exist" << nl;
    return {-1, -1};
  }

  pii res = dio(a / g, b / g);
  return {res[0] * c / g * signA, res[1] * c / g * signB};
}

int getModInvBrute(int x, int mod) {
  for (int i = 0; i < mod; i++) {
    if (((i * x) % mod) == 1)
      return i;
  }
  return -1;
}

int getModInv(int x, int mod) {
  if (gcd(x, mod) == 1) {
    // cout << solve(x, -mod, 1) << nl;
    int res = solve(x, -mod, 1)[0];
    res += (-res / mod + 1) * mod;
    return res % mod;
  }
  return -1;
}

void runTestCases() {
  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> dist(0, 1);

  for (int i = 1; i < 50; i++) {
    for (int j = 1; j < 50; j++) {
      for (int c = 1; c < 50; c++) {
        bool val1 = dist(rng);
        bool val2 = dist(rng);
        bool val3 = dist(rng);
        int a = i, b = j;
        if (val1)
          a *= -1;
        if (val2)
          b *= -1;
        if (val3)
          c *= -1;
        if ((c % gcd(a, b)) != 0)
          continue;
        auto [x, y] = solve(a, b, c);
        if (a * x + b * y == c) {
          cout << a << "(" << y << ")" << " + " << b << "(" << x << ")" << " = " << c << nl;
        } else {
          cout << "FAILED" << nl;
          return;
        }
      }
    }
  }
  cout << "all tests passed" << nl;
}

void runTestInput() {
  int a, b, c;
  cin >> a >> b >> c;
  auto [x, y] = solve(a, b, c);
  if (a * x + b * y == c) {
    cout << a << "(" << x << ")" << " + " << b << "(" << y << ")" << " = " << c << nl;
  } else {
    cout << "Failed to find any valid solution, is the equation correct?" << nl;
  }
}

int runTestCaes_Mod() {
  for (int i = 2; i < 1000; i++) {
    for (int j = 2; j < i; j++) {
      if (getModInv(i, j) != getModInvBrute(i, j)) {
        cout << "Failed: " << i << " inv mod " << j << nl;
        cout << getModInv(i, j) << " " << getModInvBrute(i, j) << nl;
        break;
      }
    }
  }
}

int main() {
  // call the function whose tests you want to run
}
