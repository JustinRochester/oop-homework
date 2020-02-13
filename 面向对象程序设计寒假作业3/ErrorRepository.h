#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
        void NotExist(string &output){
            output="����������";
        }
        void Applied(string &output){
            output="����������";
        }
        void NumberError(string &output){
            output="���ִ���";
        }
        void DontKnow(string &output){
            output="����޷�ʶ��";
        }
        void ConflictError(string &output){
            output="��ؼ��ֳ�ͻ";
        }
        void NumberLimitError(string &output){
            output="���ֳ���";
        }
        void Unknown(string &output){
            output="δ֪����";
        }
    
    public:
        ErrorRepository() {}
        ~ErrorRepository() {}
        void ErrorOutput(string &output,int errorType){
            switch(errorType){
                case 1:NotExist(output); break;
                case 2:Applied(output); break;
                case 3:NumberError(output); break;
                case 4:DontKnow(output); break;
                case 5:ConflictError(output); break;
                case 6:NumberLimitError(output); break;
                default:Unknown(output);
            }
        }
};
#endif
