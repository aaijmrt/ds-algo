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
#define debv(x) {cout<<#x<<" : "<<endl; for(int ii =0; ii < x.size(); ii++) cout<<x[ii]<<" "; cout<<endl; }
#define debarr(x, xs) {cout<<#x<<" : "<<endl; for(int ii =0; ii < xs; ii++) cout<<x[ii]<<" "; cout<<endl; }
const ll mod = 1000000007LL;
const int lmt = 1000005;

const int INF = 0x3f3f3f3f;

struct edge {
    int u, v;
    int flow;
    int cost;
    edge() {}
    edge(int u, int v, int f, int c) : u(u), v(v), flow(f), cost(c) {}
};

struct MinCostMaxFlow {
    int N;
    vector < vector <int> > G;
    vector <edge> E;
    int numEdges;
    vector <int> found, dad;
    vector <int> dist;

    MinCostMaxFlow(int N): 
     N(N), G(N), found(N), dist(N), dad(N), numEdges(0) {}
  
    void addEdge(int from, int to, int capacity, int cost) {
        // dbg(from), dbg(to), dbg(capacity), dbg(cost), dbn;
        G[from].push_back(numEdges++);
        E.push_back(edge(from, to, capacity, cost));
        G[to].push_back(numEdges++);
        E.push_back(edge(to, from, 0, int(-1) * cost));
    }
  
    bool spfa(int s, int t) {
        fill(dad.begin(), dad.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(found.begin(), found.end(), 0);
        queue <int> Q;
        dist[s] = 0;
        Q.push(s);
        found[s] = true;
        
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u == t) continue;
            for (int i = 0; i < G[u].size(); ++i) {
                edge &pres = E[G[u][i]];
                int v = pres.v;
                if(pres.flow <= 0) continue;
                if(dist[u] + pres.cost < dist[v]) {
                    dad[v] = G[u][i];
                    dist[v] = dist[u] + pres.cost;
                    if(!found[v]) Q.push(v), found[v] = true;
                }
            }
            found[u] = false;
        }
        return (dad[t] != -1);
    }
 
    int dfs(int s,int t) {
        int flow = INF;
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            if(E[i].flow < flow) flow = E[i].flow;
        }
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            E[i].flow -= flow;
            E[i ^ 1].flow += flow;
        }
        return flow;
    }

    pair <int, int> getMaxFlow(int s, int t) {
        int totflow = 0;
        int totcost = 0;
        while(spfa(s,t)) {
            int amt = dfs(s,t);
            totflow += amt;
            totcost += dist[t] * (int)amt;
        }
        return make_pair(totflow, totcost);
    }
};


int wt[105];
string str[105];

int main(){
    int n, m, x;
    S(n);
    string s;
    cin>>s;
    S(m);
    for(int i = 0; i < m; i++)
        cin>>str[i]>>wt[i];
    S(x);
    int sor = n + 1, sink = n;
    MinCostMaxFlow mcmf(n + 2);
    mcmf.addEdge(sor, 0, x, 0);

    for(int i = 0; i < n; i++) {
        mcmf.addEdge(i, i+1, x, 0);
    }

    for(int i = 0; i < m; i++) {
        int sz = str[i].size();
        for(int j = 0; j < n - sz + 1; j++) {
            bool flag = true;
            for(int k = 0; k < sz; k++) {
                if(str[i][k] != s[j+k]) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                mcmf.addEdge(j, j+sz, 1, -wt[i]);
            }
        }
    }
    pair<int, int> ans = mcmf.getMaxFlow(sor, n);
    cout<<-1*ans.Y;nl;
    return 0;
}