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
const int lmt = 1000005;
const int INF = 1<<30;
const int maxnodes = 10009;

int nodes = maxnodes, src, dest;
int dist[maxnodes],work[maxnodes];

struct Edge {
  int to, rev;
  int f, cap;
};

vector <Edge> g[maxnodes];

// Adds bidirectional edge
void addEdge(int s, int t, int cap ,int revcap){
  Edge a = {t, (int)g[t].size(), 0, cap};
  Edge b = {s, (int)g[s].size(), 0, revcap};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(dist, dist + nodes, -1);
  dist[src] = 0;
  queue <int> qu;qu.push(src);
  while( !qu.empty() )
  {
      int u = qu.front();qu.pop();
      for(int j = 0;j < g[u].size() ;j++)
      {
          Edge &e = g[u][j];
          int v = e.to;
          if(dist[v] == -1 && e.f < e.cap)
          {
              dist[v] = dist[u] + 1;
              qu.push(v);
          }
      }
  }
  return dist[dest] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (dist[v] == dist[u] + 1) {
      int df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

int maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  int result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (int delta = dinic_dfs(src, INF))
      result += delta;
  }
  return result;
}

vector<pair<int, int> > v;

int rem[10004][5];

int pre() {
    rem[0][0] = rem[0][1] = rem[0][2] = rem[0][3] = rem[0][4];
    for(int i = 1; i <= 10000; i++) {
        for(int j = 0; j < 5; j++)
            rem[i][j] = rem[i-1][j];
        rem[i][i%5]++;
    }
}

int main(){
    pre();
    int n, b, q;
    S2(n, b);
    S(q);

    for(int i = 0; i < q; i++) {
        int upto, qu;
        S2(upto, qu);
        v.pb(mp(upto, qu));
    }

    sort(v.begin(), v.end());
    if(v[q-1].X != b) {
        v.pb(mp(b, n));
        q++;
    }

    for(int i = 1; i < q; i++) {
        if(v[i].Y < v[i-1].Y) {
            printf("unfair\n");
            return 0;
        }
    }
    int taken = 0;
    for(int i = 0; i < q; i++) {
        int tmp = v[i].Y;
        v[i].Y -= taken;
        taken = tmp;
    }

    int sor = 0, sink = 6+q;

    for(int i = 1; i <= 5; i++) {
        addEdge(sor, i, n/5, 0);
        // deb3(sor, i, n/5);
    }

    int last = 0;

    for(int i = 0; i < q; i++) {
        int upto = v[i].X, num = v[i].Y;
        for(int j = 0; j < 5; j++) {
            int f = rem[upto][j] - rem[last][j];
            addEdge(j+1, 6+i, f, 0);
            // deb3(j+1, 6+i, f);
        }
        addEdge(6+i, sink, num, 0);
        // deb3(6+i, sink, num);
        last = upto;
    }

    int flow = maxFlow(sor, sink);
    if(flow == n)
        printf("fair\n");
    else
        printf("unfair\n");
    return 0;
}