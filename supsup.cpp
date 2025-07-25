/*
  2 SAT Problem
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define pb push_back
#define fi first
#define se second

const int N = 5e5 + 5, E = 5e5 + 5;

#define neig(a, u, v, e) for (int e = a.head[u], v; (~e) && (v = a.to[e], 1); e = a.nxt[e])

struct Adj
{
    int n, edcnt, head[N], nxt[E], to[E];
    void addEdge(int u, int v)
    {
        nxt[edcnt] = head[u];
        head[u] = edcnt;
        to[edcnt] = v;
        edcnt++;
    }

    void init()
    {
        edcnt = 0;
        memset(head, -1, n * sizeof(head[0]));
    }
} adj;

int low[N], dfst[N], curt, nodes[N], ndcnt, comps, comp[N];
int vis[N], vid;

void dfs(int u)
{
    vis[u] = vid;
    dfst[u] = low[u] = curt++;
    nodes[ndcnt++] = u;
    comp[u] = -1;
    neig(adj, u, v, e)
    {
        if (vis[v] != vid)
        {
            dfs(v);
            low[u] = min(low[v], low[u]);
        }
        else if (comp[v] == -1)
        {
            low[u] = min(low[u], low[v]);
        }
    }
    if (dfst[u] == low[u])
    {
        do
        {
            comp[nodes[--ndcnt]] = comps;
        } while (nodes[ndcnt] != u);
        comps++;
    }
}

void tarjan()
{
    vid++;
    ndcnt = 0;
    comps = 0;
    curt = 0;
    for (int i = 0; i < adj.n; i++)
    {
        if (vis[i] != vid)
            dfs(i);
    }
}

bool twoSat()
{
    tarjan();
    for (int i = 0; i < adj.n; i += 2)
    {
        if (comp[i] == comp[i + 1])
            return 0;
    }
    return 1;
}

int var(int x)
{
    return x << 1;
}
int notvar(int x)
{
    return x ^ 1;
}

void addor(int x, int y)
{
    adj.addEdge(notvar(x), y);
    adj.addEdge(notvar(y), x);
}

int n;
int t[105], sup[105][105], pl[105][105];
map<int, vector<int>> al;
char c;

int main()
{
    while (1)
    {
        scanf("%d", &n);
        al.clear();
        if (n == 0)
            break;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &t[i]);
            cnt += t[i];
            for (int j = 0; j < t[i]; j++)
            {
                scanf("%d", &sup[i][j]);
                cin >> c;
                pl[i][j] = (c == 'S');
            }
        }
        adj.n = 4 * cnt;
        adj.init();
        int cn = 0;
        int cn2 = cnt;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < t[i]; j++)
            {
                int id = var(cn);
                cout << "Squad " << i << ", Supply " << j << " -> id (var(cn)): " << id << endl;

                al[sup[i][j]].pb(id);
                id += pl[i][j];
                cout << "Updated id with pl[i][j]: " << id << " (pl[i][j] = " << pl[i][j] << ")" << endl;
                cout << "Value of ID : " << id << "Value of CN2 : " << cn2 << endl;
                cout << "Adding OR: (" << notvar(id) << ", " << var(cn2) << ")" << endl;
                addor(notvar(id), var(cn2));

                if (j > 0)
                {
                    cout << "(" << notvar(var(cn2 - 1)) << ", " << var(cn2) << ")" << endl;
                    addor(notvar(var(cn2 - 1)), var(cn2));

                    cout << "(" << notvar(id) << ", " << notvar(var(cn2 - 1)) << ")" << endl;
                    addor(notvar(id), notvar(var(cn2 - 1)));
                }

                cn++;
                cn2++;
                cout << endl;
            }
        }
        cout << "SUPPLY" << endl;
        for (auto &u : al)
        {
            if (u.se.size() >= 2)
            {
                for (int j = 1; j < u.se.size(); j++)
                {
                    cout << "(" << notvar(u.se[j]) << ", " << u.se[j - 1] << ")" << endl;
                    addor(notvar(u.se[j]), u.se[j - 1]);

                    cout << "(" << notvar(u.se[j - 1]) << ", " << u.se[j] << ")" << endl;
                    addor(notvar(u.se[j - 1]), u.se[j]);
                }
            }
        }

        if (twoSat())
        {
            puts("March onward");
        }
        else
        {
            puts("Coordination issue");
        }
    }

    return 0;
}
