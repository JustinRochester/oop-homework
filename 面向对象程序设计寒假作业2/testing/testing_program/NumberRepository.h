#include<string>
#include<vector>
using namespace std;

#ifndef NUMBERREPOSITORY
#define NUMBERREPOSITORY
class NumberRepository{
    private:
        vector<string> numberChar;
        int FindChar(string num){
            for(int i=0;i<=10;i++) if( numberChar[i]==num ) return i;//遍历寻找
            return -1;//找不到
        }
        bool FormatChar(string &num){
            for(int i=0;i<=num.size()-2;i+=2) if( FindChar(num.substr(i,2))==-1 ) return false;//字符合法性检验
            if( num.size()==2 ) num=numberChar[0]+num;//一个字，前补零，十因为特殊性也可以这样处理
            else if( num.size()==4 ){
                if( FindChar(num.substr(0,2))==10 && FindChar(num.substr(2,2))==10 ) return false;//两个数不同时为十
                else if( FindChar(num.substr(0,2))==10 ) num=numberChar[1]+num.substr(2,2);//十几的形式
                else if( FindChar(num.substr(2,2))==10 ) num=num.substr(0,2)+numberChar[0];//几十的形式
            }
            else if( num.size()==6 ){
                if( FindChar(num.substr(0,2))==10 || FindChar(num.substr(2,2))!=10 || FindChar(num.substr(4,2))==10 )
                    return false;//首尾不能为十，中间一定要为十
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

        string ToChar(int number){
            if(number<0||number>99) return "数字超限";
            if(number<=10) return numberChar[number];
            if(number<20) return numberChar[10]+numberChar[number-10];//十几的形式
            if(number%10==0) return numberChar[number/10]+numberChar[10];//几十的形式
            return numberChar[number/10]+numberChar[10]+numberChar[number%10];
        }

        int ToNumber(string sentence){
            if( !FormatChar(sentence) ) return -1;//失败
            return FindChar( sentence.substr(0,2) )*10+FindChar( sentence.substr(2,2) );
        }
};
#endif
