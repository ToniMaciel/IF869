#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 1000000;
int log2_floor_values[MAXN + 1];

void precompute_log2_floor_values() {
    log2_floor_values[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        log2_floor_values[i] = log2_floor_values[i >> 1] + 1;
}

function<ll(ll,ll)> func;

struct SparseTable
{
    vector<vector<ll>> st;
    ll n;
    string function;

    SparseTable(vector<ll> &a, string &type)
    {
        function = type;
        n = a.size();
        int maxn = log2_floor(a.size()) + 1;
        st.resize(maxn, vector<ll>(n));
        for (ll i = 0; i < n; i++)
            st[0][i] = a[i];
        for (ll i = 1; i < maxn; i++)
            for (ll j = 0; j < n; j++)
            {
                if(j + (1 << (i - 1)) >= n)
                    break;
                st[i][j] = func(st[i-1][j], st[i-1][j + (1 << (i - 1))]);
            }
    }

    ll query(ll l, ll r)
    {
        int i = log2_floor(r - l);
        if(function == "SUM")
        {
            ll sum = 0;
            while(l < r)
            {
                int aux = log2_floor(r - l);
                sum += st[aux][l];
                l += 1 << aux;
            }
            return sum;
        }
        
        return func(st[i][l], st[i][r - (1 << i)]);
    }

    ll upd(ll i, ll v)
    {
        st[0][i] = v;
        for(int k = 1; k < st.size(); k++)
        {
            for(int j = i - (1 << k) + 1; j <= i; j++)
            {
                if(j < 0)
                {
                    j = -1;
                    continue;
                }
                if(j + (1 << (k - 1)) >= n)
                    break;
                st[k][j] = func(st[k-1][j], st[k-1][j + (1 << (k - 1))]);
            }
        }

        return query(i, n);
    }

    int log2_floor(int i) {
        return i ? log2_floor_values[i] : -1;
    }
};

struct RGN
{
    ll seed;
    ll r = (1LL << 32), a = 1664525, c = 1013904223;
    RGN(ll seed) : seed(seed) {}
    ll next()
    {
        return seed = (a * seed + c) % r;
    }
};


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll s, n, o, q, u, m, test_case = 0;
    string f;
    precompute_log2_floor_values();

    while(cin >> s >> n >> f >> o >> q >> u)
    {
        if(f == "MIN")
            func = [](ll a, ll b) { return min(a, b); };
        else if(f == "MAX")
            func = [](ll a, ll b) { return max(a, b); };
        else
            func = [](ll a, ll b) { return a + b; };
        
        cout << "caso " << test_case++ << '\n';
        m = 4*n;
        RGN rgn(s);
        vector<ll> numbers(n);
        for(int i = 0; i < n; i++){
            numbers[i] = rgn.seed%m;
            rgn.next();
        }
        SparseTable st(numbers, f);

        for(int i = 0; i < o; i++)
        {
            if((rgn.seed%(q+u)) < q)
            {
                int l = rgn.next()%n;
                int r = l + 1 + (rgn.next()%(n-l));
                cout << st.query(l, r) << '\n';
            }
            else
            {
                int idx = rgn.next()%n;
                int v = rgn.next()%m;
                cout << st.upd(idx, v) << '\n';
            }
            rgn.next();
        }

        cout << '\n';
    }
    return 0;
}