#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

char A[50][50];
int dist[50][50];
bool visited[50][50];
bool ex[50][50];
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
};

vector<endpoint> endingpoints;
vector<point> exclude;

//struct edge
//{
//	point u, v;
//	int d;
//
//	bool operator < (const edge& e1) const
//	{
//		return d < e1.d;
//	}
//};
//
//vector<edge> edges;

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


//Ta en nod, kör bfs på den så många gånger det finns noder. 
//När den träffar en annan nod: Lägg till den noden i exclude -> Lägg till den noden i bfs(noden)s endings, break.
//Eftersom den funna noden ligger i exclude kommer den inte köras utan nästa nod hittas
//N noder ska ha n-1 endings.

void bfs(endpoint &p) // point endp)
{
	point startp;
	startp.x = p.p.x; startp.y = p.p.y;

	for (int i = 0; i < 50; i++)			//Sätt alla distanser till 0 och alla noders visited till false;
		for (int j = 0; j < 50; j++)
		{
			visited[i][j] = false;
			dist[i][j] = 99;
		
		}


	for (int i = 0; i < exclude.size(); i++) //exclude vector som har alla positioner som ska uteslutas ur sökningen
	{
		ex[exclude[i].x][exclude[i].y] = true; //Alla noder som ska uteslutas ur sökningen
	}

	queue<point> q;			// en ide är att låta endpoint minnas var den redan har varit. Så att efter den breakar kan den bara återuppta där den slutade.
	q.push(startp);			// ide 2 vad är det som säger att man måste köra en bfs för varje ending? Bara spara undan värdet när den träffar en alien och låt samma bfs fortsätta?
	visited[startp.x][startp.y] = true;
	dist[startp.x][startp.y] = 0;

	while (!q.empty())
	{
		point u = q.front();
		point v;
		q.pop();

		if ((A[u.x][u.y] == 'A' || A[u.x][u.y] == 'S') && ex[u.x][u.y] == false) // Om bfs träffar en A/S Lägg en i bfs(nodens)endings och i exclude, break.
		{
			//ans.push_back(dist[u.x][u.y]);
			u.d = dist[u.x][u.y];
			p.endings.push_back(u);
			ex[u.x][u.y] = true;
			exclude.push_back(u);			//När den träffar en Alien/Start som inte har träffats innan lägg den i exclude.
			break;
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
}


int prim(vector<endpoint> ep)
{
	vector<int> MST;
	int res = 0;
	for (int i = 0; i < ep.size(); i++)
		MST.push_back(99);
	//Kolla igenom en nods alla endings, lägg till minsta
	for (int i = 0; i < ep.size(); i++)
	{
		int min = 99;
		for (int j = 0; j < ep[i].endings.size(); j++)
			if (min > ep[i].endings[j].d)
				min = ep[i].endings[j].d;
		res += min;
	}
	return res;

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
		for (int i = 0; i < 50; i++)			//Sätt alla distanser till 0 och alla noders visited till false;
			for (int j = 0; j < 50; j++)
			{
				ex[i][j] = false;
			}

		for (int i = 0; i < endp.size(); i++) // BFSen ska köras för varje nod
		{
			endpoint p;
			p.p = endp[i];

			for (int j = 0; j < endp.size(); j++)
			{
				bfs(p);
			}
			exclude.clear();
			endingpoints.push_back(p);

		}
		//Kör tills du träffar en Alien, breaka och ta bort föregående Alien. Kör bfs och utgå från din nya position.
		//Eller så behver du bara köra en bfs per alien, och när du träffar en annan alien breakar du för då har du hittat den Aliens kortaste väg till en annan.

		int result = prim(endingpoints);
		ans.push_back(result);
		Reset();
	}
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
	cin.get();
	return 0;
}
/*
#####
#A#A##
# # A#
#S  ##
#####
*/