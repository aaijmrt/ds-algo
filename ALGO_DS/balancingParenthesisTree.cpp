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
int f[lmt], par[lmt], lev[lmt], pre[lmt], suf[lmt];
vector<int> adj[lmt];
map<int, vector<int> > M;
char s[lmt];

void add(int x, int val) {
    M[val].pb(x);
}

void remove(int x, int val) {
    M[val].pop_back();
}

int getval(int val) {
    int sz = M[val].size();
    if(sz == 0)
        return 0;
    return M[val][sz - 1];
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

void dfs(int u, int p, int l) {
    lev[u] = l;
    par[u] = p;
    jump[u][0] = p;
    if(s[u] == '(')
        f[u] = f[p] + 1;
    else
        f[u] = f[p] - 1;

    if(s[u] == ')') {
        pre[u] = 0;
        int v = getval(f[u] - 1);
        suf[u] = lev[u] - lev[v];
    }
    else {
        int v = getval(f[u] + 1);
        pre[u] = lev[u] - lev[v];
        suf[u] = 0;
    }

    add(u, f[u]);

    for(int i = 0; i < adj[u].size(); i++) {
        if(adj[u][i] != p)
            dfs(adj[u][i], u, l+1);
    }

    remove(u, f[u]);
}

int main(){
    int t;
    S(t);
    while(t--) {
        int n, q;
        S2(n, q);
        
        for(int i = 0; i <= n; i++) {
            par[i] = 0;
            lev[i] = 0;
            adj[i].clear();
            f[i] = 0;
            pre[i] = 0;
            suf[i] = 0;
            for(int j = 0; j < logn; j++)
                jump[i][j] = 0;
        }
        
        M.clear();
        
        for(int i = 0; i < n-1; i++) {
            int x, y;
            S2(x, y);
            adj[x].pb(y);
            adj[y].pb(x);
        }
        
        for(int i = 1; i <= n; i++)
            scanf(" %c",&s[i]);

        dfs(1, 0, 1);

        for(int i = 1; (1<<i) <= n; i++) {
            for(int u = 1; u <= n; u++)
                jump[u][i] = jump[jump[u][i-1]][i-1];
        }

        while(q--) {
            int x, y;
            S2(x, y);
            int lca = LCA(x, y);

            if(((lev[x] - lev[lca]) >= pre[x]) || ((lev[y] - lev[lca]) >= suf[y])) {
                printf("No\n");
                continue;
            }

            int balx = f[x] - f[par[lca]];
            int baly = f[y] - f[lca];

            if((balx + baly) == 0)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}