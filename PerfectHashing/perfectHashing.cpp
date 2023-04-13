#include <bits/stdc++.h>
using namespace std;

uint32_t const P = (1u << 31) - 1;

struct RGN
{
    uint32_t seed, a = 1664525, c = 1013904223, calls = 0;
    RGN(uint32_t seed) : seed(seed) {}
    uint32_t next() {
        if(calls){
            return seed = (a * seed + c);
        }
        else {
            calls++;
            return seed;
        }
    }
};

RGN rgn(0);

function<int(int)> H(int M)
{
    int a = 1 + rgn.next() % (P - 1);
    int b = rgn.next() % P;
    return [=](int x) { return ((a * x + b) % P) % M; };
}

struct Hashtable
{
    int M, N = 0;
    vector<int>* T;
    function<int(int)> h;
    Hashtable(int M) : M(M) {
        T = new vector<int>[M];
        h = H(M);
    }

    int get(int k)
    {
        int i = h(k);
        for(int j = 0; j < T[i].size(); j++)
            if(T[i][j] == k)
                return j;
        return -1;
    }

    pair<int, int> set(int k, bool flag = false)
    {
        int j = get(k);
        if (flag || j == -1) {
            if (2*N > M)
                rehashing();
            int i = h(k);
            T[i].push_back(k);
            N++;
            return {i, T[i].size() - 1};
        }
        return {h(k), j};
    }

    void rehashing()
    {
        int oldM = M, oldN = N;
        M = 2*M + 1;
        vector<int>* oldT = T;
        T = new vector<int>[M];
        h = H(M);
        for (int i = 0; i < oldM; i++)
            for (int j = 0; j < oldT[i].size(); j++)
                set(oldT[i][j], true);
        N = oldN;
        delete[] oldT;
    }
};

struct PerfectHashtable
{
    int M;
    vector<int>* T;
    function<int(int)> h;
    vector<function<int(int)>> g;
    PerfectHashtable(int N) {
        M = 2*floor(N/2) + 1;
        T = new vector<int>[M];
        h = H(M);
        g.resize(M, nullptr);
    }

    void insertHashtable(Hashtable &T0)
    {
        while (true)
        {
            for (int i = 0; i < T0.M; i++)
                for (int j = 0; j < T0.T[i].size(); j++)
                    set(T0.T[i][j]);
            if (getSquareSum() <= 4*T0.N)
                break;
        }

        for (int i = 0; i < M; i++){
            if (T[i].size() == 0)
                continue;
            while (true){
                vector<int> newTi((T[i].size()*T[i].size()) + 1, -1);
                g[i] = H(newTi.size());
                bool noCollision = true;
                for (int j = 0; j < T[i].size(); j++){
                    int k = g[i](T[i][j]);
                    if (newTi[k] == -1)
                        newTi[k] = T[i][j];
                    else {
                        noCollision = false;
                        break;
                    }
                }
                if (noCollision){
                    T[i] = newTi;
                    break;
                }
            }
        }
    }

    int getSquareSum()
    {
        int sum = 0;
        for (int i = 0; i < M; i++)
            sum += (T[i].size() * T[i].size());
        return sum;
    }

    int get(int k)
    {
        int i = h(k);
        for(int j = 0; j < T[i].size(); j++)
            if(T[i][j] == k)
                return j;
        return -1;
    }

    pair<int, int> getPerfect(int k)
    {
        int i = h(k);
        if (g[i] == nullptr)
            return {-1, -1};
        int j = g[i](k);
        if (T[i][j] == k)
            return {i, j};
        return {-1, -1};
    }

    pair<int, int> set(int k, bool flag = false)
    {
        int j = get(k);
        if (flag || j == -1) {
            int i = h(k);
            T[i].push_back(k);
            return {i, T[i].size() - 1};
        }
        return {h(k), j};
    }
};

int32_t main()
{
    uint32_t S, U, M0, I, Q, Pi, Pq;
    cin >> S >> U >> M0 >> I >> Q >> Pi >> Pq;
    rgn.seed = S;
    Hashtable T0(M0);

    for(int i = 0; i < I; i++)
    {
        int k = rgn.next() % U;
        pair<int, int> ans = T0.set(k);
        if(i % Pi == 0)
            cout << "I " <<  k << " " << ans.first << " " << ans.second << '\n';
    }

    PerfectHashtable T1(T0.N);
    T1.insertHashtable(T0);

    for(int i = 0; i < Q; i++)
    {
        int k = rgn.next() % U;
        pair<int, int> ans = T1.getPerfect(k);
        if(i % Pq == 0)
            cout << "Q " << k << " " << ans.first << " " << ans.second << '\n';
    }
    return 0;
}