#include<iostream>
#include<map>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<set>
using namespace std;

void helper(int num ,vector<int> & unluck,vector<int> & luck, map<int,int> &m,vector<int> &res, int carry){
	if(num == 0 && carry == 0){
		return;
	}
	int digit = num % 10;
	digit += carry;
	carry = 0;
	if(m.count(digit) != 0){
		for(int i = 0; i < res.size(); i++){
			res[i] = *luck.begin();
		}
		vector<int>::iterator pos = lower_bound(luck.begin(),luck.end(),digit);
		if(pos == luck.end()){
			carry = 1;
			res.push_back(*luck.begin());
		}else {
			carry = 0;
			res.push_back(*pos);
		}
	}else{
		res.push_back(digit);
	}
	
	helper(num/10,unluck,luck,m,res,carry);
}
int getlucky(int num ,vector<int> & unluck){
	vector<int> res;
	vector<int> luck;
	map<int,int> m;
	if(unluck.size() == 0)return num;
	sort(unluck.begin(), unluck.end());
	int k = 1;
	for(int i = 0 ; i < unluck.size(); ){
		if(k < unluck[i]){
			luck.push_back(k);k++;
		}else if(k == unluck[i]){
			i++;k++;
		}else {
			i++;
		}
	}
	for(int i = unluck.back()+1 ; i < 10; i++){
		luck.push_back(i);
	}
	for(int i  = 0; i < unluck.size(); i++){
		m[unluck[i]] = i;
	}
	m[0] = 1;
	m[10] = 1;
	int carry = 0;

	helper(num, unluck,luck,m,res, carry);
	int result = 0;
	for(int i = res.size() -1 ; i >= 0; i--){
		result = result * 10 + res[i];
	}

	return result;
}
bool check(int num, map<int, int>& unlucky){
	while(num){
		int digit = num % 10;
		if(unlucky.count(digit) != 0){
			return false;
		}
		num /= 10;
	}
	return true;
}
int getlucky2(int num ,vector<int> & unluck){
	map<int,int> m;
	if(unluck.size() == 0)return num;
	for(int i  = 0; i < unluck.size(); i++){
		m[unluck[i]] = i;
	}
	m[0] = 1;

	while(!check(num,m)){
		num++;
	}
	return num;
}
void test2(){
	srand((unsigned) time(NULL));
	int count = 0;
	while(count < 1000){
		vector<int> res;
		int round = rand() % 10 ;
		cout  << round << " round"<<endl;
		set<int> s;
		for(int i = 0; i < round; i++){
			s.insert((rand() % 9) + 1);
		}
		for(auto &&ss : s){
			res.push_back(ss);
		}
		int num = rand() % 10000;
	
		int n1 =  getlucky(num,res);
		int n2 =  getlucky2(num,res);
		assert(n1 == n2);
		count ++;
	}
}
int main(){
    teset2()	
}
