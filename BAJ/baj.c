#include <stdio.h>
#include <stdlib.h>
typedef struct state {
	short max_lvl;
	short spent;
	struct state *next;
} state;

state *add(state *head, short max_lvl, short spent){
	state *s = (state *)malloc(sizeof(state));
	s->max_lvl = max_lvl;
	s->spent = spent;
	s->next = head;
	return s;
}

void free_state(state *s){
	state * next;
	while (s != NULL){
		next = s->next;
		free(s);
		s = next;
	}
}

int main(){
	state *head = NULL;
	int N;
	int M;
	scanf("%i %i", &N, &M);
	int i = 0;
	int A[N];
	for (i = 0; i < N; i++)
		scanf("%i", &(A[i]));
	int result = 0;
	int max = A[N-1];
	short levels[max];
	int j = 0;
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
	head = add(head, 0, 0);
	short added[M+1][N+1];
	for (j = 0; j <= M; j++)
		for (i = 0; i <= N; i++)
			added[j][i] = max;
	for (i = max-1; i >= 0; i--){
		state * current = head;
		state * newhead = NULL;
		while (current != NULL){
			int smaxlvl = current->max_lvl;
			int spent = current->spent;
			int tmp = spent + smaxlvl;
			if (tmp <= M){
				if (i < added[tmp][smaxlvl]){
					newhead = add(newhead, smaxlvl, tmp);
					added[tmp][smaxlvl] = i;
				}
			}
			tmp = spent + levels[i];
			if (tmp <= M){
				if (i < added[tmp][levels[i]]){
					newhead = add(newhead, levels[i], tmp);
					added[tmp][levels[i]] = i;
				}
			}
			current = current->next;
		}
		free_state(head);
		head = newhead;
	}
	state *current = head;
	while (current != NULL){
		if ((current->spent > result) && (current->spent <= M))
			result = current->spent;
		current = current->next;
	}
	
	printf("%i\n",result);
	free_state(head);
	return 0;
}
