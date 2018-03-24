//задача https://www.e-olymp.com/ru/problems/1947

#include <bits/stdc++.h>

using namespace std;

vector<bool> used; //была ли посещена вершина
vector<vector<int>> g; //исходный граф
vector<vector<int>> gr; //граф с инвертированными ребрами
vector<int> topSort; //топологическая сортировка исходного графа
vector<int> componentIds; //номера компонент связности для каждой вершины

void dfs(int v) //обход в глубину для построения топологической сортировки
{
    used[v] = true;
    for (int to : g[v])
    {
        if (!used[to])
            dfs(to);
    }
    topSort.push_back(v);
}

void markComponentsDfs(int v, int id) //обход в глубину для пометки компонент связности
{
    used[v] = true;
    componentIds[v] = id;
    for (int to : gr[v])
        if (!used[to])
            markComponentsDfs(to, id);
}

size_t countEdges() //подсчет уникальных ребер в конденсированном графе
{
    set<pair<int, int>> edges;
    for (size_t v = 0; v < g.size(); ++v)
    {
        for (int to : g[v])
        {
            if (componentIds[v] != componentIds[to])
                edges.emplace(componentIds[v], componentIds[to]);
        }
    }
    return edges.size();
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    g.resize(n);
    gr.resize(n);
    for (size_t i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        --from, --to;
        g[from].push_back(to);
        gr[to].push_back(from);
    }

    used.assign(n, false);
    for (size_t i = 0; i < n; ++i)
    {
        if (!used[i])
            dfs(i);
    }
    reverse(topSort.begin(), topSort.end());

    used.assign(n, false);
    componentIds.resize(n);
    for (size_t i = 0, id = 0; i < n; ++i)
    {
        if (!used[topSort[i]])
            markComponentsDfs(topSort[i], id++);
    }

    cout << countEdges() << endl;

    return 0;
}
