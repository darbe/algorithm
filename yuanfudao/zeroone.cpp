#include<iostream>
#include<map>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<set>

using namespace std;

int findMax(vector<int>& nums){
	vector<int> sum(nums.size()+1,0);
	for(int i = 1; i <= nums.size(); i++){
		sum[i] = sum[i-1] + nums[i-1];
	}
	map<int, pair<int,int>> m;
	map<int, pair<int,int>>::iterator pos;
	for(int i = 1; i <= nums.size(); i++){
		pos = m.find(sum[i]);
		if(pos == m.end()){
			m[sum[i]] = make_pair(i,0);
		}else{
			pos->second.second = i;
		}
	}
	int maxv = 0;
	for(pos = m.begin(); pos != m.end(); pos++){
		if((pos->second.first  && pos->second.second ) || pos->first == 0){
			if(pos->first == 0){
				maxv = max(maxv,pos->second.second);
				maxv = max(maxv,pos->second.first);
			}else{
				maxv = max(maxv,pos->second.second - pos->second.first);
			}

		}
	}
	return maxv;
}
int findMax2(vector<int>& nums){
	int maxv = 0;
	for(int i = 0; i < nums.size(); i++){
		int sum = 0;
		int tmpmax = 0;
		for(int j = i; j < nums.size(); j++){
			sum += nums[j];
			if(sum == 0){
				tmpmax = j - i + 1;
			}
		}
		maxv = max(maxv,tmpmax);
	}
	return maxv;
}
void test(){
	srand((unsigned) time(NULL));
	int count = 0;
	while(count < 100){
		vector<int> res;
		int round = rand() % 1000 ;
		cout  << round << " round"<<endl;
		for(int i = 0; i < round; i++){
			res.push_back(rand() % 2 == 0 ? 1 : -1);
		}
		int v1 = findMax(res);
		int v2 = findMax2(res);
		assert(v1 == v2);
		count ++;
	}
}
int main(){
    test();	
}
