/****************
 * Maximum flow * (Dinic's on an adjacency list + matrix)
 ****************
 * PARAMETERS:
 *      - cap (global): adjacency matrix where cap[u][v] is the capacity
 *          of the edge u->v. cap[u][v] is 0 for non-existent edges.
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - prv contains the minimum cut. If prv[v] == -1, then v is not
 *          reachable from s; otherwise, it is reachable.
 * RUNNING TIME:
 *      - O(n^3)
 **/

#include <string.h>
#include <stdio.h>
#include<bits/stdc++.h>
using namespace std;
// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
// If you fill adj[][] yourself, make sure to include both u->v and v->u.
int cap[NN][NN], deg[NN], adj[NN][NN];

// BFS stuff
int q[NN], prv[NN];

int dinic( int n, int s, int t )
{
    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( prv, -1, sizeof( prv ) );
        int qf = 0, qb = 0;
        prv[q[qb++] = s] = -2;
        while( qb > qf && prv[t] == -1 )
            for( int u = q[qf++], i = 0, v; i < deg[u]; i++ )
                if( prv[v = adj[u][i]] == -1 && cap[u][v] )
                    prv[q[qb++] = v] = u;

        // see if we're done
        if( prv[t] == -1 ) break;

        // try finding more paths
        for( int z = 0; z < n; z++ ) if( cap[z][t] && prv[z] != -1 )
        {
            int bot = cap[z][t];
            for( int v = z, u = prv[v]; u >= 0; v = u, u = prv[v] )
                bot = min(bot, cap[u][v]);
            if( !bot ) continue;

            cap[z][t] -= bot;
            cap[t][z] += bot;
            for( int v = z, u = prv[v]; u >= 0; v = u, u = prv[v] )
            {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }

    return flow;
}

//----------------- EXAMPLE USAGE -----------------
int main()
{
    // read a graph into cap[][]
    memset( cap, 0, sizeof( cap ) );
    int n, s, t, m;
    scanf( " %d %d %d %d", &n, &s, &t, &m );
    while( m-- )
    {
        int u, v, c; scanf( " %d %d %d", &u, &v, &c );
        cap[u][v] = c;
    }

    // init the adjacency list adj[][] from cap[][]
    memset( deg, 0, sizeof( deg ) );
    for( int u = 0; u < total_vertices; u++ )
        for( int v = 0; v < total_vertices; v++ ) if( cap[u][v] || cap[v][u] )
            adj[u][deg[u]++] = v;

    printf( "%d\n", dinic( n, s, t ) );
    return 0;
}