#include<vector>
#include<string>
#include<map>
using namespace std;

#ifndef VARIABLEREPOSITORY
#define VARIABLEREPOSITORY
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
#endif
