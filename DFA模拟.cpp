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
    string acc;   //为空时用"&"表示
    string last;  //无下个状态时用"#"表示
    int type;  //标记start的状态，1为起点，2为终态，0为过度状态
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
        }else if(G[i].start == pre && G[i].acc == "&"){  //空串用&表示
            pre = G[i].last;
            tempstr = test_str; //节点为空串，重新测试
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

    //文件读入
    fstream infile;
    //DFAG.txt为实验例题，DFAG1.txt为输入奇数个a和奇数个b
    infile.open("DFAG.txt");
    cout << "G[S]：" << endl;
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
    //手动输入
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
        cout << "测试字符串为：";
        cin >> test_str;
        cout << "路径：";
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
