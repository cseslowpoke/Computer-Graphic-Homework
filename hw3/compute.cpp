#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#ifdef LOCAL    // =========== Local ===========
void dbg() { cerr << '\n'; }
template<class T, class ...U> void dbg(T a, U ...b) { cerr << a << ' ', dbg(b...); } 
template<class T> void org(T l, T r) { while (l != r) cerr << *l++ << ' '; cerr << '\n'; } 
#define debug(args...) (dbg("#> (" + string(#args) + ") = (", args, ")"))
#define orange(args...) (cerr << "#> [" + string(#args) + ") = ", org(args))
#else            // ======== OnlineJudge ========
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define debug(...) ((void)0)
#define orange(...) ((void)0)
#endif
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ll long long int
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pii pair <int, int>
#define X first
#define Y second
#define rep(i,a) for (ll i=0;i<a;i++)
#define IO ios::sync_with_stdio(false); cin.tie(0)

template<class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
const int mod = 1e9 + 7, N = 1 << 20, INF = 0x3f3f3f3f;
const double pi = acos(-1), eps = 1e-9;
void solve() {
  // for(int i = 0; i < 11; i++) {
  //   cout << '{'<< 1.3 * cos((float(i) * 5 - 25 - 90) / 180 * pi) << ',' << 1.3 * sin((float(i) * 5 - 25 - 90) / 180 * pi) << ',' << 0 << "},"<< '\n';
  // }
  // for(int i = 0; i < 11; i++) {
    // cout << '{'<< 0 << ',' << -1.2 + 2.4 * (float)i / 10 << ',' << 0 << "},"<< '\n';
  // }
  cout << float(1.4) / 4 << '\n';
}

signed main() {
  IO;
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
}