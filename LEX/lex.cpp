#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

typedef unsigned long long ull;

static const ull Q = 1e9+9;
static const ull P = 1013;

ull * powers;
ull * hash_table;
string str;
ull sub_mod(ull a, ull b)
{
	a = a % Q;
	b = b % Q;
	if (a < b)
		a += Q;
	return a - b;
}

ull get_hash(int i, int j){
	ull hash = sub_mod(hash_table[i], (powers[j - i + 1] * hash_table[j+1]));
	return hash;
}

//	-1	0 < 1
//	0	0 = 1
//	1	1 > 0

int cmp_eq(int s0, int e0, int s1, int e1){
	//char c;
	//cout << "Cmp_eq " << s0 << " "<< e0 << " "<< s1 << " "<< e1<<"\n";
	//cin >> c;
	if (s0 == e0 && s1 == e1){
		if (str[s0] == str[s1])
			return 0;
		if (str[s0] < str[s1])
			return -1;
		if (str[s0] > str[s1])
			return 1;
	}
	if (get_hash(s0, e0) == get_hash(s1, e1)){
		return 0;
	} else {
		int m0 = (s0+e0)/2;
		int m1 = (s1+e1)/2;
		if (get_hash(s0, m0) != get_hash(s1, m1))
			return cmp_eq(s0, m0, s1, m1);
		else
			return cmp_eq(m0 + 1, e0, m1 + 1, e1);
	}
}

int hash_cmp(int s0, int e0, int s1, int e1){
	int l0 = e0 - s0;
	int l1 = e1 - s1;
	int l = l0 < l1 ? l0 : l1;

	int r = cmp_eq(s0, s0+l, s1, s1+l);
	if (r == 0) {
		if (l0 == l1)
			return 0;
		else if (l0 > l1)
			return 1;
		else
			return -1;
	}
	else {
		return r;
	}

}
int main(){
	int N;
	int M;
	cin >> N >> M;
	cin >> str;

	powers = new unsigned long long[str.length() + 1];
	hash_table = new unsigned long long[str.length() + 1];

	powers[0] = 1;
	hash_table[str.length()] = 0;


	for (int i = 0; i < str.length(); i++)
		powers[i+1] = (powers[i] * P) % Q;

	for (int i = str.length(); i >= 0; i--)
		hash_table[i] = ((hash_table[i+1] * P) % Q + str[i]) % Q;

	//for (int i = 0; i < str.length() + 1; i++)
	//	cout << hash_table[i] << "\t" << powers[i] << endl;

	for (int i = 0; i < M; i++){
		int s0, e0, s1, e1;
		cin >> s0 >> e0 >> s1 >> e1;
		s0--; e0--; s1--; e1--;
		char c;
		if (hash_cmp(s0, e0, s1, e1) == -1)
			c = '<';
		else if (hash_cmp(s0, e0, s1, e1) == 1)
			c = '>';
		else
			c = '=';
		cout << c << "\n";
	}

	delete [] powers;
	delete [] hash_table;
}
