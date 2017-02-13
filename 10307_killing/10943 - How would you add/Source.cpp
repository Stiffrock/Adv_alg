#include <iostream>
#include <vector>

using namespace std;
long long A[101][101];
long long B[101][101];
long long C[101][101];


//Man bygger ut allt arrayen allt eftersom. 
// Om vi s�ger k = 2 n = 5, d� kollar man f�rst p� d�r n �r 1 och k �r 1.
//Detta motsvarar 1 v�g d� vi inte kan addera med n�got k = 1;
//D�refter expanderar man och kollar n = 2. Det blir ocks� 1 eftersom vi inte kan addera med n�got k =1 samma �nda upp till 5; == 1 1 1 1 1
//D�refter kollar vi k = 2. H�r kan vi b�rja addera siffror.
//Om k = 2 och n = 1, kom ih�h att n motsvarar antalet v�gar som kollas f�r stunden.
// s� n = 1 inneb�r att det finns tv� v�gar att g� och eftersom k = 2 motsvarar det n = 1 k = 2;
// D� h�mtar man resultatet fr�n k = 1, n = 1 och adderar det med k = 2, n = 1 vilket blir 1; (d� f�rsta v�rdet �r 0);
// d�refter expanderar man till k = 2, n = 2; Nu har vi tv� siffror och tv� niv�er.
// eftersom k = 2, kan vi g� tv� v�gar exempel: 1 + 0 och 0 + 1. 

//D� tar vi antalet v�gar man kunde g� i k = 1, f�r n = 1 och n = 2 och l�gger ihop dem == 1 + 1 = 2;
//Expanderar vi sedan antalet n = 3. m�ste vi h�mta antalet v�gar som gick att g� i n = 1,2,3 och l�gga ihop dom.
// detta motsvarar om n = 3, 3+0, 0+3, 1+2,2+1 = 4 v�gar.
//Varje g�ng man g�r ner en niv� i k r�knar man v�garna f�r varje n
//S� om k �r 3 och n �r 3 b�rjar man �nd� med n = 0 och kollar antalet v�gar d�rifr�n.
//Och eftersom man redan har v�garna utr�knade f�r n�r k=1 n=1....5  kan man addera dem.
//S� om k var 2 och n var 0 hade vi 1 v�g att g� (1+0) om n ist�llet var 1 hade vi b�de 0+1 och 1+0 s� 2 v�gar.
//S�tter vi d� k = 3 och n = 0 kan vi direkt h�mta antalet v�gar f�r n�r k = 0 k = 1 == 1
//vi kan �ven g�ra samma sak f�r n = 1, d� adderar vi v�garna som fanns f�r k = 2 d�r n = 0 och n = 1 �s� f�r vi v�garna f�r n = 1 d� k=3
//detta skulle motsvara 1+0+0 ,0+1+0, 0+0+1.

//Det viktigaste h�r som d� ocks� �r DP �r att man tar det ett k och ett n i taget och sedan expanderar p� det.
//Kollar vad varje f�r f�r antal v�gar och sen g�r vidare, inte f�rr�n hela �r klart, i slutet har man n=5 och k = 3;

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
		A[1][i] = 1; // F�r n�r k = 1 �r det alltid en v�g att g� bara.
	}

	for (int k = 2; k <= K; ++k) // b�rja p� 2 d� k = 0 kommer f�rs�ka ta fr�n 0-1 och k = 1 kommer ta fr�n 0;
	{
		for (int n = 0; n <= N; ++n) //
		{
			for (int i = n; i >= 0; --i)	// anv�nder n - i, sedan i--, f�r att hela tiden b�rja p� 0 d� f�rsta steget i - n alltid blir 0, exempel d� n �r 2 s�tts i till tv� vilket get n - i = 0 (2-2), d�refter i-- get n - i (2-1) = 1. p� det s�ttet g�r r�knaren upp�t men �nd� b�rjar p� 0.
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