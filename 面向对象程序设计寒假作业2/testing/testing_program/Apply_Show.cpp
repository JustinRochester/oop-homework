#include "VariableRepository.h"
#include<iostream>
using namespace std;

VariableRepository v;
int main(){
    char c;
    int num;
    string s,number,order;
    while(cin>>c){
        if(c=='s'||c=='S'){
            getline(cin,s);
            if( s[0]=' ' ) s=s.substr( s.find(" ")+1 );
            num=v.VariableShow(s);
            if(num<0) cout<<"变量不存在"<<endl;
            else cout<<num<<endl;
        }
        else if(c=='a'||c=='A'){
            getline(cin,s);
            if( s[0]=' ' ) s=s.substr( s.find(" ")+1 );
            if(!v.VariableApply(s)) cout<<"变量已申请"<<endl;
        }
    }
    return 0;
}
