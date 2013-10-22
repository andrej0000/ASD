#include <stdio.h>
#include <stdlib.h>


//najmniejszy wiekszy 
int lowerbound(int * A, int x, int s, int e){
	if (s == e)
		return s;
	int mid = ((s+e)-((s+e)%2))/2;
	if (A[mid] > x)
		return lowerbound(A, x, s, mid);
	else
		return lowerbound(A, x, mid+1, e);
}


int solve(int * A, int N){
	int * layers;
	layers = malloc(sizeof(int) * N);
	int i = 0;
	for (i = 0; i < N; i++)
		layers[i] = N+1;
	int layers_count = 0;
	for (i = 0; i < N; i++){
		int a = A[i];
		int j = lowerbound(layers, a, 0, N-1);
		if (layers[j] == N+1){
			layers_count++;
		}
		layers[j] = a;
	}
	free(layers);
	return N-layers_count;
}

int main(){
	int N;
	scanf("%i", &N);
	int * A = malloc(sizeof(int) * N);
	int i;
	for (i = 0; i < N; i++){
		int a = 0;
		scanf("%i", &a);
		A[i] = a;
	}
	int result = solve(A, N);
	printf("%i\n", result);
	free(A);
}
