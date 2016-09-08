#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<assert.h>
using namespace std;
void rebulid(int n){
	vector<int> data(n,0);
	list<int> free;
	int k = 1;
	for(int i  = 0; i < n; i++){
		if(i % 2 != 0){
			data[i] = k++;
		}else{
			free.push_back(i);
		}
	}
	if(n % 2 == 0){
		while(!free.empty()){
			list<int>::iterator iter = free.begin();
			while(iter != free.end()){
				iter++;
				if(iter == free.end()){
					iter = free.begin();
				}
				if(iter != free.end()){
					data[*iter] = k++;
					iter = free.erase(iter);
				}
				if(iter == free.end()){
					iter = free.begin();
				}
			}
		}
	}else{
		while(!free.empty()){
			list<int>::iterator iter = free.begin();
			while(iter != free.end()){
				data[*iter] = k++;
				iter = free.erase(iter);
				if(iter == free.end()){
					iter = free.begin();
				}
				if(iter != free.end()){
					iter++;
				}
				if(iter == free.end()){
					iter = free.begin();
				}
			}
		}
	}
	queue<int> q;
	for(int i = 0; i < n; i++){
		q.push(data[i]);
	}
	cout <<endl;
	int idx = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		q.push(x);
		assert(q.front() == ++idx);
		q.pop();
	}

}
int main(){
	for(int i = 0; i < 1000; i++){
		rebulid(i);
	}
	
	return 0 ;
	/*
	cout <<endl;
	for(int i = 0; i < n; i++){
		cout << i<< " ";
	}
	cout <<endl;
	queue<int> q;
	for(int i = 0; i < n; i++){
		cout << data[i]<< " ";
		q.push(data[i]);
	}
	cout << endl;
	cout << endl;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		q.push(x);
		cout <<q.front() << " ";
		q.pop();
	}*/
}

