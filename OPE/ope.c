#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	long long start;
	long long end;
	long long value;
	struct tree *left;
	struct tree *right;
	struct tree *next;
} tree;

void freenode(tree *node)
{
	if (node == NULL)
		return;
	freenode(node->next);
	free(node);
}


void freetree(tree *node)
{
	if (node == NULL)
		return;
	freetree(node->left);
	freetree(node->right);
	freenode(node);
}

tree *spawn(long long start, long long end)
{
	tree *node = malloc(sizeof(tree));
	node->start = start;
	node->end = end;
	node->value = 0;
	if (start != end){
		int mid = (start + end)/2;
		node->right = spawn(start, mid);
		node->left = spawn(mid+1, end);
	}
	else {
		node->left = NULL;
		node->right = NULL;
	}
	node->next = NULL;
	return node;
}

int is_inside(tree *node, long long p)
{
	if ((node->start <= p) && (node->end >= p))
		return 1;
	return 0;
}

long long query(tree *node, long long p)
{
	if (node == NULL)
		return 0;
	if ((is_inside(node, p)) == 0)
		return 0;
	long long tmp = node->value + query(node->right, p) + query(node->left, p);
	return tmp;
}

int overlap(tree *node, long long s, long long e)
{
	if (node == NULL)
		return 0;
	if (e >= node->end && s <= node->start)
		return 2;
	if (e >= node->end && s <= node->end)
		return 1;
	if (s <= node->start && e >= node->start)
		return 1;
	if (s >= node->start && e <= node->end)
		return 1;
	return 0;
}

tree *copy(tree *node, long long value)
{
	if (node == NULL)
		return NULL;
	node->next = calloc(1, sizeof(tree));
	node->next->start = node->start;
	node->next->end = node->end;
	node->next->next = NULL;
	node->next->left = node->left;
	node->next->right = node->right;
	node->next->value = node->value + value;
	return node->next;
}

tree *modify(tree *node, long long s, long long e, long long value)
{
	int ol = overlap(node, s, e);
	if (ol == 2) {
		tree *tmp = copy(node, value);
		return tmp;
	}
	if (ol == 0) {
		return node;
	}
	if (ol == 1) {
		tree *tmp = copy(node, 0);
		tmp->left = modify(tmp->left, s, e, value);
		tmp->right = modify(tmp->right, s, e, value);
		return tmp;
	}
	return NULL;
}

long long cube(long long x, long long mod)
{
	return ((((x % mod) * (x % mod)) % mod) * (x%mod)) % mod;
}

long long update_i(long long x, long long T, long long n)
{
	return 1 + (cube(x+T, n));
}
long long update_j(long long i, long long x, long long T, long long n)
{
	return i + (cube(x+T, (n - i + 1)));
}
long long update_c(long long x, long long T)
{
	return (cube((x+T), 10));
}
long long update_io(long long x, long long T, long long n)
{
	return 1 + (cube(x+1+T, n));
}
long long update_t(long long x, long long T)
{
	return (x + 1234567) % (T + 1);
}


int main()
{
	int N;
	scanf("%i", &N);

	tree *head[N+1];

	head[0] = spawn(1, N);

	int x = 0;
	int T = 0;

	for (T = 0; T < N; T++){
		long long i = update_i(x, T, N);
		long long j = update_j(i, x, T, N);
		long long c = update_c(x, T);
		long long io = update_io(x, T, N);
		long long t = update_t(x, T);
		head[T+1] = modify(head[T], i, j, c);
		x = query(head[t], io);
	}
	for (T = 0; T < N; T++){
		x = query(head[N], T+1);
		printf("%i\n", x);
	}
	//freetree(head[0]);
	return 0;
}
