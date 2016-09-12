#include<iostream>
#include<map>
#include<vector>
#include<list>
using namespace std;
struct Block{
	int handle;
	int addr;
	int size;
	Block(int h, int a, int s):handle(h),addr(a),size(s){}
};
int Mycount = 1;
int myMalloc(list<Block> &free, int size){
	auto it = free.begin();
	for(; it != free.end(); it++){
		if(it->size >= size){
			it->size = it->size - size;
			int addr = it->addr;
                        if(it->size == 0) {
				it = free.erase(it);
			}else{
				it->addr = it->addr + size;
			}
			return addr;
		}		
	}
	return -1;
}
int myNew(list<Block> &free, map<int, Block> &use, int size){
	int addr = myMalloc(free,size);
	if(addr < 0) return -1;
	Block newblock(Mycount,addr,size);
	use.insert(make_pair(Mycount,newblock));
	Mycount++;
	return Mycount-1;
}
void myFree(list<Block> &free, int size, int addr){//  need to be tested about list
	auto it = free.begin();
	
	for(; it != free.end(); it++){
		if(addr  < it->addr){
			break;
		}
	}
	Block newBlock(0,addr,size);
	free.insert(it,newBlock);
}

int myDelete(list<Block> &free, map<int, Block> &use, int handle){
	auto pos = use.find(handle);
	if(pos == use.end()) return -1;
	Block blockToDel = pos->second;
	use.erase(pos);
	int addr = blockToDel.addr;
	int size = blockToDel.size;
	myFree(free,size,addr);
	return 1;
}
void def(list<Block> &free, map<int, Block> &use, int initSize){
	auto pos = use.begin();
	//auto &pos = use.begin();
	int totalSize = 0;
	for(; pos != use.end(); pos++ ){
		totalSize += pos->second.size;
	}
	Block initBlock(0,totalSize,initSize-totalSize);
	free.clear();
	free.push_back(initBlock);
	int initAddr = 0;
	for(pos = use.begin(); pos != use.end(); pos++){
		pos->second.addr = initAddr;
		initAddr += pos->second.size;
	}
}

	
int main(){
	int round = 0; int initSize = 0;
	list<Block> free;
        list<Block> total;
	map<int , Block> used;
	cin >> round >> initSize;
	Block initBlock(0,0,initSize);
	free.push_back(initBlock);
	string op;
	int size = 0;
	int handle = 0;
	int status = 0;
	for(int i  = 0; i < round; i++){
		cin >> op;
		if(op == "new"){
			cin >> size;
			status = myNew(free,used,size);
			if(status == -1){
				cout << "NULL";
			}
			cout << status << endl;
		}else if(op == "del"){
			cin >> handle;
			status = myDelete(free,used,handle);
		}else if(op == "def"){
			def(free, used,initSize);
		}
	}
}
