#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long int llu;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define mem(a, v) memset(a, v, sizeof(a))
#define PI acos(-1)
#define S(a) scanf("%d",&a)
#define SL(a) scanf("%lld",&a)
#define S2(a, b) scanf("%d%d",&a,&b)
#define nl printf("\n")
#define deb(x) cout<<#x<<" : "<<x<<endl;
#define deb2(x, y) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<endl;
#define deb3(x, y, z) cout<<#x<<" : "<<x<<" | "<<#y<<" : "<<y<<" | "<<#z<<" : "<<z<<endl;
#define debv(x) {cout<<#x<<" : "<<endl; for(int ii =0; ii < x.size(); ii++) cout<<x[ii]<<" "; cout<<endl; }
#define debarr(x, xs) {cout<<#x<<" : "<<endl; for(int ii =0; ii < xs; ii++) cout<<x[ii]<<" "; cout<<endl; }
//auto T=clock(); 
//cout<<double(clock()-T)/CLOCKS_PER_SEC<<'\n';
const ll mod = 1000000007LL;
const int lmt = 100005;
const int logn = log2(lmt) + 3;

int jump[lmt][logn];
vector<int> adj[lmt];
int lev[lmt], siz[lmt];

int dfs(int u, int p, int l) {
	jump[u][0] = p;
	lev[u] = l;
	siz[u] = 1;
	for(int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if(v != p)
			siz[u] += dfs(v, u, l+1);
	}
	return siz[u];
}

int LCA(int x, int y) {
	if(x == y)
		return x;
	if(lev[x] < lev[y])
		swap(x, y);
	int tmp;
	for(tmp = 1; lev[x] >= (1<<tmp); tmp++);
	tmp--;
	for(int i = tmp; i >= 0; i--){
		if((lev[x] - (1<<i)) >= lev[y]){
			x = jump[x][i];
		}
	}

	if(x == y)
		return x;
	for(int i = tmp; i >= 0; i--) {
		if((jump[x][i] != 0) && (jump[x][i] != jump[y][i])){
			x = jump[x][i];
			y = jump[y][i];
		} 
	}
	return jump[x][0];
}

int getPar(int u, int ith) {
	int tmp, nlev = lev[u] - ith;
	for(tmp = 1; lev[u] >= (1<<tmp); tmp++);
	tmp--;
	for(int i = tmp; i >= 0; i--) {
		if((lev[u] - (1<<i)) >= nlev)
			u = jump[u][i];
	}
	return u;
}

int main(){
	int n;
	S(n);
	for(int i = 1; i < n; i++) {
		int u, v;
		S2(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}

	int tot = dfs(1, 0, 1);

	for(int i = 1; (1<<i) <= n; i++) {
		for(int u = 1; u <= n; u++)
			jump[u][i] = jump[jump[u][i-1]][i-1];
	}

	int q;
	S(q);
	while(q--) {
		int x, y;
		S2(x, y);
		if(x == y) {
			printf("%d\n", n);
			continue;
		}
		int lca = LCA(x, y);
		int dx = lev[x] - lev[lca];
		int dy = lev[y] - lev[lca];
		int d = dx + dy;
		if(d&1)
			printf("0\n");
		else if(dx == dy) {
			int px = getPar(x, dx-1);
			int py = getPar(y, dy-1);
			printf("%d\n", (n-siz[px]-siz[py]));
		}
		else {
			if(lev[x] < lev[y])
				swap(x, y);
			int p2 = getPar(x, d/2);
			int _p2 = getPar(x, d/2 - 1);
			printf("%d\n", (siz[p2] - siz[_p2]));
		}
	}

    return 0;
}