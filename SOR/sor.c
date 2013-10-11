//Andrzej Sulecki
//as320426
//ASD zadanie SOR
#define MOD_CONST 1000000000

//side == 0, znaczy ze ostatni element dostawiony byl z lewej
long unsort(int A[], int i, int j, int side){
	int taken = -1;
	long result = 0;
	if (side == 0){
		taken = i;
		i++;
	}
	else {
		taken = j;
		j--;
	}
	if ((i == j) && ((A[taken] < A[i]) != side))
		return 1;
	//A[i] kandydatem na nowy ostatni
	//mozliwe jesli A[taken] > A[i] == side
	if ((A[taken] < A[i]) != side){ 
		result += unsort(A, i, j, 0);
	}
	//Analogicznie dla A[j]
	if ((A[taken] < A[j]) != side){
		result += unsort(A, i, j, 1);
	}
	return result % MOD_CONST;
}

int main(){
	int N = 0;
	scanf("%i", &N);
	int A[N];
	int i = 0;
	for (i = 0; i < N; i++){
		int t = 0;
		scanf("%i", &t);
		A[i] = t;
	}
	long result = 0;
	result += unsort(A, 0, N-1, 0) % MOD_CONST;
	result += unsort(A, 0, N-1, 1) % MOD_CONST;
	printf("%i\n", result);
	return 0;
}
