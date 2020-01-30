#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

class VariableRepository{
    private:
        vector<int> variableValue;
        map<string,int> variableMap;
        int VariableFind(string name){
            if(variableMap.find(name)==variableMap.end()) return -1;//�Ҳ���
            return variableMap[name];
        }

    public:
        VariableRepository() {}
        ~VariableRepository() {}
        bool VariableApply(string name){
            if( VariableFind(name)!=-1 ) return false;//��������
            variableMap[name]=variableValue.size();//���ַ
            variableValue.push_back(0);//����ʼֵΪ0
            return true;
        }
        bool VariableAssign(string name,int value){
            if( VariableFind(name)==-1 ) return false;//���������ڣ���ͬ
            int &variable=variableValue[ VariableFind(name) ];//���ñ���
            variable=value;
            return true;
        }
        bool VariableAdd(string name,int value){
            if( VariableFind(name)==-1 ) return false;
            int &variable=variableValue[ VariableFind(name) ];
            variable+=value;
            return true;
        }
        bool VariableMinus(string name,int value){
            if( VariableFind(name)==-1 ) return false;
            int &variable=variableValue[ VariableFind(name) ];
            variable-=value;
            return true;
        }
        int VariableShow(string name){
            if( VariableFind(name)==-1 ) return -1;
            return variableValue[ VariableFind(name) ];
        }
};

class NumberRepository{
    private:
        vector<string> numberChar;
        int FindChar(string num){
            for(int i=0;i<=10;i++) if( numberChar[i]==num ) return i;//����Ѱ��
            return -1;//�Ҳ���
        }
        bool FormatChar(string &num){
            for(int i=0;i<=num.size()-2;i+=2) if( FindChar(num.substr(i,2))==-1 ) return false;//�ַ��Ϸ��Լ���
            if( num.size()==2 ) num=numberChar[0]+num;//һ���֣�ǰ���㣬ʮ��Ϊ������Ҳ������������
            else if( num.size()==4 ){
                if( FindChar(num.substr(0,2))==10 && FindChar(num.substr(2,2))==10 ) return false;//��������ͬʱΪʮ
                else if( FindChar(num.substr(0,2))==10 ) num=numberChar[1]+num.substr(2,2);//ʮ������ʽ
                else if( FindChar(num.substr(2,2))==10 ) num=num.substr(0,2)+numberChar[0];//��ʮ����ʽ
            }
            else if( num.size()==6 ){
                if( FindChar(num.substr(0,2))==10 || FindChar(num.substr(2,2))!=10 || FindChar(num.substr(4,2))==10 )
                    return false;//��β����Ϊʮ���м�һ��ҪΪʮ
                num=num.substr(0,2)+num.substr(4,2);//ȥ���м�
            }
            return true;
        }

    public:
        NumberRepository(){//��ʼ����ֵ
            numberChar.push_back("��");
            numberChar.push_back("һ");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("ʮ");
        }
        ~NumberRepository() {}

        string ToChar(int number){
            if(number<=10) return numberChar[number];
            if(number<20) return numberChar[10]+numberChar[number-10];//ʮ������ʽ
            if(number%10==0) return numberChar[number/10]+numberChar[10];//��ʮ����ʽ
            return numberChar[number/10]+numberChar[10]+numberChar[number%10];
        }

        int ToNumber(string sentence){
            if( !FormatChar(sentence) ) return -1;//ʧ��
            return FindChar( sentence.substr(0,2) )*10+FindChar( sentence.substr(2,2) );
        }
};

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
            if(sentence.find(" ")==string::npos) return 9;
            string head=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(head=="����")
                return Print_string(sentence);
            else if(head=="����")
                return Apply_string(sentence);
            else
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
}world;

int main(){
    world.Run();
    return 0;
}
