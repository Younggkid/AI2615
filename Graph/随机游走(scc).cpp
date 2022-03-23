#include <iostream>
#include <vector>
using namespace std;
struct edgenode
{
	int end;
	edgenode* next;

	edgenode(int e,  edgenode* n = NULL)
	{
		end = e;
		next = n;
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
	void insert(int x, int y)
	{

		verlist[x].head = new edgenode(y, verlist[x].head);
		Edges++;
	}
	~adjListGraph()
	{
		for (int i = 1; i < Vers+1; ++i)
		{
			edgenode* p ;
			while ((p = verlist[i].head)!=NULL)
			{
				verlist[i].head = p->next;
				delete p;
			}
		}
		delete[]verlist;


	}
};
void DFS1(adjListGraph *G,vector<int> &list, bool m[], int s,int n)
{
	
	if (m[s] == 0)
	{
		m[s] = 1;
		edgenode* p = G->verlist[s].head;
		while (p)
		{
			int v = p->end;
			p = p->next;
			if (m[v] == 0)
			{
				DFS1(G,list,m, v,n);

			}
		}
		list.push_back(s);//s is finished，维护了一个sorted list，完成时间升序
	}
	return;
}
int group = 0;
int cnt[2000000];
void DFS2(adjListGraph* G, int part[], int c[],bool m[], int s, int n)
{
	
	if (m[s] == 0)
	{
		m[s] = 1;
		part[s] = group;
		c[part[s]]++;
		edgenode* p = G->verlist[s].head;
		while (p)
		{
			int v = p->end;
			p = p->next;
			if (m[v] == 0)
			{
				part[v] = part[s];
				DFS2(G, part, c,m, v, n);

			}
		}
		
	}
	return;
}
int main()
{
	int m = 0, n = 0;//n-number of vertex,m-number of edge,
	cin >> n >> m;
	adjListGraph *G=new adjListGraph(n);
	adjListGraph *GR=new adjListGraph(n);

	for (int i = 0; i < m; ++i)
	{
		int u = 0, v = 0;
		cin >> u >> v ;
		G->insert(u, v);
		GR->insert(v, u);

	}

	bool* G_marked = new bool[n + 1];
	bool* GR_marked = new bool[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		G_marked[i] = 0;
		GR_marked[i] = 0;
	}
	vector<int> sorted_list;
	for (int i = 1; i <= n; ++i)
	{
		DFS1(GR, sorted_list, GR_marked, i, n);//topological order
	}
	
	int* belong = new int[n + 1];
	for (int i = n-1; i >=0; --i)
	{
		if (G_marked[sorted_list[i]] == 0) group++;
		DFS2(G, belong, cnt,G_marked, sorted_list[i], n);
		//依据ssc对所有点进行分划
	}
	//cout << group << endl;
/*	for (int i = 1; i <=n; ++i)
	{
		cout << belong[i];
	}
	cout << endl;
	for (int i = 1; i <=group; ++i)
	{
		cout << cnt[i] ;
	}
	cout << endl;*/
	int *outdeg = new int[group+1];
	for (int i = 1; i <=group; ++i)
	{
		outdeg[i] = 0;
	}
	for (int i = 1; i <= n; ++i)
	{
		edgenode* p = G->verlist[i].head;
		while (p)
		{
			int v = p->end;
			if (belong[i] != belong[v])
			{
				outdeg[belong[i]]++;
				
			}
			p = p->next;
		}
	}

	int result = 0;
	for (int i = 1; i <=group; ++i)
	{
		if (outdeg[i] != 0) result+=cnt[i];
	}
	cout << result;
	
	return 0;

}




