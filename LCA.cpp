/*
最近公共祖先模板（在线）
原题链接：https://www.luogu.com.cn/problem/P3379
更新时间：2021/11/15
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;
const int N = 500010, M = 1000010;
int n, m, s, t;
int tot, head[N], ver[M], nxt[M];
int depth[N], fa[N][20];

void Add(int u, int v)
{
    ver[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void Init()
{
    queue<int> Q;
    depth[s] = 1;
    Q.push(s);
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (depth[y])
                continue;
            Q.push(y);
            depth[y] = depth[x] + 1;
            fa[y][0] = x;
            for (int j = 1; j <= t; j++)
                fa[y][j] = fa[fa[y][j - 1]][j - 1];
        }
    }
}

int Lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int i = t; i >= 0; i--)
        if (depth[fa[u][i]] >= depth[v])
            u = fa[u][i];
    if (u == v)
        return u;
    for (int i = t; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    t = log2(n) + 1;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }

    Init();

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        cout << Lca(u, v) << "\n";
    }
    return 0;
}