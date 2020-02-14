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
        bool VariableFind(vector<int>::iterator &v,string name){//v Ϊ vector<int> �͵ĵ�������һ������ 
            if(variableMap.find(name)==variableMap.end()) return false;//�Ҳ���
            v=variableValue.begin()+variableMap[name];
            return true;
        }

    public:
        VariableRepository() {}
        ~VariableRepository() {}
        bool VariableApply(string name){
        	vector<int>::iterator v;
            if( VariableFind(v,name) ) return false;//��������
            variableMap[name]=variableValue.size();//���ַ 
            variableValue.push_back(0);//����ʼֵΪ 0
            return true;
        }
        bool VariableDelete(string name){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;//���������ڣ���ͬ 
            variableValue.erase(v);
            variableMap.erase( variableMap.find(name) );
            return true;
        }
        bool VariableAssign(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v=value;
            return true;
        }
        bool VariableApplyAssign(string name,int value){
            if( !VariableApply(name) ) return false;
            VariableAssign(name,value);
            return true;
        }
        bool VariableAdd(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v+=value;
            return true;
        }
        bool VariableSubtract(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v-=value;
            return true;
        }
        bool VariableMultiply(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v*=value;
            return true;
        }
        bool VariableDivide(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v/=value;
            return true;
        }
        bool VariableModule(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v%=value;
            return true;
        }
        bool VariableRemainder(string name,int value){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            *v=(*v%value+value)%value;
            return true;
		}
        bool VariableShow(int &value,string name){
        	vector<int>::iterator v;
            if( !VariableFind(v,name) ) return false;
            value=*v;
            return true;
        }
};
#endif
