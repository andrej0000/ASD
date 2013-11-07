#include <stdio.h>
#include <stdlib.h>
typedef struct state {
	int max_lvl;
	int spent;
	struct state *next;
} state;

state *add(state *head, int max_lvl, int spent){
	state *s = (state *)malloc(sizeof(state));
	s->max_lvl = max_lvl;
	s->spent = spent;
	s->next = head;
	return s;
}

void free_state(state *s){
	if (s->next != NULL)
		free_state(s->next);
	free(s);
}

int * getlevels(int *A, int N){
	int max = A[N-1];
	int *levels = (int *)malloc(sizeof(int) * max);
	int i = 0;
	int j = 0;
	int last = 0;
	for (i = 0; i < max; i++){
		if (i + 1 <= A[j]){
			levels[i] = N - j;
		}
		else {
			while (A[j] < i + 1)
				j++;
			i--;
		}
	}
	return levels;
}
void print(int *A, int N){
	int i = 0;
	for (i = 0; i < N; i++)
		printf("%i ", A[i]);
	printf("\n");
}
int solution(int * A, int N, int M){
	int result = 0;
	int max = A[N-1];
	int *levels = getlevels(A, N);
	//print(levels, max);
	state *head = NULL;
	head = add(head, 0, 0);
	int i = 0;
	int added[max][M+1];
	for (i = 0; i < max; i++){
		int j = 0;
		for (j = 0; j <= M; j++)
			added[i][j] = 0;
	}
	for (i = 0; i < max; i++){
		state * current = head;
		while (current != NULL){
			int smaxlvl = current->max_lvl;
			int spent = current->spent;
			int tmp = (i + 1 - smaxlvl) * levels[i] + spent;
			if (tmp <= M){
				if (0 == added[i][tmp]){
					head = add(head, i + 1, tmp);
					added[i][tmp] = 1;
					if (tmp > result)
						result = tmp;
				}
			}
			current = current->next;
		}
	}
	free_state(head);
	free(levels);
	return result;
}

int main(){
	int N;
	int M;
	scanf("%i %i", &N, &M);
	int i = 0;
//	int A[N];
	int *A = (int *)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++)
		scanf("%i", &(A[i]));
	printf("%i\n",solution(&A[0], N, M));
	free(A);

}
