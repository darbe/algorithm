#include<iostream>
#include "tree.h"
#include<queue>
using namespace std;

bool isCompleteTree(TreeNode *root){
	if(root == NULL){
		return true;
	}
	queue<TreeNode *> q;
	q.push(root);
	int n = 1;
	bool end = false;
	while(!q.empty()){
		TreeNode * node = q.front();
		q.pop();
		if(node->left && !end){
			q.push(node->left);
		}else if(!end && node->left == NULL){
			end = true;
		}else if(end && node->left){
			return false;
		}
		if(!end && node->right){
			q.push(node->right);
		}else if(!end && node->right  == NULL){
			end = false;
		}else if(end &&  node->right ){
			return false;
		}
	}
	return true;

}
int main(){
	 TreeNode *root     = new TreeNode(1);
	 root->left         = new TreeNode(2);
	 root->right        = new TreeNode(3);
	 //root->right->left  = new TreeNode(10);	
	 //root->left->left   = new TreeNode(4);
	 // root->left->right  = new TreeNode(5);
	 //root->right->right = new TreeNode(6);
	 cout << isCompleteTree(root)<<endl;
}