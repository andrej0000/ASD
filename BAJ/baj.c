#include <stdio.h>
#include <stdlib.h>

int main(){
	int N;
	int M;
	scanf("%i %i", &N, &M);
	int * A = malloc(sizeof(int) * N);
	int i = 0;
	for (i = 0; i < N; i++){
		scanf("%i", &(A[i]));
	}
	int maxLevel = A[N-1];
	int * levels = malloc(sizeof(int) * maxLevel + 1);
	levels[0] = 0;
	levels[1] = N;
	int j = 0;
	for (i = 0; i <= maxLevel; i++){
		if (A[j] >= i)
			levels[i] = N-j;
		if (A[j] == i)
			for (; A[j] <= i; j++){} 
	}
	int ** result = malloc(sizeof(int*) * maxLevel + 1);

	result[0] = 0;
	result[0] = malloc(sizeof(int) * M + 1);
	for (i = 0; i < M + 1; i++){
		result[0][i] = 0;
	}
	for (i = 1; i <= maxLevel; i++){
		int tmp = (i - j) * levels[i];
		result[i] = malloc(sizeof(int) * M + 1);
		int m = 0;
		result[i][0] = 0;
		for (m = 1; m <= M; M++){
			result[i][m] = M+1;
			for (j = 0; j < i; j++){
				if (tmp + result[j][m] <= m){ 
					if (result[i][m] <= m)
						result[i][m] = tmp + result[j][m] < result[i][m] ? result[i][m] : tmp + result[j][m];
					else
						result[i][m] = tmp + result[j][m];
				}
			}
		}
	}
	//to samo tylko dla kazdego M trzeba zrobic od 0 do M
	int res = 0;
	for (i = 0; i <= maxLevel; i++)
		if (result[i] <= M)
			res = res > result[i] ? res : result[i];

	/*for (i = 0; i <= maxLevel; i++)
		printf("%i ", levels[i]);
	printf("\n");
	for (i = 0; i <= maxLevel; i++)
		printf("%i ", result[i]);
	printf("\n");*/
	printf("%i\n", res);				
	free(result);
	free(levels);
	free(A);
	return 0;
}
