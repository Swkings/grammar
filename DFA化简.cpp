#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
#define max 100


struct edge {
	string	start;  /* �ߵĳ�ʼ��� */
	string	change; /* �ߵ����� */
	string	last;   /* �ߵ��յ� */
};
int	N;              /* NFA�ı��� */
string	part[max];      /* �ָ��Ӽ� */


/* ״̬����I��a��ת�� , �ж�set������Ԫ�ؾ�������ch�ܵ���ı߼���*/
string move( string set, char ch, edge *b )
{
	int	i, j;
	string	s = "";
	for ( i = 0; i < set.length(); i++ )
	{
		for ( j = 0; j < N; j++ )
		{
			if ( b[j].start[0] == set[i] && b[j].change[0] == ch )
				s = s + b[j].last;
		}
	}
	if ( s == "" )
		return("&");
	else return(s);
}


/* �ж��Ӵ��Ƿ������ĳһ���� */
int boolisexist( string s, string d )
{
	if ( d != "" && 0 <= d.find( s ) && d.find( s ) <= d.length() - 1 )
	{
		return(1);
	}else  {
		return(0);
	}
}


/* �ָ��Ӽ�������DFA����С�� */

int divide( edge *b, string change )
{
	int	x, m, flag = 2, flag0, i, j;
	string	ss, part0[max];
	flag0 = flag;
	for ( x = 0; x < change.length(); x++ )
	{
		for ( m = 0; m < flag0; m++ )
		{
			for ( i = 0; i < part[m].length(); i++ ) //�������ֵļ��ϣ��ж�ÿһ�����Ͼ��� change �� �ܵ���� ����
			{
				ss = move( part[m].substr( i, 1 ), change[x], b );
				for ( j = 0; j < flag; j++ )
				{
					if ( boolisexist( ss, part[j] ) )   //�ж�ͬһ������Ԫ�� ���� ��ͬ�� change �� �Ƿ��� ͬһ���ϡ����������Ԫ�����»���
						part0[j] = part0[j] + part[m].substr( i, 1 );
					if ( ss == "&" )
					{
						part0[flag] = part0[flag] + part[m].substr( i, 1 );
						break;
					}
				}
			}
			for ( j = 0; j <= flag; j++ )
			{
				if ( part0[j] != "" && part0[j] != part[m] )
				{
					part[flag++]	= part0[j];
					part0[j]	= "";
					part[m]		= "";
				}else part0[j] = "";
			}
		}
		flag0 = flag;
	}
	return(flag);
}


int main()
{
	int	i, j, flag, x;
	string	Change; /* ������� */
	string	ss,str, temp[4];
	edge	*b = new edge[max];
	int f = 0;
	int g = 0;
	bool point = false;
///*
    printf("%s","��ȡ�ļ���>>>>>>>>>>>>>>>>>>>>>>>>>>>>��ȡ��ɣ�\n");
//��ȡ�ļ���ʽ
    // �Զ�ģʽ���ļ�
   ifstream infile;

   infile.open("dfa.txt");
   while(getline(infile,str))   //���ж�ȡ,�������з�����
    {
        //infile.getline(str);
       // cout<<str<<endl;
        if(str == "#"){
            point = true;
            continue;
        }
        if(point){
            temp[f] = str;
            f++;
        }else{
                b[g].start = str.substr(0,1);
                b[g].change = str.substr(2,1);
                b[g].last = str.substr(4,1);
                g++;
            }

        }
        part[1] = temp[0];
        part[0] = temp[1];
        Change = temp[2];
        N = g;

   // �رմ򿪵��ļ�
   infile.close();


   //������ȡ��Ϣ
   cout << "��ȡ�ıߵ���ϢΪ��" << endl;
   cout << "���" << "\t" << "����" << "\t" << "�յ�" << endl;
   for(int k=0;k<N;k++){
        cout << b[k].start << "\t" << b[k].change << "\t" << b[k].last << endl;
   }
   	printf( "��DFA����̬����Ϊ��" );
	cout << part[1] << endl;
	printf( "��DFA�ķ���̬����Ϊ��" );
	cout << part[0] << endl;
	printf( "��DFA״̬�е�������ż����ϵ�����Ϊ:" );
	cout << Change << endl;
//*/

//�ֶ�����
/*
	printf( "������DFA������Ϣ���������������&��ʾ���յ㣬������#������" );
	for ( i = 0; i < max; i++ )
	{
		cin >> b[i].start;
		if ( b[i].start == "#" )
			break;
		else
			cin >> b[i].change >> b[i].last;
	}
	N = i;
	printf( "�������DFA����̬���ϣ�" );
	cin >> part[1];
	printf( "�������DFA�ķ���̬���ϣ�" );
	cin >> part[0];
	printf( "�������DFA״̬�е�������ż����ϵ�����:" );
	cin >> Change;
*/

	flag = divide( b, Change );
	printf( "��DFA��С�����ֵ��Ӽ����£�\n" );
	for ( i = 0; i < flag; i++ )
	{
		if ( part[i] != "" )
			cout << part[i] << endl;
	}
	printf( "��״̬A,B,C�������ȴ����Ӽ���" );
	for ( i = 0; i < flag; i++ )
	{
		if ( part[i] != "" )
			cout << "{" << part[i] << "},";
	}
	printf( "��DFA��С����ĸ�����Ϣ���£�\n" );
	char	letters[max];
	char	letter = 'A';
	for ( i = 0; i < flag; i++ )
	{
		if ( part[i] != "" )
		{
			letters[i] = letter;
			++letter;
		}
	}
	for ( i = 0; i < flag; i++ )
		for ( j = 0; j < Change.length(); j++ )
		{
			ss = move( part[i], Change[j], b );
			if ( part[i] != "" && ss != "&" )
				cout << letters[i] << " " << Change[j] << " ";
			for ( x = 0; x < flag; x++ )
				if ( boolisexist( ss.substr( 0, 1 ), part[x] ) )
					cout << letters[x] << endl;
		}
	system( "pause" );
	return(0);
}


