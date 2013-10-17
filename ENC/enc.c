#include <stdio.h>
#include <stdlib.h>

int solve(int * A, int N){
	int ** layers;
	layers = malloc(sizeof(int *) * N);
	int i = 0;
	for (i = 0; i < N; i++)
		layers[i] = NULL;
	int layers_count = 0;
	for (i = 0; i < N; i++){
		int a = A[i];
		int j = 0;
		while ((layers_count > j) && (layers[j][layers[j][0]] < a)){
			j++;
		}
		if (layers[j] == NULL){
			layers[j] = malloc(sizeof(int *) * (N + 1 - i));
			layers[j][0] = 0;
			layers_count++;
		}
		layers[j][0] += 1;
		layers[j][layers[j][0]] = a;
	}
	
	for (i = 0; i < N; i++){
		free(layers[i]);
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
