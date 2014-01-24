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
	vector <int> *ancestors;
	int depth;
	int max_depth_i;
	int farthest_i;
	int farthest_i_d;
} node;

void calc_depth(node * tree, int i, int N)
{
	int c = 0;
	queue<int> q;
	q.push(i);
	tree[i].depth = 0;
	while(!q.empty()){
		i = q.front();
		q.pop();
		c++;
		assert (c<= N + 1);
		//printf("%i\n", i);
		if (tree[i].left_i != -1){
			tree[tree[i].left_i].depth = tree[i].depth + 1;
			q.push(tree[i].left_i);
		}
		if (tree[i].right_i != -1){
			tree[tree[i].right_i].depth = tree[i].depth + 1;
			q.push(tree[i].right_i);
		}
		tree[i].max_depth_i = -1;
	}



/*
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
		tree[i].max_depth_i = tree[tree[i].right_i].max_depth_i;*/

}

void set_ancestors(node * tree, int i, int anc)
{

	queue<int> q;
	q.push(i);
	while(!q.empty()){
		i = q.front();
		q.pop();
		if (i != -1)
		{
	//		printf("%i\n", tree[i].ancestors);
	//		tree[i].ancestors = new vector<int>;
	//		tree[i].ancestors->push_back(i);
	//		printf("%i\n", tree[i].ancestors->size());

			if (tree[i].depth == 0){
				tree[i].ancestors->push_back(i);
			}
			else {
				anc = tree[i].ancestors->at(0);
				while ((int)log2(tree[i].depth) >= tree[i].ancestors->size()){
					int tmp = tree[anc].ancestors->at(tree[i].ancestors->size()-1);
					tree[i].ancestors->push_back(tmp);
					anc = tmp;
				}
			}
			if (tree[i].left_i != -1)
				tree[tree[i].left_i].ancestors->push_back(i);
			if (tree[i].right_i != -1)
				tree[tree[i].right_i].ancestors->push_back(i);
			//tree[i].ancestors->shrink_to_fit();
			q.push(tree[i].left_i);
			q.push(tree[i].right_i);
		}
	}
}

void set_max_depth(node * tree, int i, int N)
{
	queue<int> q;
	q.push(i);

	queue<int> q2;
	int c1 = 0;
	int c2 = 0;
	while(!q.empty()){
		i = q.front();
		q.pop();
		if (i != -1){
			c1++;
			assert(c1 <= N+1);
			if (tree[i].left_i == -1 && tree[i].right_i == -1){
				tree[i].max_depth_i = i;
				q2.push(i);
			}
			else {
				q.push(tree[i].left_i);
				q.push(tree[i].right_i);
			}
		}
	}
	while(!q2.empty()){
		i = q2.front();
		q2.pop();
		if (i != -1){
			c2++;
			assert(c2 <= N+1);
			tree[i].max_depth_i = i;
			if (tree[i].left_i != -1)
				tree[i].max_depth_i = tree[tree[i].left_i].max_depth_i;
			if (tree[i].right_i != -1 &&
				tree[tree[i].max_depth_i].depth <
				tree[tree[tree[i].right_i].max_depth_i].depth)
				tree[i].max_depth_i = tree[tree[i].right_i].max_depth_i;
			int f = tree[i].ancestors->at(0);
			if (f != i)
			if ((tree[f].right_i == -1 || tree[tree[f].right_i].max_depth_i != -1)
				&&
				(tree[f].left_i == -1 || tree[tree[f].left_i].max_depth_i != -1)){
				q2.push(f);
			}
		}

	}


}

void set_far(node * tree, int i)
{
	queue<int> q;
	q.push(i);
	while(!q.empty()){
		i = q.front();
		q.pop();
		if (i >= 1)
		{
			if (tree[i].depth == 0){
				tree[i].farthest_i = i;
				tree[i].farthest_i_d = 0;
			}
			else {
				int other;
				if (tree[tree[i].ancestors->at(0)].left_i == i)
					other = tree[tree[i].ancestors->at(0)].right_i;
				else
					other = tree[tree[i].ancestors->at(0)].left_i;
				int f = -1;
				if (other != -1){
					f = tree[tree[other].max_depth_i].depth - tree[other].depth + 2;
				}
				int d = tree[tree[i].ancestors->at(0)].farthest_i_d + 1;
				if (f > d){
					tree[i].farthest_i = tree[other].max_depth_i;
					tree[i].farthest_i_d = f;
				}
				else {
					tree[i].farthest_i = tree[tree[i].ancestors->at(0)].farthest_i;
					tree[i].farthest_i_d = d;
				}
			}
			assert(tree[i].farthest_i >= 1);
			q.push(tree[i].left_i);
			q.push(tree[i].right_i);
		}
	}
}

int find_k_ancestor(node * tree, int i, int k)
{
	if (i < 1)
		return -1;
	if (k == 0)
		return i;
	if (k < 0)
		return -1;
	int mask = 1;
	if (k > tree[i].depth)
		return -1;

	for (int l = 0; l < (int)log2(k)+1; l++){
		if ((k & mask) != 0)
			i = tree[i].ancestors->at(l);
		mask = mask << 1;
	}
	return i;
}
int find_lca_rec(node * tree, int a, int b)
{
	assert(tree[a].depth == tree[b].depth);
	assert(tree[a].ancestors->size() == tree[b].ancestors->size());
	if (a == b)
		return a;
	int i = tree[a].ancestors->size() - 1;
	while (i >= 0 && tree[a].ancestors->at(i) == tree[b].ancestors->at(i)){
		i--;
	}
	if (i == -1){
		assert(tree[a].ancestors->at(0) == tree[b].ancestors->at(0));
		return tree[a].ancestors->at(0);
	}
	return find_lca_rec(tree, tree[a].ancestors->at(0), tree[b].ancestors->at(0));
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
	int d = da-dxa;
	if (da-dxa != db-dxb)
		return -1;
	//jesli X jest w LCA to szukamy do gory
	if (dxa == dalca && dxb == dblca){
		if (tree[lca].depth >= d){
			return find_k_ancestor(tree, lca, d);
		}
		if (tree[lca].farthest_i_d >= d){
			return find_k_ancestor(tree, tree[lca].farthest_i, tree[lca].farthest_i_d - d);
		}
		if (lca != a && lca != b)
			return -1;
	}

	int dx;
	int y;
	if (dxa < dalca || (dxb == 0 && b == lca)){
		dx = dxa;
		y = a;
	}
	else if (dxb < dblca || (dxa == 0 && a == lca)){
		dx = dxb;
		y = b;
	}
	int x = find_k_ancestor(tree, y, dx);
	if (d == 0)
		return x;
	int leg;
	int xs;
	if (dx != 0){
		xs = find_k_ancestor(tree,y, dx-1);
		if (tree[x].right_i == xs)
			leg = tree[x].left_i;
		else
			leg = tree[x].right_i;
		d--;
	}
	else {
		leg = y;
	}
	int s = (tree[tree[leg].max_depth_i].depth - tree[leg].depth) - d;
	if (s < 0)
		return -1;
	return find_k_ancestor(tree, tree[leg].max_depth_i, s);
}

int main()
{
	int N;
	scanf("%i", &N);
	node *tree;
	tree = new node[N+1];
//	node tree[N+1];
	for (int i = 0; i < N; i++){
		tree[i+1].ancestors = new vector<int>;
		//tree[i+1].ancestors->shrink_to_fit();
		scanf("%i %i", &(tree[i+1].left_i), &(tree[i+1].right_i));
	}
	calc_depth(tree, 1, N);
	set_ancestors(tree, 1, 0);
	set_max_depth(tree, 1, N);
	//for (int i = 1; i < N+1; i++){
	//	printf("i: %i depth: %i max_depth_i: %i\n", i, tree[i].depth, tree[i].max_depth_i);
	//}
	set_far(tree, 1);
	int M;
	scanf("%i", &M);

	for (int i = 0; i < M; i++){
		int a;
		int b;
		int da;
		int db;
		scanf("%i %i %i %i", &a, &b, &da, &db);
		printf("%i\n", find_node(tree, a, b, da, db));
	}
}
