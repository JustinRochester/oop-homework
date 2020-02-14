#include "VariableRepository.h"
#include "NumberRepository.h"

#ifndef VALUEREPOSITORY
#define VALUEREPOSITORY
class ValueRepository{
    private:
        VariableRepository variableRepository;
        NumberRepository numberRepository;
    
    public:
        ValueRepository() {}
        ~ValueRepository() {}
        bool ToChar(string &cn,int value){
			return numberRepository.ToChar(cn,value);
		}
        bool ToNumber(int &value,string name){
			return numberRepository.ToNumber(value,name);
		}
        bool VariableApply(string name){
			return variableRepository.VariableApply(name);
		}
        bool VariableDelete(string name){
			return variableRepository.VariableDelete(name);
		}
        bool VariableAssign(string name,int value){
			return variableRepository.VariableAssign(name,value);
		}
        bool VariableApplyAssign(string name,int value){
			return variableRepository.VariableApplyAssign(name,value);
		}
        bool VariableAdd(string name,int value){
			return variableRepository.VariableAdd(name,value);
		}
        bool VariableSubtract(string name,int value){
			return variableRepository.VariableSubtract(name,value);
		}
		bool VariableMultiply(string name,int value){
			return variableRepository.VariableMultiply(name,value);
		}
		bool VariableDevide(string name,int value){
			return variableRepository.VariableDivide(name,value);
		}
		bool VariableModule(string name,int value){
			return variableRepository.VariableModule(name,value);
		}
        bool VariableShow(int &value,string name){
			return variableRepository.VariableShow(value,name);
		}
        bool ValueFind(int &value,string name){
            if( numberRepository.ToNumber(value,name) ) return true;
            return variableRepository.VariableShow(value,name);
        }
};
#endif
