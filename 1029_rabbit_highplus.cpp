//one pair of rabbit can give birth to one pair of kid rabbit every month and after m month the kid rabbit can become adult rabbits
//print the number of rabbit pairs of rabbits after d months.
#include<iostream>
#include<cstdio>
using namespace std;
int rabbit[110][110];
int m,d;
void add(int a[], int b[], int c[]){
	int i;
	memset(c, 0, sizeof(rabbit[0]));
	for(i = 0; i <= 105; i++){
		int temp = a[i] + b[i] + c[i];
		c[i] = temp % 10;
		c[i + 1] = temp / 10;
	}
}
//the first column of the matric is the month d and the next column is after matric[0] month how many rabbit
int main(){
	cin>>m>>d;  //after m month the rabbit become adult and after d month
	while(m != 0){
		int i,j;
		memset(rabbit, 0, sizeof(rabbit[0]));
		rabbit[0][0] = 1;
		for(i = 1; i < m; i++)
			rabbit[i][0] = i + 1;    //i is month
		for(i = m; i <= d; i++)
			add(rabbit[i - 1], rabbit[i - m], rabbit[i]);
		for(i = 109; i >= 0; i--)
			if(rabbit[d][i] != 0){
				j = i;
				break;
			}
		for(; j >= 0; j--)
			cout<<rabbit[d][j];
		cout<<endl;
		cin>>m>>d;
	}
	return 0;
}
		
