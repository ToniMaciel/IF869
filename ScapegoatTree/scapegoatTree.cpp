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

struct Node
{
    int key, size;
    Node *left, *right, *parent;
    Node(int key) : key(key), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct ScapegoatTree
{
    Node *root;
    int n;
    double alpha;
    ScapegoatTree(double alpha) : root(nullptr), n(0), alpha(alpha) {}

    int size(Node *node) 
    { 
        return node == nullptr ? 0 : size(node->left) + size(node->right) + 1; 
    }
    
    pair<int, int> insert(int key)
    {
        Node *node = new Node(key);
        int h = insertAndFindDepth(node), new_h = h;
        
        if(h < 0)
            return {-1, -1};
        
        // Unbalanced tree check
        if(h > log(n) / log(1 / alpha)) 
        {
            Node *cur = node->parent;
            int distToNode = 1;
            while(cur != nullptr)
            {
                int s = size(cur);
                if(distToNode > log(s) / log(1 / alpha))
                {
                    rebuild(cur);
                    break;
                }
                distToNode++;
                cur = cur->parent;
            }

            // Calculates new depth after rebuilding
            Node *aux = node->parent;
            new_h = 0;
            while(aux != nullptr)
            {
                new_h++;
                aux = aux->parent;
            }
        }

        return {h, new_h};
    }
    
    int insertAndFindDepth(Node *node)
    {
        int h = 0;
        if(root == nullptr) {
            root = node;
            n++;
            return h;
        }

        Node *cur = root;
        while(true) {
            h++;
            if(node->key < cur->key) {
                if(cur->left == nullptr) {
                    cur->left = node;
                    node->parent = cur;
                    n++;
                    break;
                }
                else
                    cur = cur->left;
            }
            else if(node->key > cur->key) {
                if(cur->right == nullptr) {
                    cur->right = node;
                    node->parent = cur;
                    n++;
                    break;
                }
                else
                    cur = cur->right;
            }
            else
                return -1;
        }

        return h;
    }

    void rebuild(Node *node)
    {
        int s = size(node);
        Node *p = node->parent;
        Node **arr = new Node* [s];
        storeInArray(node, arr, 0);

        if(p == nullptr)
        {
            root = buildBalancedFromArray(arr, 0, s - 1);
            root->parent = nullptr;
        }
        else if(p->left == node)
        {
            p->left = buildBalancedFromArray(arr, 0, s - 1);
            p->left->parent = p;
        }
        else
        {
            p->right = buildBalancedFromArray(arr, 0, s - 1);
            p->right->parent = p;
        }
    }

    int storeInArray(Node *node, Node *arr[], int i)
    {
        if(node == nullptr)
            return i;
        i = storeInArray(node->left, arr, i);
        arr[i++] = node;
        return storeInArray(node->right, arr, i);
    }

    Node *buildBalancedFromArray(Node **arr, int start, int end)
    {
        if(start > end)
            return nullptr;
        int mid = ceil((start + end) / 2.0);
        Node *node = arr[mid];
        node->left = buildBalancedFromArray(arr, start, mid - 1);
        if(node->left != nullptr)
            node->left->parent = node;
        node->right = buildBalancedFromArray(arr, mid + 1, end);
        if(node->right != nullptr)
            node->right->parent = node;
        return node;
    }

    int query(int key)
    {
        Node *cur = root;
        int depth = 0;
        while(cur != nullptr)
        {
            if(key < cur->key)
                cur = cur->left;
            else if(key > cur->key)
                cur = cur->right;
            else
                return depth;
            depth++;
        }
        return -1;
    }
};

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int S, U, B, N, I, Q, P;
    double A;
    cin >> S >> U >> A >> B >> N >> I >> Q >> P;
    
    RGN rgn(S);
    ScapegoatTree sg(A);

    for (int i = 0; i < B; i++)
        sg.insert(rgn.next() % U);
    
    for (int i = 0; i < N; i++) {
        int x = rgn.next() % (I + Q);
        int K = rgn.next() % U;
        if (x < I) {
            pair<int, int> ans = sg.insert(K);
            if (i % P == 0)
                cout << "I " << K  << " " << ans.first << " " << ans.second << '\n';
        }
        else {
            if (i % P == 0){
                int ans = sg.query(K);
                cout << "Q " << K << " " << ans << '\n';
            }
        }
    }

    return 0;
}