#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll R = (1LL << 32), A = 1664525, C = 1013904223;

struct minQueue {
    deque<ll> queue;
    deque<pair<ll, int>> possibleMin;
    ll offset = 0LL;

    void push(ll x) {
        queue.push_back(x);
        while (!possibleMin.empty() && possibleMin.back().first > x)
            possibleMin.pop_back();
        possibleMin.push_back({x, queue.size() - 1 + offset});
    }

    void pop() {
        if (queue.front() == possibleMin.front().first)
            possibleMin.pop_front();
        queue.pop_front();
        offset++;
    }

    pair<ll, int> getMin() {
        return possibleMin.front();
    }
};

ll nxtRand(ll &seed) {
    return seed = (A * seed + C) % R;
}

int main()
{
    ll seed, burn_in, n, p;
    cin >> seed >> burn_in >> n >> p;

    minQueue q;

    for(int i = 0; i < burn_in; i++){
        q.push(seed);
        nxtRand(seed);
    }

    for(int i = 0; i < n; i++){
        if((seed % 10) < p){
            nxtRand(seed);
            q.push(seed);
        } else{
            q.pop();
        }

        nxtRand(seed);
        cout << q.possibleMin.size() << ' ' << q.getMin().second - q.offset << '\n';
    }
    
    return 0;
}
