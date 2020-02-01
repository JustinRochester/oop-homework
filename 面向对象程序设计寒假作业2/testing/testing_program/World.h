#include "NumberRepository.h"
#include "VariableRepository.h"
#include<string>
#include<iostream>
using namespace std;

#ifndef WORLD
#define WORLD
class World{
    private:
        NumberRepository number;
        VariableRepository variable;
        bool IsConflict(string name){
            if( number.ToNumber(name)!=-1 ) return 1;
            return (name=="增加")||(name=="减少")||(name=="看看")||(name=="等于")||(name=="整数");
        }
        bool Input(string &sentence){
            return getline(cin,sentence);
        }
        int Update(string var,string order,string value){
            int data=number.ToNumber(value);
            if(data==-1) data=variable.VariableShow(value);//右值不是数字
            if(data==-1) return 8;//右值也不是变量，返回8（数字错误）
            if(order=="等于")
                return variable.VariableAssign(var,data)?0:6;//赋值成功则返回0，否则返回6（变量不存在），下同
            else if(order=="增加")
                return variable.VariableAdd(var,data)?0:6;
            else if(order=="减少")
                return variable.VariableMinus(var,data)?0:6;
            else
                return 9;//未知指令，返回9（语句无法识别）
        }
        int Update_string(string name,string sentence){
            if( sentence.find(" ")==string::npos ) return 9;//无空格，语句无法识别
            string order=sentence.substr(0, sentence.find(" ") );//增加、减少、赋值指令
            sentence=sentence.substr( sentence.find(" ")+1 );
            if( sentence.find(" ")!=string::npos ) return 9;//仍有空格，语句无法识别
            return Update(name,order,sentence);
        }
        int Apply(string name){
            if( variable.VariableApply(name) ) return 0;//申请成功，返回0
            else return 7;//申请失败，返回7（变量已申请）
        }
        int Apply_string(string sentence){
            if( sentence.find(" ")==string::npos )
                return IsConflict(sentence)?10:Apply(sentence);//没有空格，如不冲突，只申请变量
            string name=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if( sentence.find(" ")==string::npos ) return 9;//不含空格，返回9（语句无法识别）
            string order=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(order!="等于") return 9;//申请变量后不赋初值，无效，返回9（语句无法识别）
            if( IsConflict(name) ) return 10;//发生冲突，不能作为变量名，返回10（关键字冲突）
            if( number.ToNumber(sentence)==-1&&variable.VariableShow(sentence)==-1 )
                return 8;//sentence 不为值或变量的值，返回8（数字错误）
            if( Apply(name)!=0 ) return 7;//申请失败，返回7（变量已申请）
            return Update(name,order,sentence);
        }
        int Print(string name){
            int data=variable.VariableShow(name);
            if(data==-1) return 6;//输出的变量不存在，返回6（变量不存在）
            cout<<number.ToChar(data)<<endl;//存在，输出变量值的中文
            return 0;
        }
        int Print_string(string sentence){
            if( sentence.find(" ")!=string::npos ) return 9;//仍有空格，语句无法识别
            return Print(sentence);
        }
        void NotExist(){
            cout<<"变量不存在"<<endl;
        }
        void Applied(){
            cout<<"变量已申请"<<endl;
        }
        void NumberError(){
            cout<<"数字错误"<<endl;
        }
        void DontKnow(){
            cout<<"语句无法识别"<<endl;
        }
        void ConflictError(){
            cout<<"与关键字冲突"<<endl;
        }
        void Unknown(){
            cout<<"未知错误"<<endl;
        }
        int Understand(string sentence){
            if(sentence.find(" ")==string::npos) return 9;//不含空格，指令非法
            string head=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(head=="看看")
                return Print_string(sentence);
            else if(head=="整数")
                return Apply_string(sentence);
            else//其它类型的指令都有可能为变量开头
                return Update_string(head,sentence);
        }
    
    public:
        World() {}
        ~World() {}
        void Run(){
            string order;
            int ans;
            while( Input(order) ){
                if(order=="退出") break;
                ans=Understand(order);
                if(ans==0) continue;
                else if(ans==6) NotExist();
                else if(ans==7) Applied();
                else if(ans==8) NumberError();
                else if(ans==9) DontKnow();
                else if(ans==10) ConflictError();
                else Unknown();
            }
        }
};
#endif
