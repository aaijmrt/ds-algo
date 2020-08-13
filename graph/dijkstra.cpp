#include <bits/stdc++.h>
using namespace std;

const int lmt = 200005;
const long long inf = 1000000000000000L;

long long D[lmt];
set<pair<long long, int>> Q;
vector<pair<int, long long>> adj[lmt];
int p[lmt];

void dijkstra(int u) {

	for (int i = 0; i < lmt; i++) {
		D[i] = inf;
		p[i] = -1;
	}
	Q.clear();

	D[u] = 0;
	Q.insert(make_pair(0L, u)); 

	while(!Q.empty()) { 
		pair<long long, long long> top = *Q.begin();
		Q.erase(Q.begin());
		int v = top.second, d = top.first; 
		for (auto it: adj[v]) {
			int v2 = it.first;
			long long cost = it.second;
			if(D[v2] > D[v] + cost) {
				if(D[v2] != inf) 
					Q.erase(Q.find(make_pair(D[v2], v2)));
				D[v2] = D[v] + cost;
				p[v2] = v;
				Q.insert(make_pair(D[v2], v2));
			}
		}
	}
}

vector<int> ans;

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
	}

	dijkstra(0);
	if (D[n-1] == inf) {
		cout << "-1";
		return 0;
	}

	int x = n-1;
	while(x != -1) {
		ans.push_back(x+1);
		x = p[x];
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";

	return 0;
}

