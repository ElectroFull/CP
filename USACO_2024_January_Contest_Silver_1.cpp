#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2")

using namespace std;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;

struct Node {
  ll a, h;
};

void solve() {
  ll n, q, c;
  cin >> n >> q >> c;
  vector<ll> cowmpetency(n);
  for (auto &i : cowmpetency) {
    cin >> i;
  }
  vector<ll> crazy(n + 1);
  vector<Node> queries(q);
  for (ll i = 0; i < q; ++i) {
    ll a, h;
    cin >> a >> h;
    crazy[a] = h;
    queries[i] = {a, h};
  }
  sort(queries.begin(), queries.end(), [](auto a, auto b) {
    if (a.h == b.h)
      return a.a < b.a;
    return a.h < b.h;
  });
  for (ll i = 1; i <= n; ++i) {
    for (ll j = i + 1; j < crazy[i]; ++j) {
      if (crazy[j] != 0 && crazy[i] != crazy[j]) {
        cout << "-1";
        return;
      }
    }
  }
  vector<ll> nearest_zero_from_the_left(n, -1);
  for (ll i = 0; i < n; ++i) {
    if (!cowmpetency[i]) {
      nearest_zero_from_the_left[i] = i;
    } else if (i > 0)
      nearest_zero_from_the_left[i] = nearest_zero_from_the_left[i - 1];
  }
  vector<bool> solved(n + 1);
  ll last_id = 0, mx = 1;
  for (ll i = 0; i < q; ++i) {
    ll &a = queries[i].a, &h = queries[i].h;
    if (solved[h])
      continue;
    solved[h] = true;
    for (ll j = last_id; j < a; ++j) {
      mx = max(mx, cowmpetency[j]);
    }
    last_id = a;
    ll mid_max = 1;
    for (ll j = a; j < h - 1; ++j)
      mid_max = max(mid_max, cowmpetency[j]);
    if (mid_max > mx) {
      if (nearest_zero_from_the_left[a - 1] != -1) {
        cowmpetency[nearest_zero_from_the_left[a - 1]] = mid_max;
        mx = mid_max;
      } else {
        cout << "-1";
        return;
      }
    }
    if (!cowmpetency[h - 1]) {
      cowmpetency[h - 1] = mx + 1;
    } else {
      if (cowmpetency[h - 1] <= mx) {
        cout << "-1";
        return;
      }
    }
  }
  for (ll i = 0; i < n; ++i) {
    if (!cowmpetency[i])
      cowmpetency[i] = 1;
    if (cowmpetency[i] > c) {
      cout << "-1";
      return;
    }
  }
  vector<ll> pref(n + 1);
  for (ll i = 0; i < n; ++i) {
    pref[i + 1] = max(cowmpetency[i], pref[i]);
  }
  for (ll i = 0; i < q; ++i) {
    ll &a = queries[i].a, &h = queries[i].h;
    if (pref[a] >= cowmpetency[h - 1] || (pref[h - 1] > pref[a])) {
      cout << "-1";
      return;
    }
  }
  for (ll i = 0; i < n; ++i) {
    if (i + 1 < n) {
      cout << cowmpetency[i] << ' ';
    } else {
      cout << cowmpetency[i];
    }
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t != 0) {
      cout << '\n';
    }
  }
  return 0;
}