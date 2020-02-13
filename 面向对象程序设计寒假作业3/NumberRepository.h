#include<string>
#include<vector>
using namespace std;

#ifndef NUMBERREPOSITORY
#define NUMBERREPOSITORY
class NumberRepository{
    private:
        vector<string> numberChar;
        bool FindChar(int &number,string num){
            for(int i=0;i<=10;i++) if( numberChar[i]==num ){
                number=i;
                return true;
            }//����Ѱ��
            return false;//�Ҳ���
        }
        bool FormatChar(string &num){
            int temporary[3];
            for(int i=0;i<=num.size()-2;i+=2)
				if( !FindChar(temporary[i>>1],num.substr(i,2)) ) return false;//�ַ��Ϸ��Լ���
            if( num.size()==2 ) num=numberChar[0]+num;//һ���֣�ǰ���㣬ʮ��Ϊ������Ҳ������������
            else if( num.size()==4 ){
                if(temporary[0]==10&&temporary[1]==10) return false;//��������ͬʱΪʮ
                if(temporary[0]==10) num=numberChar[1]+num.substr(2,2);//ʮ������ʽ
                else if(temporary[1]==10) num=num.substr(0,2)+numberChar[0];//��ʮ����ʽ
            }
            else if( num.size()==6 ){
                if( temporary[0]==10 || temporary[1]!=10 || temporary[2]==10 ) return false;//��β����Ϊʮ���м�һ��ҪΪʮ
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

        bool ToChar(string &cn,int value){
            if(value<-99||value>99) return false;
            cn="";
            if(value<0) cn="��",value=-value;//���ж��Ƿ��Ǹ��� 
            if(value<=10) cn+=numberChar[value];
            else if(value<20) cn+=numberChar[10]+numberChar[value-10];//ʮ������ʽ
            else if(value%10==0) cn+=numberChar[value/10]+numberChar[10];//��ʮ����ʽ
            else cn+=numberChar[value/10]+numberChar[10]+numberChar[value%10];
            return true;
        }

        bool ToNumber(int &value,string name){
            bool negative=0;
            if(name.substr(0,2)=="��") negative=1,name=name.substr(2);//���ж��Ƿ��Ǹ��� 
            if( !FormatChar(name) ) return false;//ʧ��
            int ten,base;
            FindChar( ten,name.substr(0,2) );
			FindChar( base,name.substr(2,2) );
			value=ten*10+base;
			if(negative) value=-value;
            return true;
        }
};
#endif
