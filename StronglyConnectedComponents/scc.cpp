#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while(c--) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n);
        vector<vector<int>> adjT(n);
        for(int i = 0; i < n; ++i) {
            int idx, numberOfEdges;
            string edges;
            cin >> idx >> edges;
            edges.pop_back();
            numberOfEdges = stoi(edges);

            for(int j = 0; j < numberOfEdges; ++j) {
                int v;
                cin >> v;
                adj[idx].push_back(v);
                adjT[v].push_back(idx);
            }
        }

        vector<bool> visited(n, false);
        vector<int> order;

        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            for(int v : adj[u]) {
                if(!visited[v]) {
                    dfs(v);
                }
            }
            order.push_back(u);
        };

        for(int i = 0; i < n; ++i) {
            if(!visited[i]) {
                dfs(i);
            }
        }

        vector<int> scc(n, -1);
        function<void(int, int, vector<int>&)> dfs2 = [&](int u, int s, vector<int> &component) {
            scc[u] = s;
            component.push_back(u);
            for(int v : adjT[u]) {
                if(scc[v] == -1) {
                    dfs2(v, s, component);
                }
            }
        };

        vector<pair<int, string>> sccs;
        int s = 0;
        for(int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if(scc[u] == -1) {
                vector<int> component;
                dfs2(u, s++, component);
                sort(component.begin(), component.end());
                string sccString = "";
                for(int u : component) {
                    sccString += to_string(u) + " ";
                }
                sccString.pop_back();
                sccs.push_back({component[0], sccString});
            }
        }

        sort(sccs.begin(), sccs.end());
        cout << s << '\n';
        for(auto &sccString : sccs)
            cout << sccString.second << '\n';
        cout << '\n';
    }
    return 0;
}