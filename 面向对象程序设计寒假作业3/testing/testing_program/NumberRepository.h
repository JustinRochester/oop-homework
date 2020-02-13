#include<string>
#include<vector>
using namespace std;

#ifndef NUMBERREPOSITORY
#define NUMBERREPOSITORY
class NumberRepository{
    private:
        vector<string> numberChar;
        int FindChar(string num){
            for(int i=0;i<=10;i++) if( numberChar[i]==num ) return i;//����Ѱ��
            return -1;//�Ҳ���
        }
        bool FormatChar(string &num){
            for(int i=0;i<=num.size()-2;i+=2) if( FindChar(num.substr(i,2))==-1 ) return false;//�ַ��Ϸ��Լ���
            if( num.size()==2 ) num=numberChar[0]+num;//һ���֣�ǰ���㣬ʮ��Ϊ������Ҳ������������
            else if( num.size()==4 ){
                if( FindChar(num.substr(0,2))==10 && FindChar(num.substr(2,2))==10 ) return false;//��������ͬʱΪʮ
                else if( FindChar(num.substr(0,2))==10 ) num=numberChar[1]+num.substr(2,2);//ʮ������ʽ
                else if( FindChar(num.substr(2,2))==10 ) num=num.substr(0,2)+numberChar[0];//��ʮ����ʽ
            }
            else if( num.size()==6 ){
                if( FindChar(num.substr(0,2))==10 || FindChar(num.substr(2,2))!=10 || FindChar(num.substr(4,2))==10 )
                    return false;//��β����Ϊʮ���м�һ��ҪΪʮ
                num=num.substr(0,2)+num.substr(4,2);//ȥ���м�
            }
            return true;
        }

    public:
        NumberRepository(){//��ʼ����ֵ
            numberChar.push_back("��");
            numberChar.push_back("һ");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("��");
            numberChar.push_back("ʮ");
        }
        ~NumberRepository() {}

        string ToChar(int number){
            if(number<0||number>99) return "���ֳ���";
            if(number<=10) return numberChar[number];
            if(number<20) return numberChar[10]+numberChar[number-10];//ʮ������ʽ
            if(number%10==0) return numberChar[number/10]+numberChar[10];//��ʮ����ʽ
            return numberChar[number/10]+numberChar[10]+numberChar[number%10];
        }

        int ToNumber(string sentence){
            if( !FormatChar(sentence) ) return -1;//ʧ��
            return FindChar( sentence.substr(0,2) )*10+FindChar( sentence.substr(2,2) );
        }
};
#endif
