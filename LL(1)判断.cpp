#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define MAX 20

//c 42693 ��%��ʾ
using namespace std;
/*
    LL(1)�ķ�
1��������ݹ�
2������������
3��ͬһ����ʽ���������FIRST���Ͻ���Ϊ�գ���Ϊ����ȡFOLLOW
*/
struct Prod{
    string Lpro; //����ʽ��
    string Rpro[10]; //����ʽ�Ҳ�
    string First;
    string Follow;
    string Select;
};

//�и��ַ����������������Ҳ��ֿ�,���Ҽ������ʽ��������,����VT��VN����
int Split(Prod *G, string Producttion, string& VT, string& VN, int N){
    string left;
    string right;
    bool flag = false;
    int pos = Producttion.find("->",0);
    left = Producttion.substr(0,pos);
    right = Producttion.substr(pos+2);

    //ƴ��VT
    int len = right.length();
    for(int i=0; i<len; i++){
        if(!(right[i]>='A' && right[i]<='Z') && right[i] != '%'){
            if(VT.find(right[i],0) == string::npos){
               VT = VT.append(1,right[i]);
            }

        }
    }

    for(int i=0; i<MAX; i++){
        if(G[i].Lpro == left){
            for(int j=0; j<10; j++){
                if(G[i].Rpro[j].empty()){
                    G[i].Rpro[j] = right;
                    flag = true;
                    break;
                }
            }
        }else if(G[i].Lpro.empty()){
            G[i].Lpro = left;
            G[i].Rpro[0] = right;
            VN = VN.append(left);
            N++;
            flag = true;
            break;
        }

        if(flag){
            break;
        }
    }
    return N;
}
//�ж��Ƿ���ݹ飬������ʽ�����Ƿ���Ҳ���һλ��ͬ,���ж�ֱ����ݹ�ͼ����ݹ�
bool Rec(Prod* G,string Lp, string Rp[], int N, int ans, bool res){
    int temp = 0;
    while(!Rp[temp].empty()){
        if(Lp.find(Rp[temp][0],0) != string::npos){
            return false;
        }else if(Rp[temp][0]>='A' && Rp[temp][0]<='Z'){
            for(int i=0; i<N; i++){
                if(G[i].Lpro.find(Rp[temp][0],0) != string::npos){
                    //Lp = G[i].Lpro;
                    Rp = G[i].Rpro;
                    res = Rec(G, Lp, Rp, N, ans, res);   //ͬһ����ʽ��ͬ�Ҳ��ݹ�
                }
            }
        }
        temp++;
    }
    ans++;
   if(!res){
        return false;
    }else if(ans>=N && res){ //�������в���ʽ��δ�ҵ��ݹ�ʱ
        return true;
    }
    return res = Rec(G, G[ans].Lpro, G[ans].Rpro, N, ans, res);  //��ͬ����ʽ�ݹ�

}
//�ж��Ƿ���������
bool PubV(Prod* G,int N){

    for(int i=0; i<N; i++){

        char str[10];
        int j=0;
        int temp = 0;
        while(!G[i].Rpro[j].empty()){
            if(!(G[i].Rpro[j][0]>='A' && G[i].Rpro[j][0]<='Z')){
                str[temp] = G[i].Rpro[j][0];
                temp++;
            }
            j++;
        }
        if(temp < 2){
            continue;
        }else{
            for(int k=0; k<temp-1; k++){
                for(int t=k+1; t<temp; t++){
                    if(str[k] == str[t]){
                            cout << str[k] << str[t] << endl;
                        return false;
                    }
                }
            }
        }

    }
    return true;
}

void Fir(Prod* G,string VT,int N,int tempN){
    for(int i=0; i<N; i++){
        int j = 0;
        while(!G[i].Rpro[j].empty()){
            if(VT.find(G[i].Rpro[j][0],0) != string::npos  ){ // || G[i].Rpro[j][0] == '%' ���մ�����First��
                if(G[i].First.find(G[i].Rpro[j][0]) == string::npos){  //��First������δ�е��ս������
                    //G[i].First.append(1,G[i].Rpro[j][0]);
                    G[i].First = G[i].First + G[i].Rpro[j][0];
                    //cout << G[i].First  << endl;
                }
              /*  if(G[i].Rpro[j] == "��"){
                    G[i].First = G[i].First + G[i].Rpro[j];
                } */
            }else{
                for(int k=0; k<N; k++){
                    if(G[k].Lpro.find(G[i].Rpro[j][0]) != string::npos){
                        int len = G[k].First.length();
                        for(int t=0; t<len; t++){
                            if(G[i].First.find(G[k].First[t]) == string::npos){  //����һ���Ƴ��ĵ��ս������
                                G[i].First.append(1,G[k].First[t]);
                            }
                        }

                    }
                    int c = 0;
                    while(!G[k].Rpro[c].empty()){
                        if(G[k].Rpro[c]=="%"){
                            int len = G[i].Rpro[c].length();
                            if(len > 1){
                                if(VT.find(G[i].Rpro[c][1],0) != string::npos){
                                    if(G[i].First.find(G[i].Rpro[c][1]) == string::npos){
                                        //G[i].First.append(1,G[i].Rpro[j][0]);
                                        G[i].First = G[i].First + G[i].Rpro[c][1];
                                        //cout << G[i].First  << endl;
                                    }
                                }else if(G[i].Rpro[c][1]>='A' && G[i].Rpro[c][1]<='Z'){
                                    for(int l=0; l<N; l++){
                                        if(G[l].Lpro.find(G[i].Rpro[c][1],0) != string::npos){
                                                int len = G[l].First.length();
                                                for(int t=0; t<len; t++){
                                                    if(G[i].First.find(G[l].First[t]) == string::npos){
                                                        G[i].First.append(1,G[l].First[t]);
                                                    }
                                                }
                                        }
                                    }
                                }
                            }
                        }
                        c++;
                    }

                }
            }
            j++;
        }
    }
    tempN--;
    if(tempN < 0){
        return;
    }

   Fir(G, VT, N, tempN);  //�ݹ�n��
}

void Fol(Prod* G,string VT,int N, int tempN){

    //�����ʽ���пմ���Follow�� Q -> ��
    //�������1��T -> ������Qa����   ,T -> ������QA��������  T -> ����Q ,
    for(int i=0; i<N; i++){

                for(int k=0; k<N; k++){

                    int h = 0;
                    while(!G[k].Rpro[h].empty()){
                        //cout <<  'G' << endl;
                        int pos = G[k].Rpro[h].find(G[i].Lpro);
                        if(pos != string::npos){
                            //cout << k << '|' << pos << '|' << G[k].Rpro[h].length() - 1 - pos << endl;

                            if(G[k].Rpro[h].length() - 1 - pos > 0 ){
                                    //cout <<  VT << '|' << G[k].Rpro[h][pos+1]<< endl;
                                if(VT.find(G[k].Rpro[h][pos+1]) != string::npos){  //1��T -> ������Qa������
                                    //cout <<  'G' << endl;
                                    if((G[i].Follow.find(G[k].Rpro[h][pos+1])) == string::npos){
                                        //cout <<  'G' << endl;
                                       //G[i].Follow.append(1,G[k].Rpro[h][pos+1]);
                                       G[i].Follow = G[i].Follow + G[k].Rpro[h][pos+1];
                                    }
                                }else if(G[k].Rpro[h][pos+1]>='A' && G[k].Rpro[h][pos+1]<='Z'){  //2��T -> ������QA������
                                        bool f = false;
                                        for(int d=0; d<N; d++){
                                            if(G[d].Lpro.find(G[k].Rpro[h][pos+1]) != string::npos){

                                                int v=0;
                                                while(!G[d].Rpro[v].empty()){
                                                    if(G[d].Rpro[v] == "%"){
                                                        f = true;
                                                        break;
                                                    }
                                                    v++;
                                                }


                                                int len = G[d].First.length();
                                                //cout << len << '|' << G[d].First << endl;
                                                for(int c=0; c<len; c++){
                                                    if(G[i].Follow.find(G[d].First[c]) == string::npos){
                                                       // G[i].Follow.append(1,G[d].First[c]);
                                                       G[i].Follow = G[i].Follow + G[d].First[c];
                                                    }
                                                }

                                            }
                                        }

                                        if(f){
                                            int len = G[k].Follow.length();
                                            for(int c=0; c<len; c++){
                                                if(G[i].Follow.find(G[k].Follow[c]) == string::npos){
                                                    G[i].Follow = G[i].Follow + G[k].Follow[c];
                                                }

                                            }
                                        }
                                   }

                            }else if(G[k].Rpro[h].length() - 1 - pos == 0){   //3�� T -> ����Q
                                int len = G[k].Follow.length();
                                //cout << len << '|' << G[k].Follow << endl;
                                for(int c=0; c<len; c++){
                                    if(G[i].Follow.find(G[k].Follow[c]) == string::npos){
                                        //G[i].Follow.append(1,G[k].Follow[c]);
                                       // cout << G[i].Follow << '|' << G[k].Follow[c] << endl;
                                        G[i].Follow = G[i].Follow + G[k].Follow[c];
                                    }

                                }

                            }
                        }
                        h++;
                    }

                }

    }
    tempN--;
    if(tempN < 0){
        return;
    }
    //cout << tempN + 100<< endl;
    Fol(G, VT, N, tempN);
}

int main()
{
    Prod *G = new Prod[MAX];
    fstream infile;
    string str;
    string VT = "";
    string VN = "";
    bool recf,pubf;
    int N = 0;
    int ans = 0;
    //G[S]1.txtΪʵ�����⣬G[S]2.txt�������ӣ�G[S]3.txt�����ݹ飬G[S]4.txt��G[S]5.txtΪLL��1���ķ�
    infile.open("G[S]4.txt");
    while(getline(infile,str)){
        cout << str << endl;
        N = Split(G, str, VT, VN, N);
    }
    cout << endl << "VN��" << VN << "\t" << "VT��" << VT << endl;
    recf = Rec(G,G[0].Lpro,G[0].Rpro,N,ans,true);
    pubf = PubV(G, N);
    if(recf && pubf){
        int tempN = N;
        Fir(G, VT, N, tempN);
        //��#����S����ʼ��Follow
        G[0].Follow = "#";
        int tempNN = N;
        Fol(G, VT, N, tempNN);
        cout << endl << "VN" << '\t' << "VT" << '\t' << "First" << '\t' << "Follow" <<endl;
        for(int i=0; i<N; i++){
            string s = "";
            int j=0;
            while(!G[i].Rpro[j].empty()){
                if(j!=0){
                    s = s + "|";
                }
                s = s + G[i].Rpro[j];
                j++;
            }
            cout  << G[i].Lpro << '\t' << s << '\t' << G[i].First << '\t' << G[i].Follow <<endl;
        }
        cout << endl;

        //����First �� Follow�ж��Ƿ���LL��1���ķ�
        bool judge = true;
        int z=0;
        for (int i=0; i<N; i++){
            z++;
            int j=0;
            int temp = 0;
            string str[5];
            while(!G[i].Rpro[j].empty()){
                if(VT.find(G[i].Rpro[j][0],0) != string::npos){
                    str[temp] = G[i].Rpro[j][0];
                    temp++;
                }else if(G[i].Rpro[j][0]>='A' && G[i].Rpro[j][0]<='Z'){
                    for(int k=0; k<N; k++){
                        if(G[k].Lpro.find(G[i].Rpro[j][0],0) != string::npos){
                            str[temp] = G[k].First;
                            temp++;
                        }
                    }
                }else {
                    str[temp] = G[i].Follow;
                    temp++;
                }
                j++;
            }
            if(temp<2){
                continue;
            }else{
                for(int h=0; h<temp-1; h++){
                    int len = str[h].length();
                    for(int g=h+1; g<temp; g++){
                        for(int c=0; c<len; c++){
                            if(str[g].find(str[h][c],0) != string::npos && str[g] != "%"){
                                cout << "First(" << G[i].Rpro[h] << ") = {" << str[h] << "}" << endl;
                                cout << "First(" << G[i].Rpro[g] << ") = {" << str[g] << "}" << endl;
                                cout << "G[s]����LL(1)���ķ���First��Follow�н���" << endl;
                                judge = false;
                                break;
                            }
                        }
                        if(!judge){
                            break;
                        }
                    }
                    if(!judge){
                        break;
                    }
                }
            }

            if(!judge){
                break;
            }

        }

         if(z>=N){
                cout << "G[s]��LL(1)���ķ�" << endl;
        }

    }else{
        cout << '\t' << "VN" << '\t' << "VT" << '\t' << "First" << '\t' << "Follow" <<endl;
        for(int i=0; i<N; i++){
            string s = "";
            int j=0;
            while(!G[i].Rpro[j].empty()){
                if(j!=0){
                    s = s + "|";
                }
                s = s + G[i].Rpro[j];
                j++;
            }
            cout << '\t' << G[i].Lpro << '\t' << s << '\t' << G[i].First << '\t' << G[i].Follow <<endl;
        }
        cout << "G[s]����LL(1)���ķ���������ݹ�������ӣ�" << endl;
    }

    return 0;
}
