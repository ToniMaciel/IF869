#include <bits/stdc++.h>
using namespace std;
#define int long long

struct RGN
{
    int seed, a = 1664525, c = 1013904223, calls = 0, r = 1LL << 32;
    RGN(int seed) : seed(seed), calls(0) {}
    int next() {
        return (calls++ ? seed = (a * seed + c) % r : seed);
    }
};

RGN rgn(0);

struct Node
{
    int key, prty;
    Node *left, *right, *parent;
    Node(int key) : key(key), prty(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct Treap
{
    Node *root;
    Treap() : root(nullptr) {}

    int insert(int key) {
        if (query(key) != -1)
            return -1;
        Node *node = new Node(key);
        node->prty = rgn.next();

        root = insertNode(root, node);
        return query(key);
    }

    Node* insertNode(Node *rt, Node *node)
    {
        if (rt == nullptr)
            return node;
        else if (node->prty > rt->prty)
        {
            split(rt, node->key, node->left, node->right);
            return node;
        }
        else if (node->key < rt->key)
            rt->left = insertNode(rt->left, node);
        else
            rt->right = insertNode(rt->right, node);
        return rt;
    }

    void split(Node *rt, int key, Node *&left, Node *&right)
    {
        if (rt == nullptr)
            left = right = nullptr;
        else if (key < rt->key)
        {
            split(rt->left, key, left, rt->left);
            right = rt;
        }
        else
        {
            split(rt->right, key, rt->right, right);
            left = rt;
        }
    }

    int remove(int key) {
        int depth;
        tie(root, depth) = removeNode(root, key);

        return depth;
    }

    pair<Node*, int> removeNode(Node *rt, int key)
    {
        if (rt == nullptr)
            return {nullptr, INT_MIN};
        else if (key == rt->key)
        {
            Node *node = merge(rt->left, rt->right);
            delete rt;
            return {node, 0};
        }
        else if (key < rt->key)
        {
            auto [node, depth] = removeNode(rt->left, key);
            rt->left = node;
            return {rt, depth + 1};
        }
        else
        {
            auto [node, depth] = removeNode(rt->right, key);
            rt->right = node;
            return {rt, depth + 1};
        }
    }

    Node* merge(Node *left, Node *right)
    {
        if (left == nullptr)
            return right;
        else if (right == nullptr)
            return left;
        else if (left->prty > right->prty)
        {
            left->right = merge(left->right, right);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            return right;
        }
    }

    int query(int key) {
        Node *cur = root;
        int depth = 0;

        while(cur != nullptr && cur->key != key) {
            depth++;
            if(key < cur->key) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }

        return (cur == nullptr ? -1 : depth);
    }
};



int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int S, U, B, N, I, D, Q, P;
    cin >> S >> U >> B >> N >> I >> D >> Q >> P;

    rgn.seed = S;
    Treap T;

    for(int i = 0; i < B; i++)
        T.insert(rgn.next() % U);

    for(int i = 0; i < N; i++)
    {
        int x = rgn.next() % (I + D + Q);
        int K = rgn.next() % U;
        int ans = -1;
        if(x < I) {
            ans = T.insert(K);
            if(i % P == 0)
                cout << "I " << K << " " << ans << "\n";
        }
        else if(x < I + D) {
            ans = T.remove(K);
            if(i % P == 0)
                cout << "D " << K << " " << max(ans, -1LL) << "\n";
        }
        else {
            if(i % P == 0) {
                ans = T.query(K);
                cout << "Q " << K << " " << ans << "\n";
            }
        }
    } 

    return 0;
}

