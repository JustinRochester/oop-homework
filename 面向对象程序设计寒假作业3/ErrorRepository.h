#include<vector>
#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
        vector<string> keywordRepository,errorWordRepository;
        void KeywordRepositoryPrepare(){
            keywordRepository.push_back("增加");
            keywordRepository.push_back("减少");
            keywordRepository.push_back("乘以");
            keywordRepository.push_back("除以");
            keywordRepository.push_back("取模");
            keywordRepository.push_back("取余");
            keywordRepository.push_back("看看");
            keywordRepository.push_back("等于");
            keywordRepository.push_back("整数");
            keywordRepository.push_back("删除");
		}
		void ErrorWordRepositoryPrepare(){
			errorWordRepository.push_back("");
			errorWordRepository.push_back("变量不存在");
			errorWordRepository.push_back("变量已申请");
			errorWordRepository.push_back("数字错误");
			errorWordRepository.push_back("语句无法识别");
			errorWordRepository.push_back("与关键字冲突");
			errorWordRepository.push_back("数字超限");
			errorWordRepository.push_back("零不得为除数");
		}
    
    public:
        ErrorRepository(){
        	KeywordRepositoryPrepare();
        	ErrorWordRepositoryPrepare();
        }
        ~ErrorRepository() {}
        void ErrorOutput(string &output,int errorType){
        	if(errorType>=0&&errorType<errorWordRepository.size())
        		output=errorWordRepository[errorType];
        	else output="未知错误";
        }
        bool IsKeyword(string name){
            for(int i=0;i<keywordRepository.size();i++)
                if(keywordRepository[i]==name) return 1;
            return 0;
        }
};
#endif
