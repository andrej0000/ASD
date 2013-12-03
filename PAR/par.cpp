#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef struct {
	int left_i;
	int right_i;
	vector <int> ancestors;
	int depth;
	int max_depth_i;
} node;

void calc_depth(node * tree, int i, int cd)
{
	if (i == -1)
		return;
	tree[i].depth = cd;
	calc_depth(tree, tree[i].left_i, cd+1);
	calc_depth(tree, tree[i].right_i, cd+1);

	tree[i].max_depth_i = i;
	if (tree[i].left_i != -1)
		tree[i].max_depth_i = tree[tree[i].left_i].max_depth_i;
	if (tree[i].right_i != -1 &&
		tree[tree[i].max_depth_i].depth < tree[tree[i].right_i].depth)
		tree[i].max_depth_i = tree[tree[i].right_i].max_depth_i;
}

void set_ancestors(node * tree, int i, int anc)
{

	queue<int> q;
	q.push(i);
	while(!q.empty()){
		i = q.front();
		q.pop();
		printf("%i\n", i);
		if (i != -1)
		{
			if (tree[i].depth == 0){
				tree[i].ancestors.push_back(i);
			}
			else {
				anc = tree[i].ancestors[0];//tree[i].ancestors.push_back(anc);
				while ((int)log2(tree[i].depth) >= tree[i].ancestors.size()){
					int tmp = tree[anc].ancestors[tree[i].ancestors.size()-1];
					tree[i].ancestors.push_back(tmp);
					anc = tmp;
				}
			}
			if (tree[i].left_i != -1)
				tree[tree[i].left_i].ancestors.push_back(i);
			if (tree[i].right_i != -1)
				tree[tree[i].right_i].ancestors.push_back(i);
			q.push(tree[i].left_i);
			q.push(tree[i].right_i);
		}
	}
}

int find_k_ancestor(node * tree, int i, int k)
{
	int mask = 1;
	if (k > tree[i].depth)
		return -1;

	for (int l = 0; l < (int)log2(k)+1; l++){
		printf("mask %i mask&k %i from %i ", mask, k&mask, i);
		if ((k & mask) != 0)
			i = tree[i].ancestors[l];
		printf(" to %i\n", i);
		mask = mask << 1;
	}
	return i;
	/*if (k == 0)
		return i;
	int ni = tree[i].ancestors[(int)log2(k)]; //HAHA DUPA
	int nk = k + tree[ni].depth - tree[i].depth;
	return find_k_ancestor(tree, ni, nk);*/
}
int find_lca_rec(node * tree, int a, int b)
{
	assert(tree[a].depth == tree[b].depth);
	assert(tree[a].ancestors.size() == tree[b].ancestors.size());
	if (a == b)
		return a;
	int i = tree[a].ancestors.size() - 1;
	while (i >= 0 && tree[a].ancestors[i] == tree[b].ancestors[i]){
		i--;
	}
	if (i == -1){
		assert(tree[a].ancestors[0] == tree[b].ancestors[0]);
		return tree[a].ancestors[0];
	}
	return find_lca_rec(tree, tree[a].ancestors[i], tree[b].ancestors[i]);

}

int dfs(node * tree, int a, int d)
{
	//printf("DFS IN %i %i\n", a, d);
	if (a == -1)
		return -1;
	if (d == 0){
		//printf("dfs %i\n", a);
		return a;
	}
	int father = tree[a].ancestors[0];
	if (father != a){
		int *leg = NULL;
		if (tree[father].right_i == a)
			leg = &(tree[father].right_i);
		else
			leg = &(tree[father].left_i);
		*leg = -1;
		int res = dfs(tree, father, d-1);
		*leg = a;
		if (res != -1)
			return res;
	}
	if (tree[a].right_i != -1){
		int son = tree[a].right_i;
		if (tree[tree[son].max_depth_i].depth - tree[a].depth >= d){
			int deepest = tree[son].max_depth_i;
			return find_k_ancestor(tree, deepest, tree[tree[son].max_depth_i].depth - tree[a].depth - d);
		}
	}
	if (tree[a].left_i != -1){
		int son = tree[a].left_i;
		if (tree[tree[son].max_depth_i].depth - tree[a].depth >= d){
			int deepest = tree[son].max_depth_i;
			return find_k_ancestor(tree, deepest, tree[tree[son].max_depth_i].depth - tree[a].depth - d);
		}
	}
	return -1;
}

int find_lca(node * tree, int a, int b)
{
	int mind = min(tree[a].depth, tree[b].depth);
	a = find_k_ancestor(tree, a, tree[a].depth-mind);
	b = find_k_ancestor(tree, b, tree[b].depth-mind);
	return find_lca_rec(tree, a, b);
}

int find_node(node * tree, int a, int b, int da, int db)
{
	//printf("F_N %i %i %i %i\n", a, b, da, db);
	int lca = find_lca(tree, a, b);
	int dalca = tree[a].depth - tree[lca].depth;
	int dblca = tree[b].depth - tree[lca].depth;
	int dxa = (dalca + dblca + da - db);
	int dxb = (dalca + dblca + db - da);

	if (dxa % 2 == 1)
		return -1;
	if (dxb % 2 == 1)
		return -1;
	dxa /= 2;
	dxb /= 2;
	//printf("dalca %i dblca %i dxa %i dxb %i\n", dalca, dblca, dxa, dxb);
	if (da-dxa != db-dxb)
		return -1;
	if (dxa == dalca && dxb == dblca){
		int tl = tree[lca].left_i;
		int tr = tree[lca].right_i;
		tree[lca].left_i = -1;
		tree[lca].right_i = -1;
		int res = dfs(tree, lca, da-dxa);
		tree[lca].left_i = tl;
		tree[lca].right_i = tr;
		return res;
	}
	if (dxa < dalca){
		assert(dxb > dblca);
		int x = find_k_ancestor(tree, a, dxa);
		int *leg = NULL;
		int xs;
		int tmpax = tree[x].ancestors[0];
		tree[x].ancestors[0] = x;
		if (dxa != 0){
			xs = find_k_ancestor(tree,a, dxa-1);
			if (tree[x].right_i == xs)
				leg = &(tree[x].right_i);
			else
				leg = &(tree[x].left_i);
			*leg = -1;
		}
		int res = dfs(tree, x, da-dxa);
		if (dxa != 0){
			*leg = xs;
		}
		tree[x].ancestors[0] = tmpax;
		return res;
	}

	if (dxb < dblca){
		assert(dxa > dalca);
		int x = find_k_ancestor(tree, b, dxb);
		int *leg = NULL;
		int xs;
		int tmpax = tree[x].ancestors[0];
		tree[x].ancestors[0] = x;
		if (dxb != 0){
			xs = find_k_ancestor(tree,a, dxb-1);
			if (tree[x].right_i == xs)
				leg = &(tree[x].right_i);
			else
				leg = &(tree[x].left_i);
			*leg = -1;
		}
		int res = dfs(tree, x, da-dxa);
		if (dxb != 0){
			*leg = xs;
		}
		tree[x].ancestors[0] = tmpax;
		return res;
/*
		assert(dxa > dalca);
		int x = find_k_ancestor(tree, b, dxb);
		int xs = find_k_ancestor(tree, b, dxb-1);
		int tmpax = tree[x].ancestors[0];
		tree[x].ancestors[0] = x;
		int *leg = NULL;
		if (tree[x].right_i == xs)
			leg = &(tree[x].right_i);
		else
			leg = &(tree[x].left_i);
		*leg = -1;
		int res = dfs(tree, x, da-dxa);
		*leg = xs;
		tree[x].ancestors[0] = tmpax;
		return res;*/
	}
	return -1;
}

int main()
{
	int N;
	scanf("%i", &N);
	node tree[N+1];
	for (int i = 0; i < N; i++){
		scanf("%i %i", &(tree[i+1].left_i), &(tree[i+1].right_i));
	}
	calc_depth(tree, 1, 0);
	printf("NO SIGSEGVS SO FAR\n");
	set_ancestors(tree, 1, 0);
	printf("NO SIGSEGVS SO FAR\n");
	int M;
	scanf("%i", &M);
	printf("NO SIGSEGVS SO FAR %i\n", M);

	for (int i = 0; i < M; i++){
	printf("NO SIGSEGVS SO FAR\n");
		int a;
		int b;
		int da;
		int db;
		scanf("%i %i %i %i", &a, &b, &da, &db);
		printf("%i\n", find_node(tree, a, b, da, db));
	}
	for (int i = 1; i <= N; i++) {
		printf("node: %i, depth: %i anc: %i depth_i: %i\n", i, tree[i].depth, tree[i].ancestors.size(), tree[i].max_depth_i);
		for (int j: tree[i].ancestors){
			printf("%i ", j);
		}
		printf("\n");
	}
	printf("%i\n", find_k_ancestor(tree, 9, 1));
	printf("%i\n", find_k_ancestor(tree, 100, 100));
	//printf("%i\n", find_k_ancestor(tree, 9, 1));
	//printf("%i\n", find_lca(tree, 9, 2));
	//printf("%i\n", dfs(tree, 9, 4));
	/*assert (-1 == find_node(tree, 8, 2, 4, 3));
	printf("gut 1\n");
	assert (2 == find_node(tree, 8, 15, 2, 4));
	printf("gut 2\n");
	assert (1 == find_lca(tree, 8, 15));
	printf("gut 3\n");
	assert (8 == find_node(tree, 4, 2, 1, 2) || 9 == find_node(tree, 4, 2, 1,2));
	printf("gut 4\n");
	assert (8 == find_node(tree, 4, 3, 1,4) || 9 == find_node(tree, 4, 2, 1,2));
	printf("gut\n");
	assert (-1 == find_node(tree, 4,3,4,5));
	printf("gut\n");
	assert (3 == find_node(tree, 4,5,3,3));
	printf("gut\n");
	assert (-1 == find_node(tree, 8,2,4,3));
	printf("gut\n");
	assert (-1 == find_node(tree, 8,2,4,3));
	printf("gut\n");*/
}
