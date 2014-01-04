#include<iostream>
#include<cstdio>
#include<memory.h>
#include<cstring>
#include<string>
using namespace std;
int main(){
	int n;
	int temp;
	int num1;
	string num2;
	int result[110];
	cin>>n;
	while(n--){
		memset(result, 0, sizeof(result));
		cin>>num2;
		cin>>num1;
		//see if there is a zero in the number, if there is a zero then the
		//result is zero
		if(num2.at(0) == '0' || num1 == 0){
			cout<<0<<endl;
			continue;
		}

		int k = 109;
		//carry
		for(int j = num2.length() - 1; j >= 0; j--, k--){
			num2[j] = num2.at(j) - '0';  //convert the char into number
			temp = result[k] + num2[j] * num1;  //the algorithm of multiply
			result[k] = temp % 10;   //the result of the ones place
			result[k - 1] = temp / 10;  //carry
		}

		int j;
		//find in the string result the position of the first non-zero character 
		for(j = 0; result[j] == 0; j++){}
		//print out the result
		for(; j < 110; j++){
			cout<<result[j];
		}
		cout<<endl;
	}
	return 0;
}
