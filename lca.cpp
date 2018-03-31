//http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=111796#1

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct Node
{
    vector<int> children;
    vector<int> binAncestors;
    size_t parent;
    size_t tIn, tOut;
};

vector<Node> g;
size_t MaxLog;

void dfs(size_t n, size_t& timer)
{
    g[n].tIn = ++timer;

    g[n].binAncestors.resize(MaxLog + 1);
    g[n].binAncestors[0] = g[n].parent;
    for (size_t i = 1; i < MaxLog + 1; ++i)
        g[n].binAncestors[i] = g[g[n].binAncestors[i - 1]].binAncestors[i - 1];

    for (int to : g[n].children)
    {
        g[to].parent = n;
        dfs(to, timer);
    }

    g[n].tOut = ++timer;
}

bool isDescendant(size_t ancestor, size_t n)
{
    return g[ancestor].tIn <= g[n].tIn &&
            g[ancestor].tOut >= g[n].tOut;
}

int getLCA(size_t v, size_t vv)
{
    if (isDescendant(v, vv)) return v;
    if (isDescendant(vv, v)) return vv;

    for (int l = MaxLog; l >= 0; --l)
    {
        if (!isDescendant(g[v].binAncestors[l], vv))
            v = g[v].binAncestors[l];
    }
    return g[v].parent;
}

int main()
{
    size_t n, m;
    cin >> n >> m;
    g.resize(n + 1);
    for (size_t i = 1; i < n; ++i)
    {
        size_t parent;
        cin >> parent;
        g[parent].children.push_back(i);
    }

    uint64_t a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;

    MaxLog = 1;
    while ((1 << MaxLog) <= n)
        ++MaxLog;

    size_t timer = 0;
    g[0].parent = 0;
    dfs(0, timer);

    size_t v = 0, ans = 0;
    for (size_t i = 0; i < m; ++i)
    {
        uint64_t q1 = (a1 + v) % n, q2 = a2;
        v = getLCA(q1, q2);
        ans += v;

        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }

    cout << ans << endl;

    return 0;
}
