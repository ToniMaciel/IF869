#include <bits/stdc++.h>
using namespace std;
#define int long long

struct RGN
{
    int seed, a = 1664525LL, c = 1013904223LL, r = (1LL << 32), calls = 0;
    RGN(int seed) : seed(seed) {}
    int next() {
        if(calls){
            return seed = (a * seed + c) % r;
        }
        else {
            calls++;
            return seed;
        }
    }
};

RGN rgn(0LL);

struct node
{
    int key, value, height;
    vector<node*> next;
    node(int key, int value, int height) : key(key), value(value), height(height), next(vector<node*>(height, nullptr)) {}
    void print() {
        cout << this-> key << " --> " << this->height << "\n";
        node *cur = this->next[0];
        if (cur == nullptr) {
            cout << "NULL\n";
            return;
        }
        cur->print();
    }
};

struct skipList
{
    node *head;
    int height;
    
    skipList() : head(new node(-1, -1, 1)), height(1) {}

    int random_height() {
        int h = 1, max_h = height + 1;
        while(((rgn.next() % 100) < 50) && h < max_h) {
            h++;
        }
        return h;
    }
};

vector<node*> precursors(skipList &sl, int key)
{
    vector<node*> p(sl.height, nullptr);
    node *current = sl.head;
    for(int i = sl.height - 1; i >= 0; i--) {
        while(current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i];
        }
        p[i] = current;
    }
    return p;
}

pair<int, int> search(skipList &sl, int key)
{
    auto cur = sl.head;
    int visited_nodes = 1;
    for(int i = sl.height - 1; i >= 0; i--) {
        while(cur->next[i] != nullptr && cur->next[i]->key < key) {
            cur = cur->next[i];
            visited_nodes++;
        }
    }
    return make_pair(visited_nodes, (cur->next[0] != nullptr && cur->next[0]->key == key) ? cur->next[0]->height : 0);
}

int insert(skipList &sl, int key, int value)
{
    auto p = precursors(sl, key);
    if(p[0]->next[0] != nullptr && p[0]->next[0]->key == key) {
        p[0]->next[0]->value = value;
        return 0;
    }
    int height = sl.random_height();
    if (height > sl.height) {
        for(int i = sl.height; i < height; i++) {
            sl.head->next.push_back(nullptr);
            p.push_back(sl.head);
        }
        sl.height = height;
    }
    node *newNode = new node(key, value, height);
    for(int i = 0; i < height; i++) {
        newNode->next[i] = p[i]->next[i];
        p[i]->next[i] = newNode;
    }
    return 1;
}

int remove(skipList &sl, int key)
{
    auto p = precursors(sl, key);
    if (p[0]->next[0] == nullptr || p[0]->next[0]->key != key) {
        return 0;
    }
    node *toDelete = p[0]->next[0];
    for (int i = 0; i < toDelete->height; i++) {
        p[i]->next[i] = toDelete->next[i];
    }
    while (sl.height > 1 && sl.head->next[sl.height - 1] == nullptr) {
        sl.height--;
    }
    delete toDelete;
    return 1;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int s, u, b, n, f, j, d, p;
    cin >> s >> u >> b >> n >> f >> j >> d >> p;

    rgn.seed = s;
    skipList L;
    set<int> st;

    for (int i = 0; i < b; i++) {
        insert(L, rgn.next() % u, 0);
    }

    for (int i = 0; i < n; i++) {
        int x = rgn.next() % (f + j + d);
        if (x < f) {
            if (i % p == 0) {
                auto ans = search(L, rgn.next() % u);
                cout << "F " << ans.first << " " << ans.second << '\n';
            } else rgn.next();
        } else if (x < f + j) {
            int ans = insert(L, rgn.next() % u, 0);
            st.insert(rgn.seed%u);
            if (i % p == 0) {
                cout << "I " << ans << '\n';
            }
        } else {
            int ans = remove(L, rgn.next() % u);
            if (i % p == 0) {
                cout << "D " << ans << '\n';
            }
        }
    }

    return 0;
}