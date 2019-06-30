#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
#define rep(i, n) for(int i=0;i<n;i++)
 
const int MOD = 1e9 + 7;
int N, r, h, A, B;
char X[5050];
 
int pw(int x, int y = MOD - 2) {
	int res = 1;
	while(y) {
		if(y & 1) res = (ll) res * x % MOD;
		x = (ll) x * x % MOD;
		y >>= 1;
	}
	return res;
}
 
char Y[5050];
int D[5050][5050], dl[5050], dr[5050];
 
void add(int &x, int y) { x = (x + y) % MOD; }
 
void get_dp(char X[], int N, int dp[], int S) {
	if(S == 0) { dp[0] = 1; return; }
	int height[5050] = {}, hc = 0, c = 0, idxs[5050];
	for(int i=1;i<=N;i++) {
		if(X[i] == 'H') {
			height[++hc] = c;
			idxs[hc] = i;
		}
		else ++c;
	}
	memset(D, 0, sizeof D);
	D[S][1] = 1;
	for(int i=S;i<=hc;i++)
		for(int j=1;j<=height[i];j++) { 
			add(D[i][j], D[i][j-1]); 
			add(D[i][j], D[i-1][j]); 
	}
	for(int i=S;i<=hc;i++) dp[idxs[i]] = D[i][height[i]];
}

int main() {
	scanf("%d%d%d", &N, &r, &h);
	int tr = r * (ll) pw(r + h) % MOD;
	int th = h * (ll) pw(r + h) % MOD;
	r = tr; h = th;
	scanf("%s", X);
	scanf("%d%d", &A, &B);
	int lv = 0, rv = N - 1;
	while(lv < N && X[lv] == 'H') ++lv, --B;
	while(rv >= 0 && X[rv] == 'R') --rv, --A;
	if(lv == N) {
		printf("%d\n", (A == 0 && B == 0) ? 1 : 0);
	}
	else if(rv == -1) {
		printf("%d\n", (A == 0 && B == 0) ? 1 : 0);
	}
	else {
		if(A < 0 || B < 0) { puts("0"); return 0; }
		for(int i=lv;i<=rv;i++) Y[i-lv+1] = X[i];
		N = rv - lv + 1;
		get_dp(Y, N, dl, B);
		reverse(Y+1, Y+1+N);
		for(int i=1;i<=N;i++) Y[i] = (Y[i] == 'R' ? 'H' : 'R');
		get_dp(Y, N, dr, A);
		reverse(dr, dr+2+N);
		int ans = 0;
		for(int i=0;i<=N;i++) add(ans, (ll)dl[i] * dr[i + 1] % MOD);
		int ch = 0, cr = 0;
		for(int i=1;i<=N;i++) if(Y[i] == 'R') ++ch;
		cr = N - ch;
		rep(i, cr - A) ans = (ll)ans * r % MOD;
		rep(i, ch - B) ans = (ll)ans * h % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
