/*
Splay 模板
原题链接：https://www.luogu.com.cn/problem/P3391
更新时间：2021/11/16
*/

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
int n, m;

struct Node{
    int son[2], fa, val; // 节点的左儿子（son[0]）、右儿子（son[1]）、父亲、值
    int size; // 子树的大小（包括自己）
    bool flag; // 懒标记，是否应被翻转
    void Init(int _val, int _fa) // 初始化
    {
        val = _val, fa = _fa;
        size = 1;
    }
}tr[N];
int root, idx; // 根节点、节点总数

void PushUp(int x) // 向上传子树的大小
{
    tr[x].size = tr[tr[x].son[0]].size + tr[tr[x].son[1]].size + 1;
}

void PushDown(int x) // 向下传旋转的懒标记
{
    if (tr[x].flag)
    {
        swap(tr[x].son[0], tr[x].son[1]);
        tr[tr[x].son[0]].flag ^= 1, tr[tr[x].son[1]].flag ^= 1;
        tr[x].flag = false;
    }
}

void Rotate(int x) // 旋转（左旋、右旋二合一）
{
    int y = tr[x].fa, z = tr[y].fa; // y 是 x 的父亲，z 是 y 的父亲
    int k = tr[y].son[1] == x; // 如果 x 是 y 的左儿子，k 等于 0；否则 k 等于 1
    tr[z].son[tr[z].son[1] == y] = x, tr[x].fa = z; // 傻逼东西
    tr[y].son[k] = tr[x].son[k ^ 1], tr[tr[x].son[k ^ 1]].fa = y;
    tr[x].son[k ^ 1] = y, tr[y].fa = x;
    PushUp(y), PushUp(x);
}

void Splay(int x, int k) // 将 x 节点旋转为 k 节点的儿子
{
    while (tr[x].fa != k) // 还没旋到 k 节点的儿子
    {
        int y = tr[x].fa, z = tr[y].fa; // y 是 x 的父亲，z 是 y 的父亲
        if (z != k) // 至少还需旋转 2 次
        {
            if ((tr[y].son[1] == x) ^ (tr[z].son[1] == y)) // 如果 z、x、y 的关系不是一条直线，就先旋转 x（为了保证时间复杂度）
                Rotate(x);
            else
                Rotate(y); // 否则应先旋转 y
        }
        Rotate(x); // 再旋转一次
    }
    if (k == 0) // 如果 x 是根节点
        root = x;
}

void Insert(int val) // 插入值为 val 的节点（原先不存在）
{
    int u = root, fa = 0; // u 是 val 应存的位置，fa 是 u 的父节点
    while (u) // 从根节点开始找 u 的位置
        fa = u, u = tr[u].son[val > tr[u].val]; // 如果 val 小于当前节点的值，在其左子树中找；反之，右子树
    u = ++idx; // 增加节点
    if (fa)
        tr[fa].son[val > tr[u].val] = u; // 更新其父节点
    tr[u].Init(val, fa); // 初始化这个点（值为 val，父亲为 fa，子树大小为 1）
    Splay(u, 0); // 将这个点旋转上去（保证时间复杂度）
}

int GetK(int k) // 查询序列中第 k 个数
{
    int u = root;
    while (true)
    {
        PushDown(u); // 查询前先下传懒标记
        if (tr[tr[u].son[0]].size >= k) // 第 k 个数在左子树中
            u = tr[u].son[0];
        else if (tr[tr[u].son[0]].size + 1 == k) // 第 k 个数就是 u
            return u;
        else
            k -= tr[tr[u].son[0]].size + 1, u = tr[u].son[1]; // 第 k 个数在右子树中（类似于 Treap）
    }
}

void Print(int u) // 顺序输出
{
    PushDown(u); // 查询前先下传懒标记
    if (tr[u].son[0]) // 左子树有东西
        Print(tr[u].son[0]);
    if (tr[u].val >= 1 && tr[u].val <= n) // 本身有值
        cout << tr[u].val << " ";
    if (tr[u].son[1]) // 右子树有东西
        Print(tr[u].son[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++) // 插入 0、n + 1 作为边界
        Insert(i);
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        l = GetK(l), r = GetK(r + 2); // 本来应是 l - 1、 r + 1，但序列有边界 0，占用了一个编号
        Splay(l, 0), Splay(r, l); // 旋转，使翻转的区间 [l, r] 恰好处于 r 的左子树（编号大于 l、小于 r）
        tr[tr[r].son[0]].flag ^= 1;
    }
    Print(root);
    return 0;
}