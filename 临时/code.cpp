#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
//#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

#define mem(a,x) memset(a,x,sizeof(a))

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

string ask() {
    cout<<"?"<<endl;
    string s;
    cin>>s;
    return s;
}

void print(const string &s,const string &t) {
    cout<<"! "<<s<<" "<<t<<endl;
}

const int N=105;
//string s[N];
int n,k,q,num[105][2];
vector<string> v[2],V;
string ss,tt;

void Count(vector<string> V,int num[][2]) {
    mem(num,0);
    for (auto t:V) for (int i=0; i<sz(t); ++i) num[i][t[i]-'0']++;
}

int ch(int x,int y) {
    if (abs(x-y)<10) return -1;
    if (x>y) return 0;
    return 1;
}

string res;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>k>>q;
	rep(i,1,n+1) V.pb(ask());
	Count(V,num);
	rep(i,0,n) res+='0';
	int p=-1;
	rep(i,0,n-1) {
	    int t=ch(num[i][0],num[i][1]);
        if (t!=-1) res[i]=t+'0'; else {
            p=t;
            break;
        }
    }
    if (p==-1) {
        print(res,res);
        return 0;
    }
    for (auto t:V) v[t[p]-'0'].pb(t);
    Count(v[0],num);
    rep(i,1,n+1) ss+='0';
    rep(i,1,n+1) tt+='0';
    rep(i,0,n) ss[i]=(num[i][1]>=num[i][0])+'0';
    Count(v[1],num);
    rep(i,0,n) tt[i]=(num[i][1]>=num[i][0])+'0';
    if (ss>tt) swap(ss,tt);
    print(ss,tt);
	
	return 0;
}

