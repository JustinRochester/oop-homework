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
#endif
