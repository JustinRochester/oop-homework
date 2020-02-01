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
            return (name=="����")||(name=="����")||(name=="����")||(name=="����")||(name=="����");
        }
        bool Input(string &sentence){
            return getline(cin,sentence);
        }
        int Update(string var,string order,string value){
            int data=number.ToNumber(value);
            if(data==-1) data=variable.VariableShow(value);//��ֵ��������
            if(data==-1) return 8;//��ֵҲ���Ǳ���������8�����ִ���
            if(order=="����")
                return variable.VariableAssign(var,data)?0:6;//��ֵ�ɹ��򷵻�0�����򷵻�6�����������ڣ�����ͬ
            else if(order=="����")
                return variable.VariableAdd(var,data)?0:6;
            else if(order=="����")
                return variable.VariableMinus(var,data)?0:6;
            else
                return 9;//δָ֪�����9������޷�ʶ��
        }
        int Update_string(string name,string sentence){
            if( sentence.find(" ")==string::npos ) return 9;//�޿ո�����޷�ʶ��
            string order=sentence.substr(0, sentence.find(" ") );//���ӡ����١���ֵָ��
            sentence=sentence.substr( sentence.find(" ")+1 );
            if( sentence.find(" ")!=string::npos ) return 9;//���пո�����޷�ʶ��
            return Update(name,order,sentence);
        }
        int Apply(string name){
            if( variable.VariableApply(name) ) return 0;//����ɹ�������0
            else return 7;//����ʧ�ܣ�����7�����������룩
        }
        int Apply_string(string sentence){
            if( sentence.find(" ")==string::npos )
                return IsConflict(sentence)?10:Apply(sentence);//û�пո��粻��ͻ��ֻ�������
            string name=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if( sentence.find(" ")==string::npos ) return 9;//�����ո񣬷���9������޷�ʶ��
            string order=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(order!="����") return 9;//��������󲻸���ֵ����Ч������9������޷�ʶ��
            if( IsConflict(name) ) return 10;//������ͻ��������Ϊ������������10���ؼ��ֳ�ͻ��
            if( number.ToNumber(sentence)==-1&&variable.VariableShow(sentence)==-1 )
                return 8;//sentence ��Ϊֵ�������ֵ������8�����ִ���
            if( Apply(name)!=0 ) return 7;//����ʧ�ܣ�����7�����������룩
            return Update(name,order,sentence);
        }
        int Print(string name){
            int data=variable.VariableShow(name);
            if(data==-1) return 6;//����ı��������ڣ�����6�����������ڣ�
            cout<<number.ToChar(data)<<endl;//���ڣ��������ֵ������
            return 0;
        }
        int Print_string(string sentence){
            if( sentence.find(" ")!=string::npos ) return 9;//���пո�����޷�ʶ��
            return Print(sentence);
        }
        void NotExist(){
            cout<<"����������"<<endl;
        }
        void Applied(){
            cout<<"����������"<<endl;
        }
        void NumberError(){
            cout<<"���ִ���"<<endl;
        }
        void DontKnow(){
            cout<<"����޷�ʶ��"<<endl;
        }
        void ConflictError(){
            cout<<"��ؼ��ֳ�ͻ"<<endl;
        }
        void Unknown(){
            cout<<"δ֪����"<<endl;
        }
        int Understand(string sentence){
            if(sentence.find(" ")==string::npos) return 9;//�����ո�ָ��Ƿ�
            string head=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(head=="����")
                return Print_string(sentence);
            else if(head=="����")
                return Apply_string(sentence);
            else//�������͵�ָ��п���Ϊ������ͷ
                return Update_string(head,sentence);
        }
    
    public:
        World() {}
        ~World() {}
        void Run(){
            string order;
            int ans;
            while( Input(order) ){
                if(order=="�˳�") break;
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
