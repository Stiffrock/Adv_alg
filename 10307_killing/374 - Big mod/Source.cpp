#include <iostream>

using namespace std;


////***Repeated Squaring
////+ use the relation that (x\times y){\bmod  m}=((x{\bmod  m})\times (y{\bmod  m})){\bmod  m}
//// Dela upp uträkningen i en liten del genom modulus realtionen


int alg(int B, int P, int M)
{

	if (P == 0)
	{
		return 1;
	}

	if (P % 2 == 0) // odd number
	{
		int temp = alg(B, P / 2, M);
		return  (temp*temp) % M;


	}
	else
		return  (B % M * alg(B, (P - 1), M)) % M;

}



int main()
{
	int B, P, M, ans;

	while (scanf("%d\n%d\n%d", &B, &P, &M) != EOF)
	{

		ans = alg(B, P, M);
		cout << ans << endl;;
		//return false;
	}

	return 0;
}
