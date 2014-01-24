#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

typedef tuple<long long, int, vector<int> > node;

int main()
{
	int N;
	int M;
	int K;
	scanf("%i %i %i", &N, &M, &K);
	node nodes[N]; //nasza waga, od ilu zalezymy, ktore zaleza od nas
	int i = 0;
	for (i = 0; i < N; i++){
		int tmp;
		scanf("%i", &tmp);
		nodes[i] = make_tuple(tmp, 0, vector<int>());
	}
	for (i = 0; i < M; i++){
		int d1, d2;
		scanf("%i %i", &d1, &d2);
		get<1>(nodes[d1-1]) += 1;
		get<2>(nodes[d2-1]).push_back(d1-1);
	}
	priority_queue< node, vector<node>, greater<node> > pq;
	for (i = 0; i < N; i++){
		if (get<1>(nodes[i]) == 0){
			get<1>(nodes[i]) == i;
			pq.push(nodes[i]);
		}
	}
	int pro = 0;
	long long mx = 0;
	while (pro != K) {
		node tmp = pq.top();
		pq.pop();
		pro ++;
		mx = max(mx, get<0>(tmp));
		for (int dep : get<2>(tmp)){
			get<0>(nodes[dep]) = max(get<0>(nodes[dep]), get<0>(tmp));
			get<1>(nodes[dep]) -= 1;
			if (get<1>(nodes[dep]) == 0){
				pq.push(nodes[dep]);
			}
		}
	}
	printf("%i\n", mx);
}
