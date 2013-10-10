//Andrzej Sułecki
//as320426
//ASD zadanie POD

long long solution(long long * A, int N, int M){
	long long prefSum[N+1];
	prefSum[0]=0;
	int i = 0;
	for (i = 0; i < N; i++){
		prefSum[i+1] = prefSum[i] + (A[i]%M);
		prefSum[i+1] = prefSum[i+1] % M;
	}
	long long countTable[M];
	for (i = 0; i < M; i++){
		countTable[i] = 0;
	}
	for (i = 0; i < N+1; i++){
		countTable[prefSum[i]]++;
	}

	long long result = 1;
	for (i = 0; i < M; i++){
		result += (countTable[i]*(countTable[i]-1))/2;
	}
	return result;
}

int main(){
	int N = 0;
	int M = 0;
	scanf ("%i %i", &N, &M);
	int i = 0;
	long long A[N];
	for (i = 0; i < N; i++){
		int a;
		scanf("%i", &a);
		A[i] = a;
	}
	
	long long result = solution(&A[0], N, M);
	printf("%i", result);
	return 0;
}
