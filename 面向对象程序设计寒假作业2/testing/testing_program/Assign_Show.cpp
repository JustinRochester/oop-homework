#include "VariableRepository.h"
#include<iostream>
using namespace std;
VariableRepository v;

int main(){
	v.VariableApply("var");
	char c;
	int num;
	while( cin>>c ){
		if(c=='s'||c=='S') cout<<v.VariableShow("var")<<endl;
		else if(c=='a'||c=='A'){
			cin>>num;
			v.VariableAssign("var",num);
		}
	}
    return 0;
}
