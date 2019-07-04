#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;

vector<LL> f, as;
LL fast_pow(LL base, LL index, LL mod) {
    LL ret = 1;
    for(; index; index >>= 1, base = base * base % mod)
        if(index & 1) ret = ret * base % mod;
    return ret;
}
bool test_Primitive_Root(LL g, LL p) {
    for(LL i = 0; i < f.size(); ++i)
        if(fast_pow(g, (p - 1) / f[i], p) == 1)
            return 0;
    return 1;
}
LL get_Primitive_Root(LL p) {
    f.clear();
    LL tmp = p - 1;
    for(LL i = 2; i <= tmp / i; ++i) 
        if(tmp % i == 0)
            for(f.push_back(i); tmp % i == 0; tmp /= i);
    if(tmp != 1) f.push_back(tmp);
    for(LL g = 1; ; ++g) {
        if(test_Primitive_Root(g, p))
            return g;
    }
}
LL get_Discrete_Logarithm(LL x, LL n, LL m) {
    map<LL, int> rec;
    LL s = (LL)(sqrt((double)m) + 0.5), cur = 1;
    for(LL i = 0; i < s; rec[cur] = i, cur = cur * x % m, ++i);
    LL mul = cur;
    cur = 1;
    for(LL i = 0; i < s; ++i) {
        LL more = n * fast_pow(cur, m - 2, m) % m;
        if(rec.count(more))
            return i * s + rec[more];
        cur = cur * mul % m;
    }
    return -1;
}
LL ext_Euclid(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        LL ret = ext_Euclid(b, a % b, y, x);
        y -= x * (a / b);
        return ret;
    }
}
void solve_Linear_Mod_Equation(LL a, LL b, LL n) {
    LL x, y, d;
    as.clear();
    d = ext_Euclid(a, n, x, y);
    if(b % d == 0) {
        x %= n, x += n, x %= n;
        as.push_back(x * (b / d) % (n / d));
        for(LL i = 1; i < d; ++i)
            as.push_back((as[0] + i * n / d) % n);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin); freopen("data.out", "w", stdout);
#endif

    LL p, k, a;
    cin >> p >> k >> a;
    if(a == 0) {
        puts("1\n0");
        return 0;
    }
    LL g = get_Primitive_Root(p);
    LL q = get_Discrete_Logarithm(g, a, p);
    cout<<get_Discrete_Logarithm(1, 0, 2)<<endl;
//    solve_Linear_Mod_Equation(k, q, p - 1);
//    for(int i = 0; i < as.size(); ++i)
//        as[i] = fast_pow(g, as[i], p);
//    sort(as.begin(), as.end());
//    printf("%d\n", as.size());
//    for(int i = 0; i < as.size(); ++i) {
//        printf("%lld%c", as[i], i == as.size() - 1 ? '\n' : ' ');
//    }
    return 0;
}

