//输入一个十进制数，然后用-2进制
//e.g input 30000 -2
//output 30000=11011010101110000
#include<iostream>
#include<string>
using namespace std;

string ans;
char ns[21] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
	'A', 'B', 'C', 'D', 'E', 'F', 'D', 'H', 'I', 'J'};
int main(){
	int m, n, k, t, s;
	while(cin>>m>>n){
		ans = "";
		s = m;
		while(m != 0){
			k = m % n;
			t = m / n;
			if(k < 0){
				k -= n;
				t++;
			}
			m = t;
			ans.push_back(ns[k]);
		}
		cout<<s<<"=";
		for(int i =  ans.length() - 1; i >= 0; i--)
			cout<<ans[i];
	}
	cout<<"(base"<<n<<")"<<endl;
	return 0;
}





