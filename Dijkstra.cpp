/*
Dijkstra 模板
原题链接：https://www.luogu.com.cn/problem/P4779
更新时间：2021/11/15
*/

#include <cstring>
#include <iostream>
#include <queue>

using namespace std;
typedef pair<int, int> PII;
const int N = 100010, M = 400010;
int n, m, s;
int tot, head[N], ver[M], edge[M], nxt[M];
int dist[N];
bool vis[N];

void Add(int u, int v, int w)
{
    ver[++tot] = v;
    edge[tot] = w;
    nxt[tot] = head[u];
    head[u] = tot;
}

void Dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<PII, vector<PII>, greater<PII>> Q;
    dist[s] = 0;
    Q.push(make_pair(0, s));
    while (!Q.empty())
    {
        int x = Q.top().second;
        Q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = ver[i];
            if (dist[x] + edge[i] < dist[y])
            {
                dist[y] = dist[x] + edge[i];
                Q.push(make_pair(dist[y], y));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w);
    }
    Dijkstra();
    for (int i = 1; i <= n; i++)
        cout << dist[i] << " ";
    return 0;
}