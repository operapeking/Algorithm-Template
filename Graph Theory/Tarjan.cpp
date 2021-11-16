/*
Tarjan 缩点模板
原题链接：https://www.acwing.com/problem/content/369/
更新时间：2021/11/15
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N = 110;
int n;
vector<int> support[N];
stack<int> S;

int dfn[N], low[N], ts;
int in_stk[N];
int scc_cnt, id[N], din[N], dout[N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++ts;
    S.push(u);
    in_stk[u] = true;
    for (int v : support[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stk[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        scc_cnt += 1;
        int y;
        do
        {
            y = S.top();
            S.pop();
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int in;
        while (cin >> in, in)
            support[i].push_back(in);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 1; i <= n; i++)
    {
        for (int j : support[i])
        {
            int id1 = id[i], id2 = id[j];
            if (id1 != id2)
                din[id2]++, dout[id1]++;
        }
    }
    int p = 0, q = 0;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (!din[i])
            p++;
        if (!dout[i])
            q++;
    }
    cout << p << endl;
    if (scc_cnt == 1)
        cout << 0;
    else
        cout << max(p, q);
    return 0;
}