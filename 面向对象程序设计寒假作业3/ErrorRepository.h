#include<vector>
#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
    	vector<string> Keyword;
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
        void DevidedError(string &output){
        	output="零不得为除数";
		}
        void Unknown(string &output){
            output="未知错误";
        }
    
    public:
        ErrorRepository(){
        	Keyword.push_back("增加");
        	Keyword.push_back("减少");
        	Keyword.push_back("乘以");
        	Keyword.push_back("除以");
        	Keyword.push_back("取模");
        	Keyword.push_back("取余");
        	Keyword.push_back("看看");
        	Keyword.push_back("等于");
        	Keyword.push_back("整数");
        	Keyword.push_back("删除");
		}
        ~ErrorRepository() {}
        void ErrorOutput(string &output,int errorType){
            switch(errorType){
                case 1:NotExist(output); break;
                case 2:Applied(output); break;
                case 3:NumberError(output); break;
                case 4:DontKnow(output); break;
                case 5:ConflictError(output); break;
                case 6:NumberLimitError(output); break;
                case 7:DevidedError(output); break;
                default:Unknown(output);
            }
        }
        bool IsKeyword(string name){
        	for(int i=0;i<Keyword.size();i++)
        		if(Keyword[i]==name) return 1;
        	return 0;
		}
};
#endif
