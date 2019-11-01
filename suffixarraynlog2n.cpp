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
const ll mod = 1000000007LL;
const int lmt = 100005;

int sa[20][lmt];
struct sable{
    int fst, sec, id;
}t[lmt];
int SA[lmt];
int LCP[lmt];

bool cmp(const sable &a, const sable &b){
    if(a.fst == b.fst)
        return a.sec < b.sec;
    return a.fst < b.fst;
}

int getLCP(int x, int y, int N){
    int upto = ceil(log2(N)), ans = 0;
    cout<<upto;nl;
    for(int stp = upto; stp >= 0 && x < N && y < N; stp--){
        if(sa[stp][x] == sa[stp][y]){
            ans += 1<<stp;
            x += 1<<stp;
            y += 1<<stp;
        }
    }
    return ans;
}

void doSA(char *str, int N){
    for (int i = 0; i < N; ++i)
        sa[0][i] = str[i] - 'a';
    for(int stp = 1, cnt = 1; cnt < N; stp++, cnt *= 2){
        for (int i = 0; i < N; ++i){
            t[i].fst = sa[stp - 1][i];
            t[i].sec = -1;
            t[i].id = i;
            if(i+cnt < N)
                t[i].sec = sa[stp - 1][i + cnt];
        }
        sort(t, t+N, cmp);
        for (int i = 0; i < N; ++i){
            if(i > 0 && t[i].fst == t[i - 1].fst && t[i].sec == t[i - 1].sec)
                sa[stp][t[i].id] = sa[stp][t[i-1].id];
            else
                sa[stp][t[i].id] = i;
        }
    }
    for (int i = 0; i < N; ++i)
        SA[i] = t[i].id;
}

void doLCParray(int N){
    for(int i = 1; i < N; i++)
        LCP[i] = getLCP(SA[i], SA[i - 1], N);
}

int main(){
    char s[1000];
    scanf("%s",s);
    int N = strlen(s);
    doSA(s, N);
    doLCParray(N);
    for(int i = 0; i < N; i++)
        cout<<SA[i]<<" "<<LCP[i]<<endl;
    return 0;
}