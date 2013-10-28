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
	int ** result = malloc(sizeof(int*) * maxLevel + 1); //result[layer][max]
	for (i = 0; i <= maxLevel; i++){
		result[i] = malloc(sizeof(int) * M + 1);
		result[i][0] = 0;
	}	
	int m = 0;
	int l = 0;
	for (m = 0; m<=M; m++){
		result[0][m] = 0;
		for (l = 1; l <= maxLevel; l++){
			result[l][m] = M + 1;
			if ( m >= levels[l] ){
				result[l][m] = result[l-1][m];
				for (i = 0; i < l; i ++){
					int tmp = result[i][m - levels[l]] + (levels[l] * (l - i));
					if (tmp <= m){
						if (result[l][m] > m)
							result[l][m] = tmp;
						else
							result[l][m] = tmp < result[l][m] ? result[l][m] : tmp;
					}
				}
			}
		}
	}
	int res = 0;
	for (l = 0; l <= maxLevel; l++){
		for (m = 0; m<=M; m++){
//			printf("%i ", result[l][m]);
			if (result[l][m] <= M)
				res = res > result[l][m] ? res : result[l][m];
		}
//		printf("\n");
	}
	printf("%i\n", res);				
	free(result);
	free(levels);
	free(A);
	return 0;
}
