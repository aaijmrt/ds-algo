// Implementation of min cost max flow algorithm using adjacency
// matrix (Edmonds and Karp 1972).  This implementation keeps track of
// forward and reverse edges separately (so you can set cap[i][j] !=
// cap[j][i]).  For a regular max flow, set all edge costs to 0.
//
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//     
// INPUT: 
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.

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
auto T=clock(); 
//cout<<double(clock()-T)/CLOCKS_PER_SEC<<'\n';
const ll mod = 1000000007LL;
const int lmt = 1000005;

#define lli long long


struct point{
    double x, y, z;
    point(){
        x = y = z = 0.0;
    }
    point(double a, double b, double c) {
        x = a; y = b; z = c;
    }
};

double getdist(point &a, point &b) {
    double ans = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
    ans = sqrtl(ans);
    return ans;
}

const double inf = 1e18;

point pts[555];
int springs[55], towns[55];
double mat[555][555];

typedef vector<double> VI;
typedef vector<VI> VVI;
typedef vector<double> VL;
typedef vector<VL> VVL;
typedef pair<double, double> PII;
typedef vector<PII> VPII;

const double INF = numeric_limits<int>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost;
  VI found;
  VL dist, pi, width;
  VPII dad;

  MinCostMaxFlow(int N) : 
    N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)), 
    found(N), dist(N), pi(N), width(N), dad(N) {}
  
  void AddEdge(int from, int to, double cap, double cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }
  
  void Relax(int s, int k, double cap, double cost, int dir) {
    double val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  double Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;
    
    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  pair<double, double> GetMaxFlow(int s, int t) {
    double totflow = 0, totcost = 0;
    while (double amt = Dijkstra(s, t)) {
      totflow += amt;
      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }
    }
    return make_pair(totflow, totcost);
  }
};

int main(){
    // freopen("inp.txt", "r", stdin);

    int n, num_s, num_t, len;
    S2(n, num_s); S2(num_t, len);

    for(int i = 1; i <= n; i++) {

        double x, y, z;
        scanf("%lf %lf %lf",&pts[i].x,&pts[i].y,&pts[i].z);
    }

    for(int i = 0; i < num_s; i++) S(springs[i]);
    for(int i = 0; i < num_t; i++) S(towns[i]);

    for(int i = 1; i <= n; i++) {
        mat[i][i] = 0.0;
        for(int j = i+1; j <= n; j++) {
            double dst = getdist(pts[i], pts[j]);
            if(pts[i].z > pts[j].z) {
                mat[j][i] = inf;
                if(dst <= len)
                    mat[i][j] = dst;
                else
                    mat[i][j] = inf;
            }
            else if(pts[i].z < pts[j].z) {
                mat[i][j] = inf;
                if(dst <= len)
                    mat[j][i] = dst;
                else
                    mat[j][i] = inf;
            }
            else if(pts[i].z == pts[j].z) {
                mat[i][j] = mat[j][i] = inf;
            }

        }
    }


    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    int sor = 0, sink = n+1;
    MinCostMaxFlow E(n + 2);
    for(int i = 0; i < num_s; i++) {
        E.AddEdge(sor, springs[i], 1, 0);
    }
    for(int i = 0; i < num_t; i++) {
        E.AddEdge(towns[i], sink, 1, 0);
    }
    for(int i = 0; i < num_s; i++) {
        for(int j = 0; j < num_t; j++) {
            int u = springs[i];
            int v = towns[j];
            if(mat[u][v] == inf) continue;
            E.AddEdge(u, v, 1, mat[u][v]);
        }
    }
    pair<double, double> ans = E.GetMaxFlow(sor, sink);
    if((int)(ans.first) != num_t){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    
    printf("%lf\n",ans.second);
    return 0;
}
