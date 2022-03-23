#include <iostream>
#include <vector>
using namespace std;
int timee = 0;
struct edgenode
{
	int end;
	edgenode* next;

	edgenode(int e, edgenode* n = NULL)
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
		for (int i = 1; i < Vers + 1; ++i)
		{
			edgenode* p;
			while ((p = verlist[i].head) != NULL)
			{
				verlist[i].head = p->next;
				delete p;
			}
		}
		delete[]verlist;


	}
};
void DFS(adjListGraph* G, int finish[], bool m[], int s)
{
    
	if (m[s] == 0)
	{
		timee++;
		m[s] = 1;
		edgenode* p = G->verlist[s].head;
		while (p)
		{
			int v = p->end;
			p = p->next;
			if (m[v] == 0)
			{
				DFS(G, finish, m, v);
			}
		}
		finish[s] = timee;
		timee++;
	}
	return;
}
int main()
{
	int n = 0, p1 = 0, p2 = 0;
	cin >> n >> p1 >> p2;
	adjListGraph *G=new adjListGraph(n);
	for (int i = 0; i < p1; ++i)
	{
		int u, v;
		cin >> u >> v;
		G->insert(u, v);
	}
	bool* marked = new bool[n+1];
	int* finish = new int[n+1];
	for (int i = 1; i <=n; ++i)
	{
		marked[i] = 0;
		finish[i] = 0;
	}
	int* first = new int[p2];
	int* sec = new int[p2];
	for (int i = 0; i < p2; ++i)
	{
		cin >> first[i] >> sec[i];
	}
	
	
	for (int i = 1; i <=n; ++i)
	{
		DFS(G, finish, marked, i);//topological order
	}
	for (int i = 0; i < p2; ++i)
	{
		if (finish[first[i]] > finish[sec[i]])
		{
			cout << first[i] << " ";
			cout << sec[i] << endl;
		}
		else {
			cout << sec[i] << " ";
			cout << first[i] << endl;
		}
	//src should be the one with less finish time;
	return 0;

}

