// USE WITH C++11. COMPILEATION ERROR IN C++14. REASON UNKNOWN.

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

int mat[1005][1005];
int dp[1005][1005];
int jump[10][10][1002][1002];
int lg2[1005], pwr[20];

void pre(){
    int cnt = -1; 
    for(int i = 1; i <= 1004; i++){
        if(!(i&(i-1)))
            cnt++;
        lg2[i] = cnt;
    }

    pwr[0] = 1;
    for(int i = 1; i <= 20; i++)
        pwr[i] = pwr[i-1]*2;
}

void pre1(int n, int m){
    for(int i = 0; pwr[i] <= n; i++){
        for(int j = 0; pwr[j] <= m; j++){
            for(int x = 1; x + pwr[i] -1 <= n; x++){
                for(int y = 1; y + pwr[j] -1 <= m; y++){
                    if(( i == 0 ) && ( j == 0 )) 
                        jump[i][j][x][y] = dp[x][y];
                    else if (i == 0)
                        jump[i][j][x][y] = max(jump[i][j-1][x][y], jump[i][j-1][x][y + pwr[j-1]]);
                    else if (j == 0)
                        jump[i][j][x][y] = max(jump[i-1][j][x][y], jump[i-1][j][x + pwr[i-1]][y]);
                    else 
                        jump[i][j][x][y] = max(jump[i-1][j-1][x][y], max(jump[i-1][j-1][x + pwr[i-1]][y], max(jump[i-1][j-1][x][y + pwr[j-1]], jump[i-1][j-1][x + pwr[i-1]][y + pwr[j-1]])));
                }
            }
        }
    }
}
 
int query(int x, int y, int x1, int y1){
    int k = lg2[x1 - x + 1];
    int l = lg2[y1 - y + 1];
    int ans = max(max(jump[k][l][x][y], jump[k][l][x1 - pwr[k] + 1][y]), max(jump[k][l][x][y1 - pwr[l] + 1], jump[k][l][x1 - pwr[k] + 1][y1 - pwr[l] + 1]));
    return ans;
}

int solve(int x1, int y1, int x2, int y2) {
    int l = 1;
    int r = min(x2 - x1 + 1, y2 - y1 + 1);
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if(query(x1 + mid - 1, y1 + mid - 1, x2, y2) >= mid)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main(){
    pre();
    int n, m;
    S2(n, m);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            S(mat[i][j]);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(mat[i][j] == 1)
                dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
            else
                dp[i][j] = 0;
        }
    }
    pre1(n, m);    
    int q;
    S(q);
    while(q--) {
        int x1, y1, x2, y2;
        S2(x1, y1);
        S2(x2, y2);
        if(query(x1, y1, x2, y2) == 0)
            printf("0\n");
        else
            printf("%d\n", solve(x1, y1, x2, y2));
    }
    return 0;
}