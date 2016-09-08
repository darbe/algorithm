#include<iostream>
#include<string>
#include<vector>

using namespace std;

/*	
	if you want to treat space as a normal character, you ingore the code below.
	Ohterwise, you should comment the deifine NOTRIM.
	It will tirm the space at begin and end of word, like:
	"  Hello world   "---> "Hello Word".
	So Text == "" will matched by  Patten == "    "
*/

//#define NOTRIM


typedef int (*KMPFun)(const string &, const string &);
/* we implement a funtion to trim space in fisrt and end of a string. 
   so when we  want to treat space trival character (e.g not a valid character)  
   we call call this  fun
*/
inline void trimSpace(string &str){
	if(str.size() == 0)return ;
	auto pos = str.find_last_not_of(" ");
	str.erase(pos+1);
	if(str.size() == 0)return ;
	pos = str.find_first_not_of(" ");
	str.erase(0,pos);
}
	

 
// construct next;
void findNext(const string &P, vector<int> &Next){// here i make a mistakes when I copy from paper. It should not const
	if(P.size() == 0){
		return;
	}
	Next[0] = 0;
	int k = 0;
	for(int i = 1; i < P.size(); i++){
		while(k > 0 && P[i] != P[k]){
			k = Next[k-1];
		}
		if(P[i] == P[k]){
			k++;
			Next[i] = k;
		}
	}
}

// kmp used, T for text, and P for Pattern
int search(const string &T, const string & P){
	if(T.size() == 0 && P.size() != 0){
		return 0;
	}
	if(P.size() == 0){
		return 1;
	}
	int j = 0;
	vector<int> Next(P.size(), 0);
	findNext(P,Next);
	for(int i = 0; i < T.size(); i++){
		while(j > 0 && T[i] != T[j]){
			j = Next[j-1];
		}
		if(P[i] == T[j]){
			j++;
		}
		if(j == P.size()){
			return 1;
		}
	}
	return j == P.size();
}
int trimSearch(const string &T, const string & P){
	/*	
		if you want to treat space as a normal character, you ingore the code below.
		Ohterwise, you should open the comment here.
		It will tirm the space at begin and end of word, like:
		"  Hello world   "---> "Hello Word".
		So Text == "" will matched by  Patten == "    "
	*/
	string Text = T;
	string Pattern = P;
	trimSpace(Text); 
	trimSpace(Pattern); 
        return search(Text,Pattern);
}
	
void printSearch(const string& T, const string &P, const KMPFun kmp){
	cout << "In "<<(T.size()? T:"null text")<<" we "<<(kmp(T,P)? "Found ":"NotFound ")<<(P.size()?P:"null pattern")<<endl;
}

// unit test 
void test(){
#ifdef NOTRIM
	KMPFun kmp = search;
#else
	KMPFun kmp = trimSearch;
#endif
	string t1 = "";// no character;
	string p1 = "";// no character;
	printSearch(t1,p1,kmp);

	string t2= " ";//sapce;
	string p2 = " ";// space;
	search(t2,p2);
	printSearch(t2,p2,kmp);


	string t3 = "abcda";// text not null;
	string p3 = "";// patten null;
	search(t3,p3);
	printSearch(t3,p3,kmp);

	string t4 = "abcda";// cannot find;
	string p4 = "e";
	search(t4,p4);
	printSearch(t4,p4,kmp);

	string t5 = "abcda";// exactly find
	string p5 = "a"; 
	search(t5,p5);
	printSearch(t5,p5,kmp);

	string t6 = "abcdab";//  there are two matched so return true
	string p6 = "ab";
	search(t6,p6);
	printSearch(t6,p6,kmp);


	string t7 = "abcad";// total matched
	string p7 = "abcad";// 
	search(t7,p7);
	printSearch(t7,p7,kmp);

	string t8 = "abcad";// the pattern is bigger;
	string p8 = "abcade";
	search(t8,p8);
	printSearch(t8,p8,kmp);


	string t9= "      ";//text has more sapce than pattern ;
	string p9 = " ";
	search(t9,p9);
	printSearch(t9,p9,kmp);

	string t10= "";//text is null
	string p10 = " ";// pattern is space
	search(t10,p10);
	printSearch(t10,p10,kmp);

	string t11= " ";//text has fewer sapce than pattern;
	string p11 = "     ";
	search(t11,p11);
	printSearch(t11,p11,kmp);

	string t12= "a";//sapce;// one character  
	string p12 = "b";// space;
	search(t12,p12);
	printSearch(t12,p12,kmp);

	string t13= "a";//sapce; // text ha one character and pattern has more
	string p13 = "abb";// space;
	search(t13,p13);
	printSearch(t13,p13,kmp);

}

int main(){
	test();
}
