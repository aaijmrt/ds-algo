#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
 
int N, K;
int cpt[200][2], mpt[200][2];
double d[200][200];
 
int n1, n2, e, last[200], pre[40000], head[40000];
int matching[200], dist[200], Q[200]; 
bool used[200], vis[200];
void bfs() {
    memset(dist, -1, sizeof dist);
    int tail = 0;
    for(int u = 0; u < n1; u++)
        if(!used[u]) { 
            dist[u] = 0; Q[tail++] = u;
        }
    for(int i = 0; i < tail; i++) {
        int u = Q[i];
        for(int e = last[u]; e >= 0; e = pre[e]) {
            int v = matching[head[e]];
            if(v >= 0 && dist[v] < 0) {
                dist[v] = dist[u] + 1;
                Q[tail++] = v;
            }
        }
    }
}
 
bool dfs(int u) {
    vis[u] = true;
    for(int e = last[u]; e >= 0; e = pre[e]) {
        int h = head[e], v = matching[h];
        if(v<0||!vis[v]&&dist[v]==dist[u]+1&&dfs(v)){
            matching[h] = u;
            used[u] = true;
            return true;
        }
    }
    return false;
}
 
int hopcroftKarp() {
    memset(used, false, sizeof used);
    memset(matching, -1, sizeof matching);
    int matches = 0, flow;
    do{
        flow = 0;
        bfs(); 
        memset(vis, 0, sizeof vis);
        for(int u = 0; u < n1; u++)
            if(!used[u] && dfs(u)) flow++;
        matches += flow;
    }while(flow > 0);
    return matches;
}
 
void init(int n1, int n2) {
    ::n1 = n1; ::n2 = n2; e = 0;
    memset(last, -1, sizeof last);
}
 
void addEdge(int u, int v){ 
    head[e] = u; pre[e] = last[v]; last[v] = e++;
}
 
bool f(double maxd){
    init(N, N);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(d[i][j] > maxd){
                addEdge(i, j);
            }
        }
    }
    int t = 2*N-hopcroftKarp();
    return t >= K;
}
 
int main(){
    scanf("%d %d", &N, &K);
    for(int i=0; i<N; i++){
        scanf("%d %d", &cpt[i][0], &cpt[i][1]);
    }
    for(int i=0; i<N; i++){
        scanf("%d %d", &mpt[i][0], &mpt[i][1]);
    }
    
    double L = 0;
    double R = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            d[i][j] = hypot(cpt[i][1]-mpt[j][1], cpt[i][0]-mpt[j][0]);
            R = max(R, d[i][j]);
        }
    }
    
    while(R-L > 1e-10){
        double M = (L+R)/2;
        if(f(M)){
            R = M;
        }else{
            L = M;
        }
    }
    printf("%.10f\n", L);
    
    return 0;
} 