#include<string>
#include<map>
using namespace std;

#ifndef NUMBERREPOSITORY
#define NUMBERREPOSITORY
class NumberRepository{
    private:
        map<int,string> numberChar;
        map<string,int> charNumber;
        void NumberCharPrepare(){
        	numberChar[0]="��";
        	numberChar[1]="һ";
        	numberChar[2]="��";
        	numberChar[3]="��";
        	numberChar[4]="��";
        	numberChar[5]="��";
        	numberChar[6]="��";
        	numberChar[7]="��";
        	numberChar[8]="��";
        	numberChar[9]="��";
        	numberChar[10]="ʮ";
        	numberChar[100]="��";
        	numberChar[1000]="ǧ";
        	numberChar[10000]="��";
        	numberChar[100000000]="��";
		}
		void CharNumberPrepare(){
			charNumber["��"]=0;
			charNumber["һ"]=1;
			charNumber["��"]=2;
			charNumber["��"]=3;
			charNumber["��"]=4;
			charNumber["��"]=5;
			charNumber["��"]=6;
			charNumber["��"]=7;
			charNumber["��"]=8;
			charNumber["��"]=9;
			charNumber["ʮ"]=10;
			charNumber["��"]=100;
			charNumber["ǧ"]=1000;
			charNumber["��"]=10000;
			charNumber["��"]=100000000;
		}
        bool FindChar(int &number,string num){
        	if( charNumber.find(num)==charNumber.end() ) return 0;//�Ҳ��� 
        	number=charNumber[num];
        	return true;
        }
        bool FormatChar(string &num){
            int temporary[3];
            for(int i=0;i<=num.size()-2;i+=2)
				if( !FindChar(temporary[i>>1],num.substr(i,2)) ) return false;//�ַ��Ϸ��Լ���
            if( num.size()==2 ) num=numberChar[0]+num;//һ���֣�ǰ���㣬ʮ��Ϊ������Ҳ������������
            else if( num.size()==4 ){
                if(temporary[0]==10&&temporary[1]==10) return false;//��������ͬʱΪʮ
                if(temporary[0]==10) num=numberChar[1]+num.substr(2,2);//ʮ������ʽ
                else if(temporary[1]==10) num=num.substr(0,2)+numberChar[0];//��ʮ����ʽ
            }
            else if( num.size()==6 ){
                if( temporary[0]==10 || temporary[1]!=10 || temporary[2]==10 ) return false;//��β����Ϊʮ���м�һ��ҪΪʮ
                num=num.substr(0,2)+num.substr(4,2);//ȥ���м�
            }
            return true;
        }
        void ToCharInThousand(string &cn,int value){
        	if(value<20){
        		if(value<=10) cn+=numberChar[value];
        		else cn+=numberChar[10]+numberChar[value-10];
        		return ;
			}
			bool prefix=0;
			if(value>=1000) cn+=numberChar[value/1000]+numberChar[1000],prefix=1;
			else if(prefix&&value%1000!=0) cn+=numberChar[0],prefix=0;
			value%=1000;
			if(value>=100) cn+=numberChar[value/100]+numberChar[100],prefix=1;
			else if(prefix&&value%100!=0) cn+=numberChar[0],prefix=0;
			value%=100;
			if(value>=10) cn+=numberChar[value/10]+numberChar[10];
			else if(prefix&&value%10!=0) cn+=numberChar[0];
			value%=10;
			if(value>=1) cn+=numberChar[value];
		}

    public:
        NumberRepository(){//��ʼ����ֵ
        	NumberCharPrepare();
        	CharNumberPrepare();
        }
        ~NumberRepository() {}

        bool ToChar(string &cn,long long int value){
        	if(value<0) cn="��",value=-value;
        	if(value>>31) return false;
        	else cn="";
        	int Ge=value%10000,Wan=value/10000%10000,Yi=value/10000/10000;
        	bool prefix=0;
        	if(Yi) ToCharInThousand(cn,Yi),cn+=numberChar[100000000],prefix=1;
        	if(Wan){
        		if(Wan<1000&&prefix) cn+=numberChar[0];
        		if(Wan>=10&&Wan<20&&prefix) cn+=numberChar[1];
        		ToCharInThousand(cn,Wan),cn+=numberChar[10000];
        		prefix=1;
			}
			else if(prefix) cn+=numberChar[0],prefix=0;
			if(Ge){
				if(Ge<1000&&prefix) cn+=numberChar[0];
				if(Ge>=10&&Ge<20&&prefix) cn+=numberChar[1];
				ToCharInThousand(cn,Ge);
			}
			return true;
        }

        bool ToNumber(int &value,string name){
            bool negative=0;
            if(name.substr(0,2)=="��") negative=1,name=name.substr(2);//���ж��Ƿ��Ǹ��� 
            if( !FormatChar(name) ) return false;//ʧ��
            int ten,base;
            FindChar( ten,name.substr(0,2) );
			FindChar( base,name.substr(2,2) );
			value=ten*10+base;
			if(negative) value=-value;
            return true;
        }
};
#endif
