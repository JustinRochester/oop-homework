#include<vector>
#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
        vector<string> keywordRepository,errorWordRepository;
        void KeywordRepositoryPrepare(){
            keywordRepository.push_back("����");
            keywordRepository.push_back("����");
            keywordRepository.push_back("����");
            keywordRepository.push_back("����");
            keywordRepository.push_back("ȡģ");
            keywordRepository.push_back("ȡ��");
            keywordRepository.push_back("����");
            keywordRepository.push_back("����");
            keywordRepository.push_back("����");
            keywordRepository.push_back("ɾ��");
		}
		void ErrorWordRepositoryPrepare(){
			errorWordRepository.push_back("");
			errorWordRepository.push_back("����������");
			errorWordRepository.push_back("����������");
			errorWordRepository.push_back("���ִ���");
			errorWordRepository.push_back("����޷�ʶ��");
			errorWordRepository.push_back("��ؼ��ֳ�ͻ");
			errorWordRepository.push_back("���ֳ���");
			errorWordRepository.push_back("�㲻��Ϊ����");
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
        	else output="δ֪����";
        }
        bool IsKeyword(string name){
            for(int i=0;i<keywordRepository.size();i++)
                if(keywordRepository[i]==name) return 1;
            return 0;
        }
};
#endif
