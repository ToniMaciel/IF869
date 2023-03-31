#include <bits/stdc++.h>
using namespace std;
#define ui unsigned int

struct VEB_Tree 
{
    int u, max_element, min_element, sqrt_u;
    VEB_Tree *summary;    
    VEB_Tree **cluster;

    VEB_Tree(int u) : u(u), max_element(-1), min_element(-1), sqrt_u((int)sqrt(u)), summary(nullptr) 
    {
        if(u > 2) {
            cluster = new VEB_Tree*[sqrt_u];
            for (int i = 0; i < sqrt_u; i++) 
                cluster[i] = nullptr;
        }
    }

    int high(int x) {
        return x / sqrt_u;
    }

    int low(int x) {
        return x % sqrt_u;
    }

    int index(int x, int y) {
        return x * sqrt_u + y;
    }

    bool contains(int x) {
        if(x == min_element || x == max_element) {
            return true;
        }
        else if(u == 2) {
            return false;
        }
        else {
            if(cluster[high(x)] == nullptr)
                return false;
            return cluster[high(x)]->contains(low(x));
        }
    }

    int insert(int x) {
        if(min_element == -1) {
            min_element = max_element = x;
            return 1;
        }
        else if(x < min_element) {
            swap(x, min_element);
        }
        if (u == 2) {
            min_element = min(min_element, x);
            max_element = max(max_element, x);
            return 1;
        } else {
            max_element = max(max_element, x);
            if(cluster[high(x)] == nullptr) {
                cluster[high(x)] = new VEB_Tree(sqrt_u);
                if(summary == nullptr) {
                    summary = new VEB_Tree(sqrt_u);
                }
                summary->insert(high(x));
            }
            return 1 + cluster[high(x)]->insert(low(x));
        }
    }

    int successor(int x) {
        if(u == 2) {
            if(x == 0 && max_element == 1) {
                return 1;
            }
            else {
                return -1;
            }
        }
        else if(min_element != -1 && x < min_element) {
            return min_element;
        }
        else {
            int h = high(x), l = low(x);
            int max_low = (cluster[h] == nullptr ? -1 : cluster[h]->max_element);
            if(max_low != -1 && l < max_low) {
                int offset = cluster[h]->successor(l);
                return index(h, offset);
            }
            else {
                int succ_cluster = (summary == nullptr ? -1 : summary->successor(h));
                if(succ_cluster == -1) {
                    return -1;
                }
                else {
                    if (cluster[succ_cluster] == nullptr || cluster[succ_cluster]->min_element == -1) {
                        return -1;
                    }
                    int offset = cluster[succ_cluster]->min_element;
                    return index(succ_cluster, offset);
                }
            }
        }
    }

    int remove(int x) {
        int ans = 0;
        if(min_element == max_element) {
            min_element = max_element = -1;
            return 1;
        }
        else if(u == 2) {
            if(x == 0) {
                min_element = 1;
            }
            else {
                min_element = 0;
            }
            max_element = min_element;
            return 1;
        }
        else {
            if(x == min_element) {
                if (summary == nullptr || summary->min_element == -1) {
                    min_element = max_element = -1;
                    return 1;
                }
                int first_cluster = summary->min_element;
                if (cluster[first_cluster] == nullptr || cluster[first_cluster]->min_element == -1) {
                    min_element = max_element = -1;
                    return 1;
                }
                x = index(first_cluster, cluster[first_cluster]->min_element);
                min_element = x;
            }
            int h = high(x), l = low(x);
            if (cluster[h] == nullptr)
                ans = 1;
            else
                ans = 1 + cluster[h]->remove(l);
            if(cluster[h] != nullptr && cluster[h]->min_element == -1) {
                summary->remove(h);
                delete cluster[h];
                cluster[h] = nullptr;
                if(x == max_element) {
                    int summary_max = summary->max_element;
                    if(summary_max == -1) {
                        delete summary;
                        summary = nullptr;
                        max_element = min_element;
                    }
                    else {
                        max_element = index(summary_max, cluster[summary_max]->max_element);
                    }
                }
            }
            else if(x == max_element) {
                max_element = index(h, cluster[h]->max_element);
            }
            return ans;
        }
    }
};


struct RGN
{
    ui seed;
    ui a = 1664525, c = 1013904223;
    
    RGN(ui seed) : seed(seed) {}
    
    ui next() {
        return seed = (a * seed + c);
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ui s, m, b, n, i, f, d, p, U;
    cin >> s >> m >> b >> n >> i >> f >> d >> p;
    U = (1U << (1U << m));

    RGN rgn(s);
    VEB_Tree veb(U);

    for(int it = 0; it < b; it++) {
        veb.insert(rgn.seed % U);
        rgn.next();
    }

    for(int it = 0; it < n; it++) {
        int x = rgn.seed % (i + f + d);
        rgn.next();
        int ans = 0;
        if(x < i) {
            if (!veb.contains(rgn.seed % U))
                ans = veb.insert(rgn.seed % U);
            if(it % p == 0) {
                cout << "I " << ans << "\n";
            }
        }
        else if(x < i + f) {
            if (it % p == 0) {
                if (rgn.seed % U < veb.max_element)
                    ans = veb.successor(rgn.seed % U);
                cout << "S " << (ans <= 0 ? U : ans) << "\n";
            }
        }
        else {
            if (rgn.seed % U < veb.max_element) {
                int y = veb.successor(rgn.seed % U);
                if (y > 0)
                    ans = veb.remove(y % U);
            }
            if (it % p == 0) {
                cout << "D " << ans << "\n";
            }
        }
        rgn.next();
    }
}