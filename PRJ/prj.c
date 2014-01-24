#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
	int N;
	int M;
	int K;
	scanf("%i %i %i", &N, &M, &K);
	std::tuple< int, int, std::vector<int> > nodes[N]; //nasza waga, od ilu zalezymy, ktore zaleza od nas
	int i = 0;
	for (i = 0; i < N; i++){
		int tmp;
		scanf("%i", &tmp);
		nodes[i] = std::make_tuple(tmp, 0, std::vector<int>());
	}
	for (i = 0; i < M; i++){
		int d1, d2;
		scanf("%i %i", &d1, &d2);
		get<1>(nodes[d1]) += 1;
		get<2>(nodes[d2]).push_back(d1);
	}
	std::priority_queue<std::tuple<int, int, std::vector<int> > pq;
	for (i = 0; i < N; i++){
		if (get<1>(nodes[i] == 0)){
			get<1>(nodes[i]) == i;
			pq.push(nodes[i]);
		}
	}
	int pro = 0;
	while (pro != K) {
		auto tmp = pq.pop();
		for (int dep : get<2>(tmp)){
			get<0>(nodes[dep])
		}
	}
	printf("\n");
}
