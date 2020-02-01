#include "NumberRepository.h"
#include<iostream>
using namespace std;

NumberRepository n;
int main(){
	string s;
	while( getline(cin,s) ){
		int num=n.ToNumber(s);
		if(num==-1) cout<<"Ê¶±ðÊ§°Ü"<<endl;
		else cout<<num<<endl;
	}
	return 0;
}
