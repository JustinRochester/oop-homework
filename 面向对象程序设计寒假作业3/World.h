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
            if( name=="����" ) return 1;
            if( name=="����" ) return 1;
            if( name=="����" ) return 1;
            if( name=="����" ) return 1;
            if( name=="����" ) return 1;
            if( name=="ɾ��" ) return 1;
            return 0;
        }
        bool Input(string &sentence){
            return getline(cin,sentence);
        }
        void OrderBreakDown(string order){//��ָ��ո�ֽ�
            orderRegister.clear();//������ݴ��� 
            while(order.find(" ")!=string::npos){
                orderRegister.push_back( order.substr(0,order.find(" ")) );
                order=order.substr( order.find(" ")+1 );
            }
            if(order.size()!=0) orderRegister.push_back(order);
        }
        void Add(int &errorType,string name,int value){
            if( !valueRepository.VariableAdd(name,value) ) errorType=1;
        }
        void Reduce(int &errorType,string name,int value){
            if( !valueRepository.VariableReduce(name,value) ) errorType=1;
        }
        void Assign(int &errorType,string name,int value){
            if( !valueRepository.VariableAssign(name,value) ) errorType=1;
        }
        void Apply(int &errorType,string name){
            if( IsConflict(name) ) errorType=5;//��ؼ��ֳ�ͻ
            else if( !valueRepository.VariableApply(name) ) errorType=2;//����ʧ�ܣ�����2�����������룩
		}
        void ApplyAssign(int &errorType,string name,int value){
            errorType=0;
            if( IsConflict(name) ) errorType=5;//��ؼ��ֳ�ͻ
            else if( !valueRepository.VariableApplyAssign(name,value) ) errorType=2;//����ʧ�ܣ�����2�����������룩
        }
        void Print(int &errorType,string &value,string name){
            int data;
            if( !valueRepository.VariableShow(data,name) ) errorType=1;
            else if( !valueRepository.ToChar(value,data) ) errorType=6;//���ֳ���
        }
        void Delete(int &errorType,string name){
            if( !valueRepository.VariableDelete(name) ) errorType=1;
        }
        void Understand(int &errorType,string &answer,string sentence){
            errorType=0;//��ʼ���޴��� 
            answer="";//��ʼ�����Ϊ�� 
            OrderBreakDown(sentence);//�ֽ�ָ�� 
            
            if(orderRegister.size()<=1){//���ո��⣬ֻ��������һ�����ݣ�ָ��Ƿ�
                errorType=4;
                return ;
            }
            if(orderRegister.size()==4&&orderRegister[0]=="����"){
                if(orderRegister[2]!="����") errorType=4;
				//�ֽ�Ϊ�Ľڵģ�һ����Ϊ������ <����> ���� <ֵ>������ʽ
                int value;
                if( !valueRepository.ValueFind(value,orderRegister[3]) ) errorType=3;
                else ApplyAssign(errorType,orderRegister[1],value);
            }
            else if(orderRegister.size()==2){
                if(orderRegister[0]=="����") Print(errorType,answer,orderRegister[1]);
                else if(orderRegister[0]=="����") Apply(errorType,orderRegister[1]);
                else if(orderRegister[0]=="ɾ��") Delete(errorType,orderRegister[1]);
            }
            else if(orderRegister.size()==3){
                int value;
                if( !valueRepository.ValueFind(value,orderRegister[2]) ) errorType=3;
                else{
                    if(orderRegister[1]=="����") Add(errorType,orderRegister[0],value);
                    else if(orderRegister[1]=="����") Reduce(errorType,orderRegister[0],value);
                    else if(orderRegister[1]=="����") Assign(errorType,orderRegister[0],value);
                }
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
                if(order=="�˳�") break;
                Understand(errorType,answer,order);
                if(errorType!=0) errorRepository.ErrorOutput(answer,errorType);
                if(answer.size()) cout<<answer<<endl;
            }
        }
};
#endif
