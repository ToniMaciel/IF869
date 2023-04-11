#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct RGN
{
    ll seed, a = 1664525LL, c = 1013904223LL, r = (1LL << 32), calls = 0;
    RGN(ll seed) : seed(seed) {}
    ll next() {
        if(calls){
            return seed = (a * seed + c) % r;
        }
        else {
            calls++;
            return seed;
        }
    }
};

struct Node
{
    int key;
    Node *left, *right, *parent;
    Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct SplayTree
{
    Node *root;
    SplayTree() : root(nullptr) {}

    Node* rotateLeft(Node *x)
    {
        Node *parent = x->parent;
        Node *right = x->right;
        Node *rightLeft = right->left;
        x->right = rightLeft;
        if(rightLeft) rightLeft->parent = x;
        right->left = x;
        x->parent = right;
        right->parent = parent;
        if(parent)
        {
            if(parent->left == x) parent->left = right;
            else parent->right = right;
        }
        return right;
    }

    Node* rotateRight(Node *x)
    {
        Node *parent = x->parent;
        Node *left = x->left;
        Node *leftRight = left->right;
        x->left = leftRight;
        if(leftRight) leftRight->parent = x;
        left->right = x;
        x->parent = left;
        left->parent = parent;
        if(parent)
        {
            if(parent->left == x) parent->left = left;
            else parent->right = left;
        }
        return left;
    }

    Node* zig(Node *x)
    {
        Node *parent = x->parent;
        if(parent->left == x) return rotateRight(parent);
        else return rotateLeft(parent);
    }

    Node* zigZag(Node *x)
    {
        Node *parent = x->parent;
        Node *grandParent = parent->parent;
        if(parent == grandParent->left)
        {
            if(x == parent->left)
            {
                rotateRight(grandParent);
                return rotateRight(parent);
            }
            else
            {
                rotateLeft(parent);
                return rotateRight(grandParent);
            }
        }
        else
        {
            if(x == parent->left)
            {
                rotateRight(parent);
                return rotateLeft(grandParent);
            }
            else
            {
                rotateLeft(grandParent);
                return rotateLeft(parent);
            }
        }
    }

    Node* splay(Node *x)
    {
        while(x->parent)
        {
            Node *parent = x->parent;
            if(!parent->parent) x = zig(x);
            else x = zigZag(x);
        }
        return x;
    }

    int find(int key)
    {
        Node *x = root;
        int depth = 0;
        while(x)
        {
            if(x->key == key) {
                root = splay(x);
                return depth;
            }
            else if(x->key > key) x = x->left;
            else x = x->right;
            depth++;
        }
        return -1;
    }

    int insert(int key)
    {
        Node *x = root;
        Node *parent = nullptr;
        int depth = 0;
        while(x)
        {
            parent = x;
            if(x->key == key) return -1;
            else if(x->key > key) x = x->left;
            else x = x->right;
            depth++;
        }
        Node *newNode = new Node(key);
        newNode->parent = parent;
        if(!parent) root = newNode;
        else if(parent->key > key) parent->left = newNode;
        else parent->right = newNode;
        // root = splay(newNode);
        return depth;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll s, u, b, n, i, q, p;
    cin >> s >> u >> b >> n >> i >> q >> p;

    RGN rgn(s);
    SplayTree st;

    for(int j = 0; j < b; j++)
        st.insert(rgn.next() % u);
    
    for(int j = 0; j < n; j++) {
        int op = rgn.next() % (i + q), ans = 0;
        if(op < i) {
            int key = rgn.next() % u;
            ans = st.insert(key);
            if(j % p == 0)
                cout << "I " << key << " " << ans << "\n";
        }
        else {
            int key = rgn.next() % u;
            ans = st.find(key);
            if(j % p == 0)
                cout << "Q " << key << " " << ans << "\n";
        }
    }
    return 0;
}