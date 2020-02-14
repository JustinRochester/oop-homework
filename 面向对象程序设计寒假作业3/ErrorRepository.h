#include<vector>
#include<string>
using namespace std;

#ifndef ERRORREPOSITORY
#define ERRORREPOSITORY
class ErrorRepository{
    private:
    	vector<string> Keyword;
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
        void DevidedError(string &output){
        	output="�㲻��Ϊ����";
		}
        void Unknown(string &output){
            output="δ֪����";
        }
    
    public:
        ErrorRepository(){
        	Keyword.push_back("����");
        	Keyword.push_back("����");
        	Keyword.push_back("����");
        	Keyword.push_back("����");
        	Keyword.push_back("ȡģ");
        	Keyword.push_back("ȡ��");
        	Keyword.push_back("����");
        	Keyword.push_back("����");
        	Keyword.push_back("����");
        	Keyword.push_back("ɾ��");
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
