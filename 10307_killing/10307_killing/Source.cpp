#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

char A[50][50];
int dist[50][50];
bool visited[50][50];
bool excl[50][50];
vector<int> ans;

int c, n, m;


struct point
{
	int x, y, d;
};

struct endpoint
{
	point p;

	vector<point> endings;

	vector<int> node;
};

vector<endpoint> endingpoints;
vector<point> exclude;


void Reset()
{
	endingpoints.clear();
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			A[i][j] = '\0';
			dist[i][j] = 0;
			visited[i][j] = false;

		}
	}
}


int bfs(point &startp, point &endp) // point endp)
{

	for (int i = 0; i < 50; i++)			//Sätt alla distanser till 0 och alla noders visited till false;
		for (int j = 0; j < 50; j++)
		{
			visited[i][j] = false;
			dist[i][j] = 99;
		}
	
	queue<point> q;	
	q.push(startp);
	visited[startp.x][startp.y] = true;
	dist[startp.x][startp.y] = 0;	
				

	while (!q.empty())
	{
		point u = q.front();
		q.pop();

		if (u.x == endp.x && u.y == endp.y && dist[u.x][u.y] != 0)
		{

			return dist[u.x][u.y];
		}		

		if (u.x >= 0 && u.x < n && A[u.x + 1][u.y] != '#' && A[u.x + 1][u.y] != '\0' && visited[u.x + 1][u.y] == false)
		{
			visited[u.x + 1][u.y] = true;
			dist[u.x + 1][u.y] = dist[u.x][u.y] + 1;
			point v;
			v.x = u.x + 1; v.y = u.y;
			q.push(v);
		}

		if (u.y >= 0 && u.y < m && A[u.x][u.y + 1] != '#' && A[u.x][u.y + 1] != '\0' && visited[u.x][u.y + 1] == false)
		{
			visited[u.x][u.y + 1] = true;
			dist[u.x][u.y + 1] = dist[u.x][u.y] + 1;
			point v;
			v.x = u.x; v.y = u.y + 1;
			q.push(v);
		}

		if (u.x > 0 && u.x <= n && A[u.x - 1][u.y] != '#' && A[u.x - 1][u.y] != '\0' && visited[u.x - 1][u.y] == false)
		{
			visited[u.x - 1][u.y] = true;
			dist[u.x - 1][u.y] = dist[u.x][u.y] + 1;
			point v;
			v.x = u.x - 1; v.y = u.y;
			q.push(v);
		}

		if (u.y > 0 && u.y <= n && A[u.x][u.y - 1] != '#' && A[u.x][u.y - 1] != '\0' && visited[u.x][u.y - 1] == false)
		{

			visited[u.x][u.y - 1] = true;
			dist[u.x][u.y - 1] = dist[u.x][u.y] + 1;
			point v;
			v.x = u.x; v.y = u.y - 1;
			q.push(v);
		}
	}
	return 99;
}

int minKey(vector<int> key, vector<bool> mstSet, vector<endpoint> ep)
{
	// Initialize min value
	int min = 99, min_index = 0;

	for (int v = 0; v < ep.size(); v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
int prim2(vector<endpoint> ep)
{
	vector<int> parent;
	vector<bool> mstSet;
	vector<int> key;
	int res = 0;
	int count = 0;
	for (int i = 0; i < ep.size(); i++)
	{
		parent.push_back(99);
		mstSet.push_back(false);
		key.push_back(99);
	}

	key[0] = 0;
	parent[0] = -1;

	for (int i = 0; i < ep.size(); i++)
	{
		int u = minKey(key, mstSet, ep);
		mstSet[u] = true;						//Välj vilken nod som skall kollas och få en edge

		for (int j = 0; j < ep.size(); j++)
		{
			if (ep[u].node[j] != 0				// om grafens värde inte är noll
				&& mstSet[j] == false			// Om denna noden inte redan har blivit behandlad
				&& ep[u].node[j] < key[j])		//kolla varje varje koppling till denna noden om de har en nyckel som är mindre.
			{				
				parent[j] = u;
				key[j] = ep[u].node[j];	
			}
			key;
		}
	}
	for (int i = 0; i < ep.size(); i++)
	{
		count += key[i];		
	}

	return count;
}


int main()
{
	cin >> c;
	while (c--)
	{
		cin >> n >> m;
		vector<point> endp;
		point startp;
		string input;
		cin.get();
		for (int i = 0; i < m; i++)
		{
			getline(cin, input);
			for (int j = 0; j < input.length(); j++)
			{
				A[i][j] = input[j];
				if (input[j] == 'S' || input[j] == 'A')
				{
					point p;
					p.x = i; p.y = j;
					endp.push_back(p);
				}
			}
		}

		for (int i = 0; i < endp.size(); i++) // BFSen ska köras för varje nod
		{
			endpoint p;
			p.p = endp[i];
			for (int j = 0; j < endp.size(); j++)
			{
				endp[j].d = bfs(endp[i], endp[j]);
				p.node.push_back(endp[j].d);
				p.endings.push_back(endp[j]);
			}
			endingpoints.push_back(p);
		}
	
		dist;
		int result = prim2(endingpoints);
		ans.push_back(result);
		Reset();
	}
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
//	cin.get();
	return 0;
}