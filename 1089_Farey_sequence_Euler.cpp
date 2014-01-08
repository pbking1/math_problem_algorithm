#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
//欧拉函数是少于或等于n的数中与n互质的数的数目  
////通式：φ(x)=x(1-1/p1)(1-1/p2)(1-1/p3)(1-1/p4)…..(1-1/pn),其中p1, p2……pn为x的所有质因数，x是不为0的整数。  
////φ(1)=1（唯一和1互质的数就是1本身）。  
////知道了这个还不一定做出来，他编程实现还需要用筛选法那种方式，才能大大降低实现复杂度  
const int MAXP = 1000000;
int prime[MAXP];
bool isprime[MAXP];
int num[MAXP];
void primelist(){
	memset(isprime, true, sizeof(isprime));
	for(int i = 2; i <= MAXP; i++){
		if(isprime[i])
			prime[++prime[0]] = i;
		for(int j = 1, k; (j <= prime[0]) && (k = i * prime[j]) <= MAXP; j++){
			isprime[k] = false;
			if(i % isprime[j] == 0)
				break;
		}
	}
}

long long result[1000005], n;
long long euler[MAXP + 5];
void Euler(){
	for(int i = 2; i <= MAXP; ++i)
		euler[i] = i;
	for(int i = 1; i <= prime[0]; ++i){
		int p = prime[i];
		for(int j = p; j <= MAXP; j+=p){
			if(j % p != 0)
				continue;
			euler[j] = euler[j] / (p * (p - 1));
		}
	}
}

int main(){
	primelist();
	Euler();
	
	result[2] = 1;
	for(int i = 3; i <= 1000000; ++i)
		result[i] = result[i - 1] + euler[i];
	while(cin>>n && n){
		cout<<result[n]<<endl;
	}
	return 0;
}
