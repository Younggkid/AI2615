#include <iostream>
using namespace std;
struct edgenode
{
	int end;
	edgenode* next;
	int weight;

	edgenode(int e, int w, edgenode* n = NULL)
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
	void insert(int x, int w, int y)
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
	cin >> n >> m;

	adjListGraph mygraph(n);
	for (int i = 0; i < m; ++i)
	{
		int u = 0, v = 0;
		int w = 0;
		cin >> u >> v >> w;
		mygraph.insert(u, w, v);
	}

	int* dist = new int[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		dist[i] = 1e5;
	}
	int s = 2;
	dist[s] = 0;
	for (int i = 0; i < n-1; ++i)
	{
		for (int i = 1; i <= n; ++i)
		{
			edgenode* p = mygraph.verlist[i].head;
			int v = 0, w = 0;
			while (p)
			{
				v = p->end;
				w = p->weight;
				p = p->next;
				if (dist[v] > dist[i] + w)
				{
					dist[v] = dist[i] + w;
				}
			}
		}
	}
	bool flag = false;
	for (int i = 1; i <= n; ++i)
	{
		edgenode* p = mygraph.verlist[i].head;
		int v = 0, w = 0;
		while (p)
		{
			v = p->end;
			w = p->weight;
			p = p->next;
			if (dist[v] > dist[i] + w)
			{
				dist[v] = dist[i] + w;
				flag = true;
			}
		}
	}
	if (flag) cout << "Yes";
	else cout << "No";
	
	
}

