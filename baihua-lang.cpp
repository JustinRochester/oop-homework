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
            if(variableMap.find(name)==variableMap.end()) return -1;//找不到
            return variableMap[name];
        }

    public:
        VariableRepository() {}
        ~VariableRepository() {}
        bool VariableApply(string name){
            if( VariableFind(name)!=-1 ) return false;//变量存在
            variableMap[name]=variableValue.size();//存地址
            variableValue.push_back(0);//赋初始值为0
            return true;
        }
        bool VariableAssign(string name,int value){
            if( VariableFind(name)==-1 ) return false;//变量不存在，下同
            int &variable=variableValue[ VariableFind(name) ];//引用变量
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
            if(sentence.find(" ")==string::npos) return 9;
            string head=sentence.substr(0, sentence.find(" ") );
            sentence=sentence.substr( sentence.find(" ")+1 );
            if(head=="看看")
                return Print_string(sentence);
            else if(head=="整数")
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
}world;

int main(){
    world.Run();
    return 0;
}
