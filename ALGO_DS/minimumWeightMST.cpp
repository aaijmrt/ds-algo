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
const int lmt = 200005;
const int logn = log2(lmt) + 3;

//////////////////////////////////////////////////////////////
//CODE TO FIND THE MINIMUM WEIGHT MST IF AN EDGE IS INCLUDED//
//////////////////////////////////////////////////////////////

struct edge{
    int u, v, id;
    ll wt;
    edge(int a, int b, ll c, int d) {
        u = a; v = b; wt = c; id = d;
    }
};


vector<edge> edges;
int par[lmt];
bool inmst[lmt];
vector<pair<int, ll> > adj[lmt];
int jump[lmt][logn];
ll Ewt[lmt][logn];
int lev[lmt];
ll ans[lmt];

bool cmp(const edge &a, const edge &b) {
    return a.wt < b.wt;
}

int find(int x){
    if(par[x] == x)
        return x;
    else
        return par[x] = find(par[x]);
}

void unite(int x, int y) {
    par[find(x)] = find(y);
}

ll mstwt = 0;

void mst(){
    sort(edges.begin(), edges.end(), &cmp);
    mem(inmst, false);
    for(int i = 0; i < edges.size(); i++) {
        int x = edges[i].u, y=edges[i].v;
        if(find(x) != find(y)){
            unite(x,y);
            mstwt += edges[i].wt;
            // deb2(x, y);
            inmst[edges[i].id] = true;
            adj[x].pb(mp(y, edges[i].wt));
            adj[y].pb(mp(x, edges[i].wt));
        }
    }
}

void dfs(int u, int p, ll wt, int l) {
    jump[u][0] = p;
    Ewt[u][0] = wt;
    lev[u] = l;
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].X;
        if(v != p)
            dfs(v, u, adj[u][i].Y, l+1);
    }
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

ll getweight(int x, int upto) {
    if(x == upto) return 0LL;
    int tmp;
    for(tmp = 1; lev[x] >= (1<<tmp); tmp++);
    tmp--;
    ll ret = 0LL;
    for(int i = tmp; i >= 0; i--){
        if((lev[x] - (1<<i)) >= lev[upto]){
            ret = max(ret, Ewt[x][i]);
            x = jump[x][i];
        }
    }
    return ret;
}

void solve() {
    for(int i = 0; i < edges.size(); i++) {
        if(inmst[edges[i].id]) {
            ans[edges[i].id] = mstwt;
            continue;
        }
        int x = edges[i].u, y = edges[i].v;
        ll w = edges[i].wt;
        int lca = LCA(x, y);
        // deb3(x, y, lca);
        ll rem = max(getweight(x, lca), getweight(y, lca));
        // deb2(rem, w);
        ans[edges[i].id] = mstwt - rem + w;
    }
}

int main(){
    // freopen("inp.txt", "r", stdin);
    int n, m;
    S2(n, m);
    for(int i = 0; i < m; i++) {
        int x, y;
        ll w;
        S2(x, y);
        SL(w);
        edges.pb(edge(x, y, w, i));
        par[x] = x; par[y] = y;
    }
    mst();
    // deb(mstwt);
    dfs(1, 0, 0, 1);

    for(int i = 1; (1<<i) <= n; i++) {
        for(int u = 1; u <= n; u++) {
            jump[u][i] = jump[jump[u][i-1]][i-1];
            Ewt[u][i] = max(Ewt[u][i-1], Ewt[jump[u][i-1]][i-1]);
            // deb3(u, i, Ewt[u][i]);
        }
    }

    solve();

    for(int i = 0; i < m; i++)
        printf("%lld\n", ans[i]);

    return 0;
}