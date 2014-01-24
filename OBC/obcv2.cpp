#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <cassert>
using std::queue;
using std::map;
using std::vector;
using std::set;

struct Node;

struct Route{
	Node *from;
	Node *to;
	Node *lca;
	unsigned long long weight;
};

struct Node{
	int id;
	set<Node *> neighbours;
	int unvisited;
	vector<Route*> routes;
	unsigned long long start_weight;
	unsigned long long end_weight;
	int rank;
	Node* highest;
	Node* anc;
	bool black;
};

Node* find(Node * n)
{
	if (n == n->highest){
		return n;
	}
	else {
		n->highest = find(n->highest);
		return n->highest;
	}
}

void make_set(Node * n){
	n->rank = 0;
	n->highest = n;
}
void union_set(Node * a, Node * b)
{
	Node *aR = find(a);
	Node *bR = find(b);
	if (aR->rank > bR->rank){
		bR->highest = aR;
	} else if (aR->rank < bR->rank){
		aR->highest = bR;
	} else {
		bR->highest = aR;
		aR->rank++;
	}
}
void count_lca(Node * n)
{
//	printf("count lca %i\n", n->id);
	make_set(n);
	n->anc = n;
	for (Node * c : n->neighbours){
		c->neighbours.erase(n);
		count_lca(c);
		union_set(c, n);
		find(n)->anc = n;
	}
	n->black = true;
	for (Route * r : n->routes){
		Node * dest;
		if (r->from == n)
			dest = r->to;
		else if (r->to == n)
			dest = r->from;
		else
			assert(false);
		if (dest->black){
			r->lca = find(dest)->anc;
			r->lca->end_weight += r->weight * 2;
			r->to->start_weight += r->weight;
			r->from->start_weight += r->weight;
			delete r;
		//	printf("calculated lca %i %i : %i\n", r->from->id, r->to->id, r->lca->id);
		}
	}
}
unsigned long long count_val(Node *n, unsigned long long &max)
{
	unsigned long long v = 0;
	for (Node * c: n->neighbours){
		v += count_val(c, max);
	}
	v += n->start_weight;
	v -= n->end_weight;
	//printf("Weight from %i : %i\n", n->id, v);
	if (max < v)
		max = v;
	return v;
}
int main()
{
	int N;
	int M;
	unsigned long long max_score = 0;
	scanf("%i %i", &N, &M);
	Node* vertex[N];

	for (int i = 0; i < N; i++){
		vertex[i] = new Node;
		vertex[i]->id = i;
		vertex[i]->routes.shrink_to_fit();
		vertex[i]->unvisited = 0;
		vertex[i]->start_weight = 0;
		vertex[i]->end_weight = 0;
		vertex[i]->black = false;

	}
	for (int i = 0; i < N-1; i++){
		int f = 0;
		int t = 0;
		scanf("%i %i", &f, &t);
		vertex[f]->unvisited++;
		vertex[t]->unvisited++;
		vertex[f]->neighbours.insert(vertex[t]);
		vertex[t]->neighbours.insert(vertex[f]);
	}
	for (int i = 0; i < M; i++){
		int f = 0;
		int t = 0;
		unsigned long long w=0;
		scanf("%i %i %llu", &f, &t, &w);
		Route * r = new Route;
		r->weight = w;
		r->from = vertex[f];
		r->to = vertex[t];
		vertex[f]->routes.push_back(r);
		vertex[t]->routes.push_back(r);
	}
	count_lca(vertex[0]);
	unsigned long long max = 0;
	count_val(vertex[0], max);

	printf("%llu\n", max);
}
