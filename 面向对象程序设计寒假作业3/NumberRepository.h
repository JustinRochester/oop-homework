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
        	numberChar[0]="零";
        	numberChar[1]="一";
        	numberChar[2]="二";
        	numberChar[3]="三";
        	numberChar[4]="四";
        	numberChar[5]="五";
        	numberChar[6]="六";
        	numberChar[7]="七";
        	numberChar[8]="八";
        	numberChar[9]="九";
        	numberChar[10]="十";
        	numberChar[100]="百";
        	numberChar[1000]="千";
        	numberChar[10000]="万";
        	numberChar[100000000]="亿";
		}
		void CharNumberPrepare(){
			charNumber["零"]=0;
			charNumber["一"]=1;
			charNumber["二"]=2;
			charNumber["三"]=3;
			charNumber["四"]=4;
			charNumber["五"]=5;
			charNumber["六"]=6;
			charNumber["七"]=7;
			charNumber["八"]=8;
			charNumber["九"]=9;
			charNumber["十"]=10;
			charNumber["百"]=100;
			charNumber["千"]=1000;
			charNumber["万"]=10000;
			charNumber["亿"]=100000000;
		}
        bool FindChar(int &number,string num){
        	if( charNumber.find(num)==charNumber.end() ) return 0;//找不到 
        	number=charNumber[num];
        	return true;
        }
        bool FormatChar(string &num){
            int temporary[3];
            for(int i=0;i<=num.size()-2;i+=2)
				if( !FindChar(temporary[i>>1],num.substr(i,2)) ) return false;//字符合法性检验
            if( num.size()==2 ) num=numberChar[0]+num;//一个字，前补零，十因为特殊性也可以这样处理
            else if( num.size()==4 ){
                if(temporary[0]==10&&temporary[1]==10) return false;//两个数不同时为十
                if(temporary[0]==10) num=numberChar[1]+num.substr(2,2);//十几的形式
                else if(temporary[1]==10) num=num.substr(0,2)+numberChar[0];//几十的形式
            }
            else if( num.size()==6 ){
                if( temporary[0]==10 || temporary[1]!=10 || temporary[2]==10 ) return false;//首尾不能为十，中间一定要为十
                num=num.substr(0,2)+num.substr(4,2);//去掉中间
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
        NumberRepository(){//初始化赋值
        	NumberCharPrepare();
        	CharNumberPrepare();
        }
        ~NumberRepository() {}

        bool ToChar(string &cn,long long int value){
        	if(value<0) cn="负",value=-value;
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
            if(name.substr(0,2)=="负") negative=1,name=name.substr(2);//先判定是否是负数 
            if( !FormatChar(name) ) return false;//失败
            int ten,base;
            FindChar( ten,name.substr(0,2) );
			FindChar( base,name.substr(2,2) );
			value=ten*10+base;
			if(negative) value=-value;
            return true;
        }
};
#endif
