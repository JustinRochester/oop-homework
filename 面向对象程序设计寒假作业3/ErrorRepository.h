#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
        void NotExist(string &output){
            output="变量不存在";
        }
        void Applied(string &output){
            output="变量已申请";
        }
        void NumberError(string &output){
            output="数字错误";
        }
        void DontKnow(string &output){
            output="语句无法识别";
        }
        void ConflictError(string &output){
            output="与关键字冲突";
        }
        void NumberLimitError(string &output){
            output="数字超限";
        }
        void Unknown(string &output){
            output="未知错误";
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
