#include <iostream>

using namespace std;
const int N = 200010;
int n;

struct Node
{
    int val, dist;
    int fa, l, r;
} tr[N];
int idx;

bool Compare(int x, int y)
{
    if (tr[x].val != tr[y].val)
        return tr[x].val < tr[y].val;
    return x < y;
}

int Find(int x)
{
    if (tr[x].fa != x)
        tr[x].fa = Find(tr[x].fa);
    return tr[x].fa;
}

int Merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (Compare(y, x))
        swap(x, y);
    tr[x].r = Merge(tr[x].r, y);
    if (tr[tr[x].r].dist > tr[tr[x].l].dist)
        swap(tr[x].l, tr[x].r);
    tr[x].dist = tr[tr[x].r].dist + 1;
    return x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    tr[0].val = 2e9;
    while (n--)
    {
        int t, x, y;
        cin >> t >> x;
        switch (t)
        {
        case 1:
            tr[++idx].val = x;
            tr[idx].dist = 1;
            tr[idx].fa = idx;
            break;
        case 2:
            cin >> y;
            x = Find(x), y = Find(y);
            if (x != y)
            {
                if (Compare(y, x))
                    swap(x, y);
                tr[y].fa = x;
                Merge(x, y);
            }
            break;
        case 3:
            cout << tr[Find(x)].val << "\n";
            break;
        default:
            x = Find(x);
            if (Compare(tr[x].r, tr[x].l))
                swap(tr[x].l, tr[x].r);
            tr[x].fa = tr[x].l, tr[tr[x].l].fa = tr[x].l;
            Merge(tr[x].l, tr[x].r);
            break;
        }
    }
    return 0;
}