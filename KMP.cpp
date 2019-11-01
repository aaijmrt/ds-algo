int F[N], mark[N];

void computeFailure(const string & T, int m) { // m is the length of T
    int i = 1,j = 0;
    F[0] = 0;
    while(i < m) {
        while(j < m && T[i] == T[j]) {
            ++j; F[i] = j; ++i;
        }
        if(i == m) break;
        if(j == 0) {
            F[i] = 0;
            ++i;
        } else {
            j = F[j-1];
        }
    }
}

void KMP(const string & S, const string & T) {  // search T in S
    int n = S.length();
    int m = T.length();

    memset(mark, false, sizeof(mark));
    if(m > n) return;

    computeFailure(T, m);

    int i = 0, j = 0;
    while((i-j) <= n - m) {
        while(j < m && S[i] == T[j]) {
          ++j; ++i;
        }
        if(j == m) {
            mark[i - m] = true;
        }
        if(j == 0) ++i;
        else j = F[j-1];
    }
}