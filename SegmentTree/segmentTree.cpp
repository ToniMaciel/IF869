#include <bits/stdc++.h>
using namespace std;
#define int uint32_t

struct RGN
{
    int seed, a = 1664525, c = 1013904223, calls = 0;
    RGN(int seed) : seed(seed), calls(0) {}
    int next() {
        return (calls++ ? seed = (a * seed + c) : seed);
    }
};

struct SegmentTree
{
    int N, neutralFuncElement;
    vector<int> tree;
    function<int(int, int)> F;
    
    SegmentTree(vector<int> &arr, function<int(int, int)> func, int neutralFuncElement) : F(func), N(arr.size()), neutralFuncElement(neutralFuncElement) {
        tree.resize(2 * N);
        for (int i = 0; i < N; i++)
            tree[N + i] = arr[i];
        for (int i = N - 1; i > 0; i--)
            tree[i] = F(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int idx, int val) {
        int i = N + idx;
        tree[i] = val;
        for (i /= 2; i >= 1; i /= 2)
            tree[i] = F(tree[2 * i], tree[2 * i + 1]);
    }

    int query(int l, int r) {
        int res = neutralFuncElement;
        for (l += N, r += N; l < r; l /= 2, r /= 2) {
            if (l & 1)
                res = F(res, tree[l++]);
            if (r & 1)
                res = F(res, tree[--r]);
        }
        return res;
    }
};

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int S, N, W, Q, U, P, M;
    string F;
    int neutralElement, caso = 0;
    function<int(int, int)> func;

    while (cin >> S >> N >> F >> W >> Q >> U >> P) {
        cout << "caso " << caso++ << '\n';
        M = 4 * N;

        if (F == "MIN") {
            func = [](int a, int b) { return min(a, b); };
            neutralElement = UINT32_MAX;
        }
        else if (F == "MAX") {
            func = [](int a, int b) { return max(a, b); };
            neutralElement = 0;
        }
        else {
            func = [](int a, int b) { return a + b; };
            neutralElement = 0;
        }

        vector<int> arr(N);
        RGN rgn(S);

        for (int i = 0; i < N; i++)
            arr[i] = rgn.next() % M;

        SegmentTree st(arr, func, neutralElement);
        
        for (int i = 0; i < W; i++) {
            int x = rgn.next() % (Q + U);
            if (x < Q) {
                int L = rgn.next() % N;
                int R = L + 1 + (rgn.next() % (N - L));
                if (i % P == 0)
                    cout << st.query(L, R) << '\n';
            }
            else {
                int I = rgn.next() % N;
                int V = rgn.next() % M;
                st.update(I, V);
                if (i % P == 0)
                    cout << st.query(I, N) << '\n';
            }
        }

        cout << '\n';
    }
    return 0;
}