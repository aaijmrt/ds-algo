/* Bridge in one dfs O(N) */

bool vis[lmt];
int h[lmt], par[lmt], d[lmt];


void dfs(int u, int lev) {
    h[u] = lev;
    d[u] = h[u];
    vis[u] = true;
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if(!vis[v]) {
            par[v] = u;
            dfs(v, lev+1);
            d[u] = min(d[u], d[v]);
            if(d[v] > h[u]) {

            	u - v is a bridge.

            }
        } else if(v != par[u]) {
            d[u] = min(d[u], h[v]);
        }
    }
}

/* bridge end */

/* BIT code */

void update(int idx, ll num) {
    for(; idx <= n; idx += idx&(-idx))
        bit[idx] += num;
}

ll query(int idx) {
    ll ans = 0;
    for(; idx > 0; idx -= idx&(-idx))
        ans += bit[idx];
    return ans;
}

/* BIT END */