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

struct Route{
	int from;
	int to;
	unsigned long long weight;
};

struct Node{
	set<int> neighbours;
	int unvisited;
	vector<Route*> routes;
	unsigned long long weight;
};
int main()
{
	int N;
	int M;
	unsigned long long max_score = 0;
	scanf("%i %i", &N, &M);
	Node vertex[N];
	for (int i = 0; i < N; i++){
		vertex[i].unvisited = 0;
		vertex[i].weight = 0;
	}
	for (int i = 0; i < N-1; i++){
		int f = 0;
		int t = 0;
		scanf("%i %i", &f, &t);
		if (t >= N || t < 0 || f >= N || f < 0){
			printf("-2");
			return 0;
		}
		vertex[f].unvisited++;
		vertex[t].unvisited++;
		vertex[f].neighbours.insert(t);
		vertex[t].neighbours.insert(f);
	}
	for (int i = 0; i < M; i++){
		int f = 0;
		int t = 0;
		unsigned long long w=0;
		scanf("%i %i %llu", &f, &t, &w);
		if (t >= N || t < 0 || f >= N || f < 0){
			printf("-3");
			return 0;
		}
		Route * r = new Route;
		if (r == NULL){
			printf("-4");
			return 0;
		}
		r->weight = w;
		r->from = f;
		r->to = t;
		vertex[f].routes.push_back(r);
		vertex[t].routes.push_back(r);
		vertex[f].weight += w;
		vertex[t].weight += w;
	}
	queue<int> leafs;
	for (int i = 0; i < N; i++){
		if (vertex[i].unvisited == 1)
			leafs.push(i);
	}

	while (!leafs.empty()){
		int v = leafs.front();
		leafs.pop();
		if (v < 0 || v>= N){
			printf("-9");
			return 0;
		}
		int father = -1;
		if (vertex[v].unvisited != 0){
			if (vertex[v].neighbours.size() == 0){
				printf("-10");
				return 0;
			}
			father = *(vertex[v].neighbours.begin());
			if (father >= N || father < 0){
				printf("-5");
				return 0;
			}
			vertex[father].unvisited--;
			if(vertex[father].neighbours.find(v) != vertex[father].neighbours.end())
				vertex[father].neighbours.erase(v);
			if (vertex[father].unvisited == 1)
				leafs.push(father);
		}
		for (Route *r : vertex[v].routes){
			if (r == NULL){
				printf("-4");
				return 0;
			}
			if (r->from == r->to){
				vertex[v].weight -= r->weight;
			}
			else {
				if (vertex[v].unvisited != 0){
					if (r->from == v)
						r->from = father;
					else if (r->to == v)
						r->to = father;
					else {
						printf("-6");
						return 0;
					}
					if (father >= N || father < 0){
						printf("-7");
						return 0;
					}
					vertex[father].routes.push_back(r);
					vertex[father].weight += r->weight;
				}
			}
		}
		if (vertex[v].weight > max_score){
			max_score = vertex[v].weight;
		}
	}
	printf("%llu\n", max_score);
}
