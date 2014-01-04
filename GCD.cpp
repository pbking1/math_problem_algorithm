//欧几里得算法：(gcd(a,b)=gcd(b,a%b))
//拓展欧几里得算法：y -= a/b * x
//应用判断不定方程是否有整数解，求不定方程的整数解， 判断在规定范围内有多少整数解
#include<iostream>
#include<string.h>
using namespace std;
int a, b, x, y, d;
void gcd(int a, int b){
	if(!b){
		x = 1; y = 0; d = a;
	}else{
		gcd(b, a % b);
		int temp = x;
		x = y;
		y = temp - a / b * x;
	}
}
//对于a1=b， b1=a%b而言，我们求得x,y使得a1*x+b1*y=GCD(a1,b1)
//因为b1=a%b=a-a/b*b
//得到：a1*x+b1*y=GCD(a1,b1)
//==> b*x+(a-a/b*b)y=GCD(a1,b1) ==> GCD(a,b)
//==> a*y + b*(x-a/b*y) = GCD(a,b)
//所以对于a和b而言，他们对应的p，q分别是y和(x-a/b*y)
void gcd1(int a, int b, int &d, int &x, int &y){
	if(!b)
		x = 1, y = 0, d = a;
	else{
		gcd1(b, a % b, d, y, x);
		y -= a / b * x;
	}
}

int main(){
	int cas;
	cin>>cas;
	while(cas--){
		cin>>a>>b;
		gcd1(a, b, d, x, y);
		cout<<a<<"*"<<x<<"+"<<b<<"*"<<y<<"="<<d<<endl;
	}
	return 0;
}
