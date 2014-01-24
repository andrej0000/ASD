#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

typedef struct block {
	struct block *left;
	struct block *right;

	int start;
	int end;
	int *perm;
	int maxk;
} block;

block *spawn(int start, int end, int maxk){
	block * b = malloc(sizeof(block));
	b->perm = malloc(sizeof(int) * maxk);
	b->maxk = maxk;
	b->start = start;
	b->end = end;
	if (start == end){
		b->left = NULL;
		b->right = NULL;
	}
	else {
		int mid = (end + start) / 2;
		b->left = spawn(start, mid, maxk);
		b->right = spawn(mid+1, end, maxk);
	}
	return b;
}

void freetree(block *tree){
	if (tree != NULL){
		freetree(tree->left);
		freetree(tree->right);
		free(tree->perm);
		free(tree);
	}
}

int fits(block *tree, int val){
	return ((tree != NULL) && ((val >= tree->start) && (val <= tree->end)));
}

void put(block *tree, int val, int *perm, int maxk){
	if (!fits(tree, val))
		return;

	put(tree->left, val, perm, maxk);
	put(tree->right, val, perm, maxk);

	int i;
	for (i = 0; i < maxk; i++){
		tree->perm[i] += perm[i];
		tree->perm[i] %= MOD;
	}
}
void query(block *tree, int val, int *perm, int maxk){
	if (tree == NULL)
		return;

	if (fits(tree->right, val)){
		query(tree->right, val, perm, maxk);
	}
	else {
		if (tree->right != NULL){
			int i = 0;
			for (i = 0; i < maxk; i++){
				perm[i]+=tree->right->perm[i];
				perm[i]%=MOD;
			}
		}
		query(tree->left, val, perm, maxk);
	}
}
void process(block *tree, int val, int maxk){
	int *perm = calloc(maxk + 1, sizeof(int));
	perm[0] = 1;
	query(tree, val, perm+1, maxk);
	put(tree, val, perm, maxk);
	free(perm);
}

int main(){
	int N;
	int K;
	scanf("%i %i", &N, &K);

	int A[N];

	int i;
	for (i = 0; i < N; i++){
		scanf("%i", &(A[i]));
	}

	block *tree = spawn(1, N, K);
	for (i = 0; i < N; i++){
		process(tree, A[i], K);
	}

	printf("%i\n", tree->perm[K-1]);
	freetree(tree);
	return 0;
}
