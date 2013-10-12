//Andrzej Sułecki
//as320426
//ASD zadanie POD

#include <stdio.h>

unsigned long long solution(unsigned long long * A, int N, int M){
	unsigned long long prefSum[N+1];
	prefSum[0]=0;
	int i = 0;
	for (i = 0; i < N; i++){
		prefSum[i+1] = prefSum[i] + A[i];
		prefSum[i+1] = prefSum[i+1] % (unsigned long long)M;
	}
	unsigned long long countTable[M];
	for (i = 0; i < M; i++){
		countTable[i] = 0;
	}
	unsigned long long result = 1;
	for (i = 0; i < N+1; i++){
		result += countTable[prefSum[i]];
		countTable[prefSum[i]]++;
	}

//	unsigned long long result = 1;
//	for (i = 0; i < M; i++){
//		result += (countTable[i]*(countTable[i]-1))/2;
//	}
	return result;
}

int main(){
	int N = 0;
	int M = 0;
	scanf ("%i %i", &N, &M);
	int i = 0;
	unsigned long long A[N];
	for (i = 0; i < N; i++){
		int a;
		scanf("%u", &a);
		A[i] = a;
	}
	
	unsigned long long result = solution(&A[0], N, M);
	printf("%u", result);
	return 0;
}
