#include <iostream>
#include <vector>

using namespace std;
long long A[101][101];
long long B[101][101];
long long C[101][101];


//Man bygger ut allt arrayen allt eftersom. 
// Om vi säger k = 2 n = 5, då kollar man först på där n är 1 och k är 1.
//Detta motsvarar 1 väg då vi inte kan addera med något k = 1;
//Därefter expanderar man och kollar n = 2. Det blir också 1 eftersom vi inte kan addera med något k =1 samma ända upp till 5; == 1 1 1 1 1
//Därefter kollar vi k = 2. Här kan vi börja addera siffror.
//Om k = 2 och n = 1, kom ihåh att n motsvarar antalet vägar som kollas för stunden.
// så n = 1 innebär att det finns två vägar att gå och eftersom k = 2 motsvarar det n = 1 k = 2;
// Då hämtar man resultatet från k = 1, n = 1 och adderar det med k = 2, n = 1 vilket blir 1; (då första värdet är 0);
// därefter expanderar man till k = 2, n = 2; Nu har vi två siffror och två nivåer.
// eftersom k = 2, kan vi gå två vägar exempel: 1 + 0 och 0 + 1. 

//Då tar vi antalet vägar man kunde gå i k = 1, för n = 1 och n = 2 och lägger ihop dem == 1 + 1 = 2;
//Expanderar vi sedan antalet n = 3. måste vi hämta antalet vägar som gick att gå i n = 1,2,3 och lägga ihop dom.
// detta motsvarar om n = 3, 3+0, 0+3, 1+2,2+1 = 4 vägar.
//Varje gång man går ner en nivå i k räknar man vägarna för varje n
//Så om k är 3 och n är 3 börjar man ändå med n = 0 och kollar antalet vägar därifrån.
//Och eftersom man redan har vägarna uträknade för när k=1 n=1....5  kan man addera dem.
//Så om k var 2 och n var 0 hade vi 1 väg att gå (1+0) om n istället var 1 hade vi både 0+1 och 1+0 så 2 vägar.
//Sätter vi då k = 3 och n = 0 kan vi direkt hämta antalet vägar för när k = 0 k = 1 == 1
//vi kan även göra samma sak för n = 1, då adderar vi vägarna som fanns för k = 2 där n = 0 och n = 1 ¨så får vi vägarna för n = 1 då k=3
//detta skulle motsvara 1+0+0 ,0+1+0, 0+0+1.

//Det viktigaste här som då också är DP är att man tar det ett k och ett n i taget och sedan expanderar på det.
//Kollar vad varje får för antal vägar och sen går vidare, inte förrän hela är klart, i slutet har man n=5 och k = 3;

int alg2(int N, int K)
{
	long long res;

	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			A[i][j] = 0;
		}
	}

	for (int i = 0; i <= N; i++)
	{
		A[1][i] = 1; // För när k = 1 är det alltid en väg att gå bara.
	}

	for (int k = 2; k <= K; ++k) // börja på 2 då k = 0 kommer försöka ta från 0-1 och k = 1 kommer ta från 0;
	{
		for (int n = 0; n <= N; ++n) //
		{
			for (int i = n; i >= 0; --i)	// använder n - i, sedan i--, för att hela tiden börja på 0 då första steget i - n alltid blir 0, exempel då n är 2 sätts i till två vilket get n - i = 0 (2-2), därefter i-- get n - i (2-1) = 1. på det sättet går räknaren uppåt men ändå börjar på 0.
			{
				A[k][n] = (A[k][n] + A[k - 1][n - i]) % 1000000;
			}
		}
	}
	res = A[K][N];
	return res;
	cout << res;
}

int alg(int N, int K)
{
	//for (int i = 0; i <= K; i++)
	//{
	//	for (int j = 0; j <= N; j++)
	//	{
	//		B[i][j] = j;
	//	}
	//}


	//for (int n = 0; n < 0; n++)
	//
	//	for (int k = 0; k < K; k++)
	//	{
	//		for (int i = 0; i < N; i++)
	//		{
	//			int j = k;
	//			for (j; j < K; j++)
	//			{
	//				C[k][n] += B[j+1][i];// + B[j + 1][i];
	//			}
	//		}
	//	}
	//}
	

	return 0;
}

int main()
{
	int N, K;
	vector<int> ans;
	while (true)
	{
		scanf_s("%d%d", &N, &K);
		if (N == 0 && K == 0)
			break;
		ans.push_back(alg2(N, K));
	}
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
	cin.get();


}