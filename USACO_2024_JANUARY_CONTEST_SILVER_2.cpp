#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2")

using namespace std;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;

constexpr ll N = 1e5 + 5;

ll dp[N];
ll ans = 0;

void dfs(ll v, ll p, vector<vector<ll>> &graph, vector<ll> &val) {
  if (graph[v].size() == 1 && v != 1) {
    dp[v] = 1;
  }
  for (auto &u : graph[v]) {
    if (u == p)
      continue;
    dfs(u, v, graph, val);
    dp[v] += dp[u];
  }
  ll can_fulfill = min(val[v], dp[v]);
  dp[v] -= can_fulfill;
  ans += can_fulfill;
}

void solve() {
  ll n;
  cin >> n;
  vector<ll> potions(n);
  for (auto &i : potions)
    cin >> i;
  vector<vector<ll>> graph(n + 1);
  for (ll i = 0; i < n - 1; ++i) {
    ll u, v;
    cin >> u >> v;
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  ll cnt = 0;
  for (ll i = 2; i <= n; ++i) {
    if (graph[i].size() == 1) {
      ++cnt;
    }
  }
  vector<ll> val(n + 1);
  for (ll i = 0; i < cnt; ++i)
    ++val[potions[i]];
  dfs(1, 1, graph, val);
  cout << ans;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
    if (t != 0) {
      cout << '\n';
    }
  }
  return 0;
}