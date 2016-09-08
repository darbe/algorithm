#include<iostream>
#include<string>
using namespace std;
#define SIZE 100
class BigData{
	friend ostream &operator<<(ostream &out, const BigData &data);
	friend istream &operator>>(istream &in, BigData &data);
	friend BigData operator+(const BigData &op1, const BigData &op2);
	friend BigData operator-(const BigData &op1, const BigData &op2);
public :
	BigData();
	BigData(const char *op);
	BigData (const BigData &);
	BigData& operator = (const BigData &);
	BigData& operator += (const BigData &);
	BigData& operator -= (const BigData &);
	~BigData();
private :
	char *num;
	int size;
	static void addBig(const char *op1, const char *op2, char * &num);
	static void subBig(const char* op1, const char* op2, char * &num);
};
BigData :: BigData(){
	num = new char[1];
	num[0] = '\0';
	size = 0;
}


BigData& BigData ::operator = (const BigData &src){
	if(this ==  &src){
		return *this;
	}
	delete[] num;
	int len = strlen(src.num);
	num = new char[len + 1];
	strcpy(num,src.num);
	size = src.size;
	return *this;
}
BigData& BigData::operator += (const BigData &src){
	BigData result = *this + src;
	delete[] num;
	size = result.size;
	num = new char[strlen(result.num)+1];
	strcpy(num,result.num);
	return *this;
}
	
BigData& BigData::operator -= (const BigData &src){
	BigData result = *this - src;
	delete[] num;
	size = result.size;
	num = new char[strlen(result.num)+1];
	strcpy(num,result.num);
	return *this;
}

		
BigData::BigData (const BigData & src){
	int len = strlen(src.num);
	num = new char[len + 1];
	strcpy(num,src.num);
	size = src.size;
}

BigData :: BigData(const char *op){
	if(op == NULL){
		num = new char[1];
		num[0] = '\0';
		size = 0;
		return;
	}	
	int len = strlen(op);
	num = new char[len + 1];
	strcpy(num,op);
	size = num[0] == '-'? len-1 : len;
}
ostream &operator << (ostream &out, const BigData &data){
	out << data.num;
	return out;
}
istream &operator >> (istream &in, BigData &data){
	if(data.num != NULL){
		delete[] data.num;
	}
	data.num = new char[SIZE];
	in >> data.num;
	int size = strlen(data.num);
	data.size = data.num[0] == '-'? size-1 : size; 
	return in;
}
BigData::~BigData(){
	if(num != NULL){
		delete[] num;
	}
	num = NULL;
	size = 0;
}
void reverseStr(char * str){
	if(str == NULL){
		return ;
	}
	int j = strlen(str) - 1;
	int i = 0;
	while(i < j){
		std::swap(str[i++],str[j--]);
	}
}

BigData operator+(const BigData &op1, const BigData &op2){
	if(op1.size == 0){
		return op2;
	}
	if(op2.size == 0){
		return op1;
	}
	int len1 = op1.size;
	int len2 = op2.size;
	int size = len1 > len2 ? len1 : len2;
	char * res = new char[size+4];
	char *op1NotNeg = new char [len1+2];
	char *op2NotNeg = new char [len2+2];
	if(op1.num[0] == '-' && op2.num[0] != '-'){
		strcpy(op1NotNeg,op1.num+1);
		BigData::subBig(op2.num,op1NotNeg,res);
	}else if(op1.num[0] == '-' && op2.num[0] == '-'){
		strcpy(op1NotNeg,op1.num+1);
		strcpy(op2NotNeg,op2.num+1);
		BigData::addBig(op1NotNeg,op2NotNeg,res);
		int len = strlen(res);
		for(int i = len; i >= 0; i--){
			res[i+1] = res[i];
		}
		res[0] = '-';
	}else if(op1.num[0] != '-' && op2.num[0] != '-'){
		BigData::addBig(op1.num,op2.num,res);
	}else if(op1.num[0] != '-' && op2.num[0] == '-'){
		strcpy(op2NotNeg,op2.num+1);
		BigData::subBig(op1.num,op2NotNeg,res);
	}
	BigData  re(res);
	delete[] op1NotNeg;
	delete[] op2NotNeg;
	delete[] res;
	return re;
}
		
BigData operator-(const BigData &op1, const BigData &op2){
	int len1 = op1.size;
	int len2 = op2.size;
	int size = len1 > len2 ? len1 : len2;
	char * res = new char[size+4];
	char *op1NotNeg = new char [len1+2];
	char *op2NotNeg = new char [len2+2];
	if(op1.num[0] == '-' && op2.num[0] != '-'){
		strcpy(op1NotNeg,op1.num+1);
		BigData::addBig(op2.num,op1NotNeg,res);
		cout << res <<endl;
		int len = strlen(res);
		for(int i = len; i >= 0; i--){
			res[i+1] = res[i];
		}
		res[0] = '-';
	}else if(op1.num[0] == '-' && op2.num[0] == '-'){
		strcpy(op1NotNeg,op1.num+1);
		strcpy(op2NotNeg,op2.num+1);
		BigData::subBig(op2NotNeg,op1NotNeg,res);
	}else if(op1.num[0] != '-' && op2.num[0] != '-'){
		BigData::subBig(op1.num,op2.num,res);
	}else if(op1.num[0] != '-' && op2.num[0] == '-'){
		strcpy(op2NotNeg,op2.num+1);
		BigData::addBig(op1.num,op2NotNeg,res);
	}
	BigData  re(res);
	delete[] op1NotNeg;
	delete[] op2NotNeg;
	delete[] res;
	return re;

}	
void BigData:: addBig(const char *op1, const char *op2, char * &num){
	//int len1 = op1.size;
	//int len2 = op2.size;
	int len1 = strlen(op1);
	int len2 = strlen(op2);
	int size = len1 > len2 ? len1 : len2;
	//char * num = new char[size+2];
	int i = len1 - 1;
	int j = len2 - 1;
	int sum = 0;
	int k = 0;
	while(i >=0 || j >= 0){
		sum /= 10;
		if(i >= 0){
			sum += op1[i--] - '0';
		}
		if( j >= 0){
			sum += op2[j--] - '0';
		}
		num[k++] = sum % 10 + '0';
	}
	if(sum / 10== 1){
		num[k] = '1';
		size ++;
	}
	num[size] = '\0';
	reverseStr(num);
	//BigData result(num);
	//delete[] num;
	//return result;
}
void BigData:: subBig(const char* op1, const char* op2, char * &num){
	//int len1 = op1.size ;
	//int len2 = op2.size ; // we must check here if size == 0
	int len1 = strlen(op1);
	int len2 = strlen(op2);
	const char * dvd = NULL;
	const  char * dvded = NULL;
	int sign = 1;
	int i = 0;
	int j = 0;
	if(len1 > len2 || (len1 == len2 && strcmp(op1, op2) >= 0)){
		dvd = op1;
		dvded = op2;
		i = len1 ;
		j = len2 ;
	}else{
		dvd = op2;
		dvded = op1;
		sign = -1;
		i = len2 ;
		j = len1 ;
	}
	//char * num = new char[i+2];
	i--;
	j--;
	int sum = 0;
	int k = 0;
	while(i >= 0 || j >= 0){
		if(i >= 0){
			sum += dvd[i--] - '0';
		}
		if(j >= 0){
			sum -= dvded[j--] - '0';
		}
		if(sum < 0){
			num[k++] = 10 + sum + '0';
			sum = -1;
		}else{
			num[k++] = sum + '0';
			sum = 0;
		}
	}
	k--;
	while(k >= 0 && num[k] == '0'){
		k--;
	}
	if(sign < 0){
		num[++k] = '-';
	}
	num[++k] = '\0';
	reverseStr(num);
	//BigData result(num);
	//delete[] num;
	//return result;
}
	
int main(){
	BigData b1;
	BigData b2;
	BigData bb1("5467");
	BigData bb2("99998");
	cout <<bb1 << " + "<< bb2 << " "<< bb1 + bb2<<endl;
	
	cin >> b1;
	cin >> b2;
	b1 += b2;
	cout <<b1 << " + "<< b2 << " "<< b1<<endl;
	cin >> b1;
	cin >> b2;
	b1 -= b2;
	cout <<b1 << " - "<< b2 << " "<< b1<<endl;

	

}	


	

