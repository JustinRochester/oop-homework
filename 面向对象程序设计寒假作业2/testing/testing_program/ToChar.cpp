#include "NumberRepository.h"
#include<iostream>
using namespace std;

NumberRepository n;
int main(){
	int number;
	while( cin>>number ) cout<<n.ToChar(number)<<endl;
    return 0;
}
