#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
#define max 100


struct edge {
	string	start;  /* 边的初始结点 */
	string	change; /* 边的条件 */
	string	last;   /* 边的终点 */
};
int	N;              /* NFA的边数 */
string	part[max];      /* 分割子集 */


/* 状态集合I的a弧转换 , 判断set集合中元素经过条件ch能到达的边集合*/
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


/* 判断子串是否存在在某一集合 */
int boolisexist( string s, string d )
{
	if ( d != "" && 0 <= d.find( s ) && d.find( s ) <= d.length() - 1 )
	{
		return(1);
	}else  {
		return(0);
	}
}


/* 分割子集法进行DFA的最小化 */

int divide( edge *b, string change )
{
	int	x, m, flag = 2, flag0, i, j;
	string	ss, part0[max];
	flag0 = flag;
	for ( x = 0; x < change.length(); x++ )
	{
		for ( m = 0; m < flag0; m++ )
		{
			for ( i = 0; i < part[m].length(); i++ ) //遍历划分的集合，判断每一个集合经过 change 后 能到达的 集合
			{
				ss = move( part[m].substr( i, 1 ), change[x], b );
				for ( j = 0; j < flag; j++ )
				{
					if ( boolisexist( ss, part[j] ) )   //判断同一集合中元素 经过 相同的 change 后 是否在 同一集合。如果不是则将元素重新划分
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
	string	Change; /* 输入符号 */
	string	ss,str, temp[4];
	edge	*b = new edge[max];
	int f = 0;
	int g = 0;
	bool point = false;
///*
    printf("%s","读取文件中>>>>>>>>>>>>>>>>>>>>>>>>>>>>读取完成！\n");
//读取文件形式
    // 以读模式打开文件
   ifstream infile;

   infile.open("dfa.txt");
   while(getline(infile,str))   //按行读取,遇到换行符结束
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

   // 关闭打开的文件
   infile.close();


   //遍历读取信息
   cout << "读取的边的信息为：" << endl;
   cout << "起点" << "\t" << "条件" << "\t" << "终点" << endl;
   for(int k=0;k<N;k++){
        cout << b[k].start << "\t" << b[k].change << "\t" << b[k].last << endl;
   }
   	printf( "该DFA的终态集合为：" );
	cout << part[1] << endl;
	printf( "该DFA的非终态集合为：" );
	cout << part[0] << endl;
	printf( "此DFA状态中的输入符号即边上的条件为:" );
	cout << Change << endl;
//*/

//手动输入
/*
	printf( "请输入DFA各边信息：起点条件（空用&表示）终点，以输入#结束。" );
	for ( i = 0; i < max; i++ )
	{
		cin >> b[i].start;
		if ( b[i].start == "#" )
			break;
		else
			cin >> b[i].change >> b[i].last;
	}
	N = i;
	printf( "请输入该DFA的终态集合：" );
	cin >> part[1];
	printf( "请输入该DFA的非终态集合：" );
	cin >> part[0];
	printf( "请输入此DFA状态中的输入符号即边上的条件:" );
	cin >> Change;
*/

	flag = divide( b, Change );
	printf( "此DFA最小化划分的子集如下：\n" );
	for ( i = 0; i < flag; i++ )
	{
		if ( part[i] != "" )
			cout << part[i] << endl;
	}
	printf( "用状态A,B,C···等代替子集：" );
	for ( i = 0; i < flag; i++ )
	{
		if ( part[i] != "" )
			cout << "{" << part[i] << "},";
	}
	printf( "则DFA最小化后的各边信息如下：\n" );
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


