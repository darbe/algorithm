#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<cstdio>
#include<cstdlib>
#include<memory>
#include<functional>
using namespace std;
struct TreeNode{
	vector<TreeNode*> clild;
	int val;
	int app;
	TreeNode(int v, int a):val(v),app(a){}
};
void findMax(vector<int>res, int &first, int &second){
	if(res.size() == 0)return ;
	if(res.size() == 1){
		first = res[0];
		return ;
	}
	first = max(res[0],res[1]);
	second = min(res[0],res[1]);
	for(int i = 2; i < res.size();i ++){
		if(res[i] > first){
			second = first;
			first = res[i];

		}else if(res[i] <= first && res[i] > second){
			second = res[i];
		}
		
	}
}

class Solution {
private:
    int maxval;
    int maxHelper(TreeNode *root){
        if(root == NULL)return 0;
		vector<TreeNode*> child = root->clild;
		vector<int>res;
		for(int i = 0; i < child.size(); i++){
			int v = maxHelper(child[i]);
			res.push_back(v);
		}
		int first = 0;
		int second = 0;
		findMax(res,first,second);
        maxval = std::max(maxval,first+second+root->app);
        return first+root->app;
	}
public:
    int maxPathSum(int N, int K, int * app, int T[][2]) {
        maxval = INT_MIN;
        maxHelper(count(N,K,app,T));
        return maxval;
    }
	TreeNode* count(int N, int K, int * app, int T[][2]){
		set<int> s;
		for(int i = 0; i < K; i++){
			s.insert(app[i]);
		}
		vector<TreeNode *> nodes;
		for(int i = 0; i < N ; i++){
			int a = 0;
			if(s.find(i+1) != s.end()){
				a = 1;
			}else{
				a = 0;
			}
			TreeNode * node = new TreeNode(i+1,a);
			nodes.push_back(node);
		}
		for(int i = 0; i < N -1; i++){
			int fisrt = T[i][0];
			int second = T[i][1];
			nodes[ fisrt-1]-> clild.push_back(nodes[second-1]);
		}
		return nodes[0];
	}
};
