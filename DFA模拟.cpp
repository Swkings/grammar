#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#define max 100
using namespace std;
struct Arc{
    string start;
    string acc;   //Ϊ��ʱ��"&"��ʾ
    string last;  //���¸�״̬ʱ��"#"��ʾ
    int type;  //���start��״̬��1Ϊ��㣬2Ϊ��̬��0Ϊ����״̬
};
int pos(Arc *G, string pre, int N){
    for(int i=0; i<N; i++){
        if(G[i].start == pre){
            return i;
        }
    }
}
string tempstr;
string tstr;
int sumstr = 0;
bool res;
bool DFA(Arc *G, string test_str, string pre, int test_str_len, int N){
    int temp = max;
    int index;
    tempstr = test_str.substr(1 ,test_str.length()-1);
    tstr = test_str.substr(0,1);
    cout << "->" ;
    for(int i=0;i<N;i++){
        if(G[i].start == pre && G[i].acc == tstr){
            pre = G[i].last;
            temp = i;
            //cout << temp;
            cout << pre ;
            sumstr++;
            break;
        }else if(G[i].start == pre && G[i].acc == "&"){  //�մ���&��ʾ
            pre = G[i].last;
            tempstr = test_str; //�ڵ�Ϊ�մ������²���
            temp = i;
            cout << pre;
            break;
        }
    }
    if(temp == max){
        return false;
    }
    index = pos(G,pre,N);
    if(sumstr==test_str_len && G[index].type == 2){
        //cout <<  "hehe"  << endl;
        sumstr = 0;
        return true;
    }
    if((sumstr==test_str_len && G[index].type != 2) ||
       (sumstr!=test_str_len && G[index].last == "#" && G[index].type == 2) ){
        //cout << "lala" << endl;
        sumstr = 0;
        return false;
    }
    return DFA(G,tempstr,pre,test_str_len,N);
}

int main()
{
    int N;
    int i=0;
    string str;
    string test_str;
    bool flag = true;
    Arc *G = new Arc[max];

    //�ļ�����
    fstream infile;
    //DFAG.txtΪʵ�����⣬DFAG1.txtΪ����������a��������b
    infile.open("DFAG.txt");
    cout << "G[S]��" << endl;
    while(getline(infile,str)){
            cout << str << endl;
        G[i].start = str.substr(0,1);
        G[i].acc = str.substr(2,1);
        G[i].last = str.substr(4,1);
        G[i].type = str.substr(6,1)[0] - '0';
        i++;
    }
    N=i;

  /*
    //�ֶ�����
    for(i=0; i<max; i++){
        cin >> G[i].start;
        if(G[i].start == "#"){
            break;
        }else{
            cin >> G[i].acc >> G[i].last >> G[i].type;
        }
    }
    N = i;
 */
    for(int j=0;;j++){
        cout << "�����ַ���Ϊ��";
        cin >> test_str;
        cout << "·����";
        cout << G[0].start ;
        flag = DFA(G,test_str,G[0].start,test_str.length(),N);
        if(flag){
            cout << "\n\tyes!" << endl;
        }else{
            cout << "\n\tno!" << endl;
        }
    }
    system( "pause" );
    return 0;
}
