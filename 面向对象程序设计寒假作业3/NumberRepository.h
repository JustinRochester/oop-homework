#include<string>
#include<vector>
using namespace std;

#ifndef NUMBERREPOSITORY
#define NUMBERREPOSITORY
class NumberRepository{
    private:
        vector<string> numberChar;
        bool FindChar(int &number,string num){
            for(int i=0;i<=10;i++) if( numberChar[i]==num ){
                number=i;
                return true;
            }//遍历寻找
            return false;//找不到
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

    public:
        NumberRepository(){//初始化赋值
            numberChar.push_back("零");
            numberChar.push_back("一");
            numberChar.push_back("二");
            numberChar.push_back("三");
            numberChar.push_back("四");
            numberChar.push_back("五");
            numberChar.push_back("六");
            numberChar.push_back("七");
            numberChar.push_back("八");
            numberChar.push_back("九");
            numberChar.push_back("十");
        }
        ~NumberRepository() {}

        bool ToChar(string &cn,int value){
            if(value<-99||value>99) return false;
            cn="";
            if(value<0) cn="负",value=-value;//先判定是否是负数 
            if(value<=10) cn+=numberChar[value];
            else if(value<20) cn+=numberChar[10]+numberChar[value-10];//十几的形式
            else if(value%10==0) cn+=numberChar[value/10]+numberChar[10];//几十的形式
            else cn+=numberChar[value/10]+numberChar[10]+numberChar[value%10];
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
