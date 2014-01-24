#include <vector>
#include <tuple>
#include <cassert>
//#include <pair>
#include <map>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <set>

using std::pair;
using std::multimap;
using std::tuple;
using std::vector;
using std::set;

static const unsigned long long ULL = 18000000000ll;
static const int SIZE = 50000;

struct Edge {
	int dest;
	int weight;
	Edge(int d, int w) : dest(d), weight(w)
	{
	}
};

struct Node {
	// 0 - edges out, path to n-1
	// 1 - edges in, path to 0;
	unsigned long long path[2];
	vector <Edge> edges[2];
	bool visited[2];
	Node() : path{ULL,ULL}, visited{false,false}
	{
	}
};


Node nodes[SIZE];

template <int dir> struct cmp {
	inline bool operator() (const int& a, const int &b) {
		if (nodes[a].path[dir] != nodes[b].path[dir])
			return nodes[a].path[dir] < nodes[b].path[dir];
		return a < b;
	}
};


template <int dir>
void dijkstra(int source)
{

	set<int, cmp<dir> > queue;
//	printf("Dijkstra\n");
	nodes[source].path[dir] = 0;
	nodes[source].visited[dir] = true;
	queue.insert(source);
	while(!queue.empty()){
		auto it = queue.begin();
		int id = *it;
		queue.erase(it);
		unsigned long long time = nodes[id].path[dir];
//		printf("time: %llu id: %i\n", time, id);
		nodes[id].visited[dir] = true;
		for (Edge e : nodes[id].edges[dir]){
//			printf("Edge from: %i to: %i weight: %i\n", id, e.dest, e.weight);
			if (nodes[e.dest].path[dir] > e.weight + time){
				auto it2 = queue.find(e.dest);
				if (it2 != queue.end()){
					queue.erase(it2);
				}
				queue.insert(e.dest);
				nodes[e.dest].path[dir] = e.weight + time;
			}
		}
	}
}

void printnode(Node * nodes, int id)
{
//	printf("%i path[0] %i path[1] %i\n", id, nodes[id].path[0], nodes[id].path[1]);
	for (int s = 0; s < 2; s++){
		for (Edge e : nodes[id].edges[s])
			printf("%i %i, ", e.dest, e.weight);
		printf("\n");
	}
}

int main(){
	int N;
	int M;
	scanf("%i%i", &N, &M);
	for (int i = 0; i < M; i++){
		int a;
		int b;
		int w;
		scanf("%i%i%i", &a, &b, &w);
		nodes[a].edges[0].push_back(Edge(b, w));
		nodes[b].edges[1].push_back(Edge(a, w));
	}
	dijkstra<0>(0);
	dijkstra<1>(N-1);
	unsigned long long min = ULL;
	for (int i = 0; i < N; i++){
//		printnode(nodes, i);
		int tmp = std::max(nodes[i].path[0], nodes[i].path[1]);
		if (tmp < min)
			min = tmp;
	}
	printf("%llu\n", min);

}
