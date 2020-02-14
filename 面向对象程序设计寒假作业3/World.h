#include "ValueRepository.h"
#include "ErrorRepository.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;

#ifndef WORLD
#define WORLD
class World{
    private:
        ValueRepository valueRepository;
        ErrorRepository errorRepository;
        vector<string> orderRegister;
        bool IsConflict(string name){
            int value;
            if( valueRepository.ToNumber(value,name) ) return 1;
            return errorRepository.IsKeyword(name);
        }
        bool Input(string &sentence){
            return getline(cin,sentence);
        }
        void OrderBreakDown(string order){//将指令按空格分解
            orderRegister.clear();//先清空暂存器 
            while(order.find(" ")!=string::npos){
                orderRegister.push_back( order.substr(0,order.find(" ")) );
                order=order.substr( order.find(" ")+1 );
            }
            if(order.size()!=0) orderRegister.push_back(order);
        }
        void Add(int &errorType,string name,int value){
            if( !valueRepository.VariableAdd(name,value) ) errorType=1;
        }
        void Subtract(int &errorType,string name,int value){
            if( !valueRepository.VariableSubtract(name,value) ) errorType=1;
        }
        void Multiply(int &errorType,string name,int value){
            if( !valueRepository.VariableMultiply(name,value) ) errorType=1;
        }
        void Devide(int &errorType,string name,int value){
        	if(value==0) errorType=7;//0 不能作为除数，下同 
            else if( !valueRepository.VariableDevide(name,value) ) errorType=1;
        }
        void Module(int &errorType,string name,int value){
        	if(value==0) errorType=7;
            else if( !valueRepository.VariableModule(name,value) ) errorType=1;
        }
        void Remainder(int &errorType,string name,int value){
        	if(value==0) errorType=7;
            else if( !valueRepository.VariableRemainder(name,value) ) errorType=1;
        }
        void Assign(int &errorType,string name,int value){
            if( !valueRepository.VariableAssign(name,value) ) errorType=1;
        }
        void Apply(int &errorType,string name){
            if( IsConflict(name) ) errorType=5;//与关键字冲突
            else if( !valueRepository.VariableApply(name) ) errorType=2;//申请失败，返回2（变量已申请）
		}
        void ApplyAssign(int &errorType,string name,int value){
            errorType=0;
            if( IsConflict(name) ) errorType=5;//与关键字冲突
            else if( !valueRepository.VariableApplyAssign(name,value) ) errorType=2;//申请失败，返回2（变量已申请）
        }
        void Print(int &errorType,string &value,string name){
            int data;
            if( !valueRepository.VariableShow(data,name) ) errorType=1;
            else if( !valueRepository.ToChar(value,data) ) errorType=6;//数字超限
        }
        void Delete(int &errorType,string name){
            if( !valueRepository.VariableDelete(name) ) errorType=1;
        }
        void Update(int &errorType,string name,int value){//变量值发生变化的操作 
        	if(orderRegister[1]=="增加") Add(errorType,name,value);
        	if(orderRegister[1]=="减少") Subtract(errorType,name,value);
        	if(orderRegister[1]=="乘以") Multiply(errorType,name,value);
        	if(orderRegister[1]=="除以") Devide(errorType,name,value);
        	if(orderRegister[1]=="取模") Module(errorType,name,value);
        	if(orderRegister[1]=="取余") Remainder(errorType,name,value);
		}
        void Understand(int &errorType,string &answer,string sentence){
            errorType=0;//初始化无错误 
            answer="";//初始化输出为空 
            OrderBreakDown(sentence);//分解指令 
            
            if(orderRegister.size()<=1){//除空格外，只含不超过一个内容，指令非法
                errorType=4;
                return ;
            }
            if(orderRegister.size()==4&&orderRegister[0]=="整数"){
                if(orderRegister[2]!="等于") errorType=4;
				//分解为四节的，一定需为“整数 <变量> 等于 <值>”的形式
                int value;
                if( !valueRepository.ValueFind(value,orderRegister[3]) ) errorType=3;
                else ApplyAssign(errorType,orderRegister[1],value);
            }
            else if(orderRegister.size()==2){
                if(orderRegister[0]=="看看") Print(errorType,answer,orderRegister[1]);
                if(orderRegister[0]=="整数") Apply(errorType,orderRegister[1]);
                if(orderRegister[0]=="删除") Delete(errorType,orderRegister[1]);
            }
            else if(orderRegister.size()==3){
                int value;
                if( !valueRepository.ValueFind(value,orderRegister[2]) ) errorType=3;
                else Update(errorType,orderRegister[0],value);
            }
            else errorType=4;
        }
    
    public:
        World() {}
        ~World() {}
        void Run(){
            string order,answer;
            int errorType;
            while( Input(order) ){
                if(order=="退出") break;
                Understand(errorType,answer,order);
                if(errorType!=0) errorRepository.ErrorOutput(answer,errorType);
                if(answer.size()) cout<<answer<<endl;
            }
        }
};
#endif
