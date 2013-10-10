//Andrzej Sułecki
//as320426
//ASD zadanie PUN
int solution(int A[], int N) {
	int sum = 0;
	int i = 0;
	for (i = 0; i < N; i++){
		sum += A[i]; 
	}
	int currsum = 0;
	int j = 0;
	i = 0;
	int max = 0;
	while(i < N){
		int odl;
		//printf("Punkty i : %i j : %i", i, j);
		if (currsum > sum-currsum){ //jestesmy za polowa
			odl = sum-currsum;
			currsum -= A[j];
			j ++;
		}
		else { //jestesmy przed polowa
			odl = currsum;
			currsum += A[i];
			i++;
		}
		//printf(" odleglosc: %i\n", odl);
		if (odl > max)
			max = odl;
	}
	return max;
}
int main(){
	int N;
	scanf("%i", &N);
	int i = 0;
	int A[N];
	for (i = 0; i < N; i++){
		scanf("%i", &A[i]);
	}
	int result = solution(A, N);
	printf("%i", result);
	return 0;
}
