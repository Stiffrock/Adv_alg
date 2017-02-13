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


//Ta en nod, k�r bfs p� den s� m�nga g�nger det finns noder. 
//N�r den tr�ffar en annan nod: L�gg till den noden i exclude -> L�gg till den noden i bfs(noden)s endings, break.
//Eftersom den funna noden ligger i exclude kommer den inte k�ras utan n�sta nod hittas
//N noder ska ha n-1 endings.

void bfs(endpoint &p) // point endp)
{
	point startp;
	startp.x = p.p.x; startp.y = p.p.y;

	for (int i = 0; i < 50; i++)			//S�tt alla distanser till 0 och alla noders visited till false;
		for (int j = 0; j < 50; j++)
		{
			visited[i][j] = false;
			dist[i][j] = 99;
		
		}


	for (int i = 0; i < exclude.size(); i++) //exclude vector som har alla positioner som ska uteslutas ur s�kningen
	{
		ex[exclude[i].x][exclude[i].y] = true; //Alla noder som ska uteslutas ur s�kningen
	}

	queue<point> q;			// en ide �r att l�ta endpoint minnas var den redan har varit. S� att efter den breakar kan den bara �teruppta d�r den slutade.
	q.push(startp);			// ide 2 vad �r det som s�ger att man m�ste k�ra en bfs f�r varje ending? Bara spara undan v�rdet n�r den tr�ffar en alien och l�t samma bfs forts�tta?
	visited[startp.x][startp.y] = true;
	dist[startp.x][startp.y] = 0;

	while (!q.empty())
	{
		point u = q.front();
		point v;
		q.pop();

		if ((A[u.x][u.y] == 'A' || A[u.x][u.y] == 'S') && ex[u.x][u.y] == false) // Om bfs tr�ffar en A/S L�gg en i bfs(nodens)endings och i exclude, break.
		{
			//ans.push_back(dist[u.x][u.y]);
			u.d = dist[u.x][u.y];
			p.endings.push_back(u);
			ex[u.x][u.y] = true;
			exclude.push_back(u);			//N�r den tr�ffar en Alien/Start som inte har tr�ffats innan l�gg den i exclude.
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
	//Kolla igenom en nods alla endings, l�gg till minsta
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
		for (int i = 0; i < 50; i++)			//S�tt alla distanser till 0 och alla noders visited till false;
			for (int j = 0; j < 50; j++)
			{
				ex[i][j] = false;
			}

		for (int i = 0; i < endp.size(); i++) // BFSen ska k�ras f�r varje nod
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
		//K�r tills du tr�ffar en Alien, breaka och ta bort f�reg�ende Alien. K�r bfs och utg� fr�n din nya position.
		//Eller s� behver du bara k�ra en bfs per alien, och n�r du tr�ffar en annan alien breakar du f�r d� har du hittat den Aliens kortaste v�g till en annan.

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