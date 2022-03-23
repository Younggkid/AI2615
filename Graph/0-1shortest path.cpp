#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct edgenode
{
	int end;
	edgenode* next;
	bool weight;

	edgenode(int e,  bool w, edgenode* n = NULL)
	{
		end = e;
		next = n;
		weight = w;
	}
};

struct vernode
{
	int data;
	edgenode* head;

	vernode(int d, edgenode* h = NULL)
	{
		data = d; head = h;
	}
	vernode(const vernode& x)
	{
		data = x.data; head = x.head;
	}
	vernode()
	{
		data = 0; head = NULL;
	}
};
class adjListGraph
{
private:
	int Vers;//节点数
	int Edges;//边数

public:
	vernode* verlist;
	adjListGraph(int vSize)
	{
		Vers = vSize;
		Edges = 0;
		verlist = new vernode[vSize + 1];
		for (int i = 1; i < Vers + 1; ++i)
		{
			verlist[i].data = i;
			verlist[i].head = NULL;
		}
	}//构造函数，初始化点数边数和邻接表点数据
	void insert(int x, bool w,int y)
	{

		verlist[x].head = new edgenode(y, w, verlist[x].head);
		Edges++;
	}
	bool exist(int x, int y)
	{
		if (Edges == 0) return 0;
		int u = x, v = y;
		edgenode* p = verlist[u].head;
		//if (!p) return 0;
		while (p)
		{
			if (p->end == v) return 1;
			p = p->next;
		}
		return 0;
	}

	~adjListGraph()
	{
		for (int i = 0; i < Vers; ++i)
		{
			edgenode* p = verlist[i].head, * q;
			while (p)
			{
				q = p->next;
				delete p;
				p = q;
			}
			verlist[i].head = NULL;
		}
		Edges = 0;
		delete[]verlist;
		Vers = 0;


	}
};

int main()
{
	int m = 0, n = 0;//n-number of vertex,m-number of edge,
	int s = 0, t = 0;//s-source t-terminal
	cin >> n >> m >> s >> t;


	adjListGraph mygraph(n);
	for (int i = 0; i < m; ++i)
	{
		int u = 0, v = 0;
		bool w = 0;
		cin >> u >> v >> w;
		mygraph.insert(u, w, v);
		mygraph.insert(v, w, u);
	}
	bool* marked = new bool[n + 1];
	int* dist = new int[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		marked[i] = 0;
		dist[i] = 0;
	}
	//initialize

	queue<int> Q;
	stack<int> S;
	Q.push(s);
	S.push(s);
	marked[s] = 1;
	while (!Q.empty())
	{
		int u = 0, v = 0;
		bool w = 0;

		while (!S.empty())
		{
			u = S.top();
			S.pop();
			edgenode* p = mygraph.verlist[u].head;
			while (p)
			{
				v = p->end;
				w = p->weight;
				p = p->next;
				if (marked[v] == 0)
				{
					if (w == 0)
					{
						marked[v] = 1;
						S.push(v);
						Q.push(v);
						dist[v] = dist[u];
					}
				}

			}

		}//搜遍w=0的点,并把它们全部入队，更新他们的距离
		u = Q.front();
		Q.pop();
		edgenode* p = mygraph.verlist[u].head;
		while (p)
		{
			v = p->end;
			w = p->weight;
			p = p->next;
			if (marked[v] == 0)
			{
				if (w == 1)
				{
					marked[v] = 1;
					Q.push(v);
					S.push(v);
					dist[v] = dist[u] + 1;
				}

			}
		}
	}
	//for (int i = 1; i <= n; ++i)
	//{
	//	cout << dist[i];
	//}

	cout << dist[t];
	return 0;
}