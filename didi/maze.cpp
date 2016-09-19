#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
using namespace std;
int curmin = INT_MAX;
vector<pair<int, int> > result;
void dfs(vector<vector<int> > &nums,vector<pair<int, int> > &res, int i, int j, int cur, bool &succ, int add, int P, int n, int m){
   if(i < 0 || i >= n || j < 0 || j >= m || nums[i][j] == 0 || cur + add >= curmin || cur + add >= P){
        return;
    }
   cur += add;
   res.push_back(make_pair(i,j));
   if(i == 0 && j == m-1){
        succ = true;
        if(cur < curmin){
            curmin = cur;
            result = res;
        }
	res.pop_back();
        return ;
    }

    nums[i][j] = 0;
    dfs(nums,res,i+1,j,cur,succ,0,P,n,m);
    dfs(nums,res,i-1,j,cur,succ,3,P,n,m);
    dfs(nums,res,i,j+1,cur,succ,1,P,n,m);
    dfs(nums,res,i,j-1,cur,succ,1,P,n,m);
    nums[i][j] = 1;
    res.pop_back();
    
}
bool computeMaze(vector<vector<int> > &nums, int P, int n, int m){
    bool succ = false;
    vector<pair<int, int> > res;
    dfs(nums,res,0,0,0,succ,0,P,n,m);
    if(succ){
        return true;
    }
    return false;
}
int main(){
    int n  = 0;
    int m = 0;
    int P = 0;
    while(cin >> n >> m >> P){
        int val = 0;
        vector<vector<int> > nums(n,vector<int>(m,0));
        vector<pair<int, int> > res;
        for(int i = 0; i < n ; i++){
            for(int j = 0; j < m; j++){
                cin >> val;
                nums[i][j] = val;
            }
            
        }
        bool flag = computeMaze(nums,P,n,m);
        if(!flag){
            cout << "Can not escape!"<<endl;
        }else{
            for(int i = 0; i < result.size(); i++){
		if(i != result.size()-1)
                    cout << "[" << result[i].first<< ","<<result[i].second<<"]"<<",";
		else 
		    cout << "[" << result[i].first<< ","<<result[i].second<<"]";

            }
	    cout << endl;
        }
    }
}
