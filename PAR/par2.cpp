#include <vector>
#include <cassert>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using std::vector;
using std::queue;

const int SIZE = 500000;
struct Node {
	int depth;
	int deepest_son;
	int furthest_i;
	int furthest_d;
	int son[2];
	vector<int> ancestors;
	Node(): depth(-1), deepest_son(-1), furthest_i(-1), furthest_d(-1), son{-1, -1}
	{

	}
};

int set_depth(Node * tree, int size)
{
	int i = 0;
	int c = 0;
	queue<int> q;
	q.push(i);
	tree[i].depth = 0;
	while(!q.empty()){
		c++;
		if (c > size){
			exit(101);
		}
		i = q.front();
		q.pop();
		//printf("%i depth: %i\n", i, tree[i].depth);
		for (int s = 0; s < 2; s++){
			if (tree[i].son[s] != -1){
				tree[tree[i].son[s]].depth = tree[i].depth + 1;
				q.push(tree[i].son[s]);
			}
		}
	}
	return c;
}
int set_ancestors(Node * tree, int size)
{
	int i = 0;
	int c = 0;
	queue<int> q;
	q.push(i);
	while(!q.empty()){
		i = q.front();
		q.pop();
		c++;
		//printf("Przerabiamy: %i\n", i);
		if (c > size){
			exit(102);
		}
		if (tree[i].depth == 0){
			tree[i].ancestors.push_back(i);
		}
		else {
			for (int k = 0; k < (int)log2(tree[i].depth); k++){
				tree[i].ancestors.push_back(tree[tree[i].ancestors[k]].ancestors[k]);
				//printf("Dodano %i\n", tree[tree[i].ancestors[k]].ancestors[k]);

			}
		}
		//for (int k : tree[i].ancestors)
		//	printf("%i ", k);
		//printf("\n");
		for (int s = 0; s < 2; s++){
			if (tree[i].son[s] != -1){
				tree[tree[i].son[s]].ancestors.push_back(i);
				q.push(tree[i].son[s]);
			}
		}
	}
	return c;
}

int set_deepest(Node *tree, int N)
{
	int i = 0;
	int c = 0;
	queue<int> q1;
	queue<int> q2;
	q1.push(i);
	while (!q1.empty()){
		i = q1.front();
		q1.pop();
		c++;
		if (c > N)
			exit(103);
		if (tree[i].son[0] == -1 && tree[i].son[1] == -1){
			q2.push(i);
		//	printf("Leaf %i\n", i);
		}
		else {
			for (int s = 0; s < 2; s++)
				if (tree[i].son[s] != -1)
					q1.push(tree[i].son[s]);
		}
	}
	assert(c == N);
	c = 0;
	while (!q2.empty()){
		i = q2.front();
		q2.pop();
		c++;
		if (c > N)
			exit(104);
		if (tree[i].son[0] == -1 && tree[i].son[1] == -1){
			tree[i].deepest_son = i;
		}
		else {
			for (int s = 0; s < 2; s++){
				if (tree[i].son[s] != -1){
					int tmp = tree[i].son[s];
					int ds = tree[i].deepest_son;
					if (ds == -1 || tree[tree[tmp].deepest_son].depth > tree[ds].depth)
						tree[i].deepest_son = tree[tmp].deepest_son;
				}
			}
		}
		int f = tree[i].ancestors[0];
		if (f != i){
			bool able = true;
			for (int s = 0; s < 2; s++)
				able = able && (tree[f].son[s] == -1 || tree[tree[f].son[s]].deepest_son != -1);
			if (able)
				q2.push(f);
		}
		//printf("%i deepest son: %i\n", i, tree[i].deepest_son);
	}
	return c;
}

int set_furthest(Node * tree, int N)
{
	queue<int> q;
	int i = 0;
	q.push(i);
	int c = 0;

	while(!q.empty()){
		i = q.front();
		q.pop();
		c++;
		if (c > N)
			exit(105);
		int f = tree[i].ancestors[0];
		if (f != i){
			int leg = 0;
			if (tree[f].son[0] == i)
				leg = 1;
			int leg_depth = tree[tree[tree[f].son[leg]].deepest_son].depth;
			leg_depth += 2;
			leg_depth -= tree[tree[f].son[leg]].depth;
			if (leg_depth > tree[f].furthest_d + 1){
				tree[i].furthest_d = leg_depth;
				tree[i].furthest_i = tree[tree[f].son[leg]].deepest_son;
			}
			else {
				tree[i].furthest_d = tree[f].furthest_d + 1;
				tree[i].furthest_i = tree[f].furthest_i;
			}

		}
		else {
			tree[i].furthest_i = i;
			tree[i].furthest_d = 0;
		}
		//printf("%i furthest: i %i d %i\n", i, tree[i].furthest_i, tree[i].furthest_d);
		for (int s = 0; s < 2; s++)
			if (tree[i].son[s] != -1)
				q.push(tree[i].son[s]);

	}
	return c;
}

Node tree[500000];
int main(){
	int N;
	int M;
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%d %d", &(tree[i].son[0]), &(tree[i].son[1]));
		for (int s = 0; s < 2; s++)
			if (tree[i].son[s] != -1)
				tree[i].son[s]--;
	}
	assert(N == set_depth(tree, N));
	assert(N == set_ancestors(tree, N));
	assert(N == set_deepest(tree, N));
	assert(N == set_furthest(tree, N));
	exit(100);
}




