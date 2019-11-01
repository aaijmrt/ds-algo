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
#define DEB(x) cout<<#x<<" : "<<x<<endl;
const ll mod = 1000000007LL;
const int lmt = 200005;

int trie[32*lmt][2];
map<int, int> last;
map<int, int> occur;
int num = 1;
int par[40*lmt];

void add(int x) {
    int node = 0;
    for(int i = 31; i >= 0; i--) {
        int next = 0;
        if(x & (1 << i))
            next = 1;
        if(trie[node][next] == -1){
            trie[node][next] = num;
            num++;
        }
        par[trie[node][next]] = node;
        node = trie[node][next];
        last[x] = node;        
    }
}

int query(int x) {
    int node = 0, ans = 0;
    for (int i = 31; i >= 0; i--) {
        int next = 0;
        if((x & (1 << i)))
            next = 1;
        bool found = true;
        if(trie[node][1 - next] == -1) {
            next = 1 - next;
            found = false;
        }
        if(found)
            ans += (1 << i);
        node = trie[node][1 - next];
    }
    return ans;
}

void remove(int x) {
    int node = last[x];
    while(node != 0) {
        if((trie[node][0] == -1) && (trie[node][1] == -1)) {
            int pnode = par[node];
            if(trie[pnode][0] == node)
                trie[pnode][0] = -1;
            else
                trie[pnode][1] = -1;
        }
        node = par[node];
    }
    last.erase(x);
}

int main(){
    mem(trie, -1);
    int q;
    S(q);
    add(0);
    while(q--) {
        char c;
        int x;
        cin>>c>>x;
        if(c == '+') {
            if(occur[x] == 0)
                add(x);
            occur[x]++;
        }
        else if(c == '-') {
            if(occur[x] == 1)
                remove(x);
            occur[x]--;
        }
        else
            printf("%d\n", query(x));
    }
    return 0;
}