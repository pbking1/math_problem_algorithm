//p*e(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x2 + u = 0
//g(x) = x – (x – A/x) / 2 根据这条公式迭代就可以
//终止条件是前后两次迭代出来的值少于1e-6

//0 <= x <= 1
//Sample Input
//0 0 0 0 -2 1
//1 0 0 0 -1 2
//1 -1 1 -1 -1 1
//Sample Output
//0.7071
//No solution
//0.7554
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
double x;
int p, q, r, s, t, u;

inline double fun(double x){
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

inline double fun_1(double x){
	return -p * exp(-x) + q * cos(x) - r * sin(x) + s / (cos(x) * cos(x)) + 2 * t * x;
}

int main(){
	while(cin>>p>>q>>r>>s>>t>>u){
		double x1 = fun(0.0);
		double x2 = fun(1.0);
		if(x1 == 0){
			puts("0.0000");
			continue;
		}
		if(x2 == 0){
			puts("0.0000");
			continue;
		}
		if(x1 * x2 > 0){
			puts("No solution");
			continue;
		}
		x = 0.5; //start from 0.5
		double temp = 0.0;
		while(fabs(x - temp) > 1e-6){
			temp = x;
			x -= fun(x) / fun_1(x);
		}
		printf("%.4f\n", x);
	}
	return 0;
}

