#include<iostream>
using namespace std;

int GCD(int a, int b){
	int tmp = 0;
	while(b){
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}


int main(){
	cout << GCD(120,210);
}
		
