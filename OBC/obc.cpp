#include <vector>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <cassert>
using std::queue;
using std::map;
using std::vector;
using std::set;

typedef struct {
	int from;
	int to;
	unsigned long long weight;
} route;

typedef struct {
	set<int> neighbours;
	int unvisited;
	vector<route*> routes;
	unsigned long long weight;
} node;
int main()
{
	int N;
	int M;
	scanf("%i %i", &N, &M);
	node vertex[N];
	for (int i = 0; i < N; i++){
		vertex[i].unvisited = 0;
		vertex[i].weight = 0;
	}
	for (int i = 0; i < N-1; i++){
		int f;
		int t;
		scanf("%i %i", &f, &t);
		vertex[f].unvisited++;
		vertex[t].unvisited++;
		vertex[f].neighbours.insert(t);
		vertex[t].neighbours.insert(f);
	}
	for (int i = 0; i < M; i++){
		int f;
		int t;
		unsigned long long w;
		scanf("%i %i %u", &f, &t, &w);
		route * r = new route;
		r->weight = w;
		r->from = f;
		r->to = t;
		vertex[f].routes.push_back(r);
		vertex[t].routes.push_back(r);
		vertex[f].weight += w;
		vertex[t].weight += w;
	}
	/*
		printf("%i unvisited: %i\n", i, vertex[i].unvisited);
		for (int j : vertex[i].neighbours)
			printf("%i ", j);
		printf("\n");
	}*/
	queue<int> leafs;
	unsigned long long max_score = 0;
	for (int i = 0; i < N; i++){
		if (vertex[i].unvisited == 1)
			leafs.push(i);
	}
	/*
	 * usuwamy z mapy wszyskie klucze dest
	 */
	while (!leafs.empty()){
		int v = leafs.front();
		leafs.pop();
		int father = *(vertex[v].neighbours.begin());
		//printf("wezel %i, z ojcem %i, unv %i\n", v, father, vertex[v].unvisited);
		vertex[father].unvisited--;
		vertex[father].neighbours.erase(v);
		if (vertex[father].unvisited == 1)
			leafs.push(father);
		for (route *r : vertex[v].routes){
			if (r->from == r->to){
				vertex[v].weight -= r->weight;
				//delete(r);
			}
			else {
				if (r->from == v)
					r->from = father;
				else if (r->to == v)
					r->to = father;
				else
					assert(false);
				vertex[father].routes.push_back(r);
				vertex[father].weight += r->weight;
			}
		}
		//printf("o wadze %i\n", vertex[v].weight);
		if (vertex[v].weight > max_score)
			max_score = vertex[v].weight;
	}
	printf("%u\n", max_score);
}
