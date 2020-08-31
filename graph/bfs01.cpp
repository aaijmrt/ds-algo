#include <bits/stdc++.h>
using namespace std;

const int lmt = 200005;
const long long inf = 1000000000000000L;

long long D[lmt];
deque<int> dq;
vector<pair<int, long long>> adj[lmt];

void bfs01(int u) {
	for (int i = 0; i < lmt; i++) {
		D[i] = inf;
	}
	dq.clear();

	D[u] = 0;
	dq.insert(u); 

	while(!dq.empty()) { 
		int top = *Q.begin();
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


int main() {

	return 0;
}