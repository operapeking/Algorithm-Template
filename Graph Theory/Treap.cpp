/*
Treap 模板
原题链接：https://www.acwing.com/problem/content/description/255/
更新时间：2021/11/15
*/

#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010, inf = 1e8;
int n;
struct Node
{
    int l, r; // 左子树、右子树
    int key, val; // 当前节点存的点值
    int cnt, size; // 相同点值的的个数、其子树的大小（包括自己）
} tr[N];
int root, idx;

void PushUp(int p) // 更新当前子树的 size 值
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int GetNode(int key) // 新建节点
{
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void Zig(int &p) // 右旋
{
    int q = tr[p].l;
    tr[p].l = tr[q].r;
    tr[q].r = p;
    p = q;
    PushUp(tr[p].r), PushUp(p);
}

void Zag(int &p) // 左旋
{
    int q = tr[p].r;
    tr[p].r = tr[q].l;
    tr[q].l = p;
    p = q;
    PushUp(tr[p].l), PushUp(p);
}

void Build() // 初始化一个正无穷和一个负无穷
{
    GetNode(-inf), GetNode(inf);
    root = 1, tr[1].r = 2;
    PushUp(root);
    if (tr[root].val < tr[tr[root].r].val)
        Zag(root);
}

void Insert(int &p, int key)
{
    if (!p) // 新建一个点
        p = GetNode(key);
    else if (tr[p].key == key) // 就是这个点
        tr[p].cnt++;
    else if (tr[p].key > key) // 在它左子树中找
    {
        Insert(tr[p].l, key);
        if (tr[p].val < tr[tr[p].l].val)
            Zig(p);
    }
    else // 在它右子树中找
    {
        Insert(tr[p].r, key);
        if (tr[p].val < tr[tr[p].r].val)
            Zag(p);
    }
    PushUp(p);
}

void Remove(int &p, int key)
{
    if (!p) // 点不存在
        return;
    else if (tr[p].key == key) // 就是这个点
    {
        if (tr[p].cnt > 1) // 这个数不只有一个，就直接让个数减一
            tr[p].cnt--;
        else if (tr[p].l || tr[p].r)
        {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) // 如果它没有右子树，或其左子树的 val 大于其右子树的 val，就右旋再删（将当前节点旋到他右子树的位置）
            {
                Zig(p);
                Remove(tr[p].r, key);
            }
            else // 同理，如果它没有左子树，或其左子树的 val 小于其右子树的 val，就左旋再删（将当前节点旋到他左子树的位置）
            {
                Zag(p);
                Remove(tr[p].l, key);
            }
        }
        else
            p = 0;
    }
    else if (tr[p].key > key) // 在它左子树中找
        Remove(tr[p].l, key);
    else // 在它右子树中找
        Remove(tr[p].r, key);
    PushUp(p);
}

int GetRankByKey(int p, int key) // 通过值找排名
{
    if (!p) // 点不存在
        return 0;
    if (tr[p].key == key) // 就是这个点
        return tr[tr[p].l].size + 1;
    if (tr[p].key > key) // 在它左子树中找
        return GetRankByKey(tr[p].l, key);
    else // 在它右子树中找，当前点 、其左子树的所有点排名都在它之前
        return tr[tr[p].l].size + tr[p].cnt + GetRankByKey(tr[p].r, key);
}

int GetKeyByRank(int p, int Rank) // 通过排名找值
{
    if (!p) // 点不存在
        return 0;
    if (tr[tr[p].l].size >= Rank) // 在它左子树中找
        return GetKeyByRank(tr[p].l, Rank);
    if (tr[tr[p].l].size + tr[p].cnt >= Rank) // 就是这个点
        return tr[p].key;
    else // 在它右子树中找，在它左子树中排名为 Rank - tr[tr[p].l].size - tr[p].cnt 的数在整个树中的排名为 Rank
        return GetKeyByRank(tr[p].r, Rank - tr[tr[p].l].size - tr[p].cnt);
}

int GetPrev(int p, int key) // 求数值 x 的前驱（前驱定义为小于 x 的最大的数）
{
    if (!p)
        return -inf;
    if (tr[p].key >= key)
        return GetPrev(tr[p].l, key);
    return max(tr[p].key, GetPrev(tr[p].r, key));
}

int GetNext(int p, int key) // 求数值 x 的后继（后继定义为大于 x 的最小的数）
{
    if (!p)
        return inf;
    if (tr[p].key <= key)
        return GetNext(tr[p].r, key);
    return min(tr[p].key, GetNext(tr[p].l, key));
}

int main()
{
    ios::sync_with_stdio(false);
    Build();
    cin >> n;
    while (n--)
    {
        int op, x;
        cin >> op >> x;
        switch (op)
        {
        case 1:
            Insert(root, x);
            break;
        case 2:
            Remove(root, x);
            break;
        case 3:
            cout << GetRankByKey(root, x) - 1 << "\n";
            break;
        case 4:
            cout << GetKeyByRank(root, x + 1) << "\n";
            break;
        case 5:
            cout << GetPrev(root, x) << "\n";
            break;
        case 6:
            cout << GetNext(root, x) << "\n";
            break;
        }
    }
    return 0;
}