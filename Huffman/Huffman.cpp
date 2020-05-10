#include<iostream>  
#include<string>  
#include<conio.h>
#include<stdlib.h>
#include<iomanip>
#include<fstream>
#include <windows.h>
using namespace std;


struct element
{
	double weight;
	int lchild, rchild, parent;
	string ch;
	string code;
};

const int n = 27;
element huffTree[2 * n];
int deep[53];

void Select(element huffTree[], int* a, int* b, int n);//找权值最小的两个a和b  
void Huff_Tree(element huffTree[], double w[], string ch[], int n);//哈夫曼算法
void Huff_Code(element huffTree[], int n);//哈夫曼编码
void Sethuffman();//建立哈夫曼树
void Huff_Encode(element huffTree[], int n);//编码
void Huff_Decode(element huffTree[], int n);//译码
void Print(element huffTree[]);//打印哈夫曼编码
void InOrder(element huffTree[], int i, int p[53], int& num);//树的中序遍历
void Deep(element huffTree[], int i);//查找树的深度
void Printtree(element huffTree[]);//打印哈夫曼树
string Getpassword(char rch);//密码


int main()
{
	system("color 0C");
	string password;
	cout << endl << endl << endl;
	cout << "      ----------------------------------------------------------------------------------\n";
	cout << "      |                                      请输入密码：                              | \n";
	cout << "      ---------------------------------------------------------------------------------- \n";
	cout << "                                               ";
	password = Getpassword('*');
	cout << endl << endl;
	if (password == "2019")
	{
		system("CLS");
		cout << endl << endl << endl << endl << endl;
		cout << "                                        欢迎使用!" << endl << endl << endl << endl;
		Sleep(1000);
		Sethuffman();//初始化哈夫曼树
		system("CLS");//清屏
		int function;
		while (true)
		{
			//首界面
			system("color 2e");
			cout << "                                                                                     ";
			cout << "                                                                                     ";
			cout << "                                                                                     ";
			cout << "\n\n                          欢迎进入哈夫曼信息收发站!:-)    \n\n\n";
			cout << "      -----------------------------------------------------------------------\n\n";
			cout << "                          请选择需要的功能(输入序号0~4)                      \n\n";
			cout << "                                1.编码                                       \n";
			cout << "                                2.译码                                       \n";
			cout << "                                3.查看编码表                                   \n";
			cout << "                                4.查看哈夫曼树                                 \n";
			cout << "                                0.退出程序                                   \n\n";
			cout << "      ------------------------------------------------------------------------ \n";
			cout << endl << endl;
			cout << "请输入序号：  ";
			cin >> function;
			if (function == 0)break;//0退出程序
			else
			{
				system("CLS");
				switch (function)//功能选择
				{
				case 1:
				{
					system("color 3E");//颜色变化
					Huff_Encode(huffTree, n);
					break;//功能结束后返回主页面
				}
				case 2:
				{
					system("color 3E");
					Huff_Decode(huffTree, n);
					break;
				}
				case 3:
				{
					system("color BF");
					Print(huffTree);//调用打印编码表函数
					break;
				}
				case 4:
				{
					system("color 3F");
					Printtree(huffTree);//调用打印哈弗曼树函数
					break;
				}

				default:
				{
					system("color 2E");
					cout << "\n\n\n输入错误，请重新输入！\n";
					cin >> function;
					system("CLS");
					break;
				}
				}
			}
		}
	}
	else//密码输入错误，程序退出
	{
		system("CLS");
		cout << endl << endl << endl << endl;
		cout << "                              输入密码错误！" << endl << endl << endl;
		system("pause");
		return 0;
	}

	system("pause");
	return 0;
}


//找权值最小的两个a和b
void Select(element huffTree[], int* a, int* b, int n)
{
	int i;
	double weight = 0; //找最小的数
	for (i = 0; i < n; i++)
	{
		if (huffTree[i].parent != -1)     //判断节点是否已经选过
			continue;
		else
		{
			if (weight == 0)
			{
				weight = huffTree[i].weight;
				*a = i;
			}
			else
			{
				if (huffTree[i].weight < weight)
				{
					weight = huffTree[i].weight;
					*a = i;
				}
			}
		}
	}
	weight = 0; //找第二小的数
	for (i = 0; i < n; i++)
	{
		if (huffTree[i].parent != -1 || (i == *a))//排除已选过的数
			continue;
		else
		{
			if (weight == 0)
			{
				weight = huffTree[i].weight;
				*b = i;
			}
			else
			{
				if (huffTree[i].weight < weight)
				{
					weight = huffTree[i].weight;
					*b = i;
				}
			}
		}
	}
	int temp;
	if (huffTree[*a].lchild < huffTree[*b].lchild)  //小的数放左边
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

//哈夫曼算法
void Huff_Tree(element huffTree[], double w[], string ch[], int n)
{
	for (int i = 0; i < 2 * n - 1; i++) //初始过程
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
		huffTree[i].code = "";
	}
	for (int i = 0; i < n; i++)
	{
		huffTree[i].weight = w[i];
		huffTree[i].ch = ch[i];
	}
	for (int k = n; k < 2 * n - 1; k++)
	{
		int i1 = 0;
		int i2 = 0;
		Select(huffTree, &i1, &i2, k); //将i1，i2节点合成节点k
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
}

//哈夫曼编码
void Huff_Code(element huffTree[], int n)
{
	int i, j, k;
	string s = "";
	for (i = 0; i < n; i++)
	{
		s = "";
		j = i;
		while (huffTree[j].parent != -1) //从叶子往上找到根节点
		{
			k = huffTree[j].parent;
			if (j == huffTree[k].lchild) //如果是根的左孩子，则记为0
			{
				s = s + "0";
			}
			else
			{
				s = s + "1";
			}
			j = huffTree[j].parent;
		}
		for (int l = s.size() - 1; l >= 0; l--)
		{
			huffTree[i].code += s[l]; //保存编码
		}
	}
}

//建立哈夫曼树
void Sethuffman()
{
	string str[] = { "A", "B", "C", "D", "E" ,"F", "G", "H", "I", "J" ,"K", "L", "M", "N", "O" ,"P", "Q", "R", "S", "T" ,"U", "V", "W", "X", "Y" ,"Z"," " };
	double w[] = { 6.3,1.05,2.3,3.5,10.5,2.21,1.1,4.7,5.4,0.1,0.3,2.9,2.1,5.9,6.44,1.75,0.1,5.3,5.2,7.1,2.25,0.8,1.2,0.2,1.2,0.1,20 };
	Huff_Tree(huffTree, w, str, n);
	Huff_Code(huffTree, n);
}


//编码
void Huff_Encode(element huffTree[], int n)
{
	int select;
	const char* p;
	while (true)
	{
		system("color 3E");
		cout << "                                请选择从文件导入还是手动输入" << endl << endl;
		cout << "                                1.从文件导入                                       \n";
		cout << "                                2.手动输入                                        \n";
		cout << "                                0.返回主界面                                 \n\n";
		cout << endl;
		cout << "                                请输入    ";
		cin >> select;

		if (select == 0)
		{
			break;
		}//0退出程序
		else
		{
			system("CLS");
			switch (select)//功能选择
			{
			case 1:
			{
				string cd, str;
				system("color 02");//颜色变化
				ifstream fc("e:\\decode.txt");
				if (!fc.is_open())
				{
					cout << "文件打开失败!" << endl;
					break;
				}
				getline(fc,cd);
				for (int i = 0; i < cd.size(); i++)
				{
					for (int j = 0; j < n; j++)
					{
						p = huffTree[j].ch.c_str();
						if (cd[i] == *p)
						{
							str = str + huffTree[j].code;
							break;
						}

					}
				}
				fc.close();
				cout << "编码为" << endl << str << endl;

				int o;
				while (true)//输入错误后可重新输入
				{
					cout << "\n\n\n是否保存为文件？(输入1保存，输入0返回上一级)\n" << endl;
					cout << "请输入  ";
					cin >> o;
					if (o != 0 && o != 1)continue;//输入错误进行循环
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//退出循环
							break;
						}
						if (o == 1)//将编码保存在文件中
						{
							ofstream fc("e:\\encode.txt");
							if (!fc.is_open())  //将数据存入新的文件
							{
								cout << "\n\n\n保存失败！请重试！";
								cout << "按任意键继续......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n保存成功！" << endl << "按任意键返回主菜单..." << endl;//清屏后返回主菜单
								_getch();
								system("CLS");
								break;
							}
						}
					}
				}
				break;
			}
			case 2:
			{
				string cd, str;
				string a;
				system("color 02");
				cout << "请输入需要编码的文段" << endl;
				getline(cin, a);    //清空输入缓存区无效，此语句为了捕获上一个回车符，也可将下面的getline中结束符更改成除了回车符以外的字符
				getline(cin, cd);  //获取带空格的字符串
				for (int i = 0; i < cd.size(); i++)
				{
					for (int j = 0; j < n; j++)
					{
						p = huffTree[j].ch.c_str();
						if (cd[i] == *p)
						{
							str = str + huffTree[j].code;
							break;
						}

					}
				}
				cout << "编码为" << endl << str << endl;

				int o;
				while (true)//输入错误后可重新输入
				{
					cout << "\n\n\n是否保存为文件？(输入1保存，输入0返回上一级)\n" << endl;
					cout << "请输入  ";
					cin >> o;
					if (o != 0 && o != 1)continue;//输入错误进行循环
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//退出循环
						}
						if (o == 1)//将编码保存在文件中
						{
							ofstream fc("e:\\encode.txt", ios::app);
							if (!fc.is_open())  //将数据存入新的文件
							{
								cout << "\n\n\n保存失败！请重试！";
								cout << "按任意键继续......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n保存成功！" << endl << "按任意键返回主菜单..." << endl;//清屏后返回主菜单
								_getch();
								system("CLS");
								break;
							}
						}
					}
				}
			}
			break;
			default:
			{
				system("color 2e");
				cout << "\n\n\n输入错误，请重新输入！\n";
				cin >> select;
				system("CLS");
				break;
			}
			}
		}
		cout << endl;

	}

	system("CLS");

}


//译码
void Huff_Decode(element huffTree[], int n)
{
	int select;
	while (true)
	{
		system("color 3E");
		cout << "                                请选择从文件导入还是手动输入" << endl << endl;
		cout << "                                1.从文件导入                                       \n";
		cout << "                                2.手动输入                                        \n";
		cout << "                                0.返回主界面                                 \n\n";
		cout << endl;
		cout << "                                请输入    ";
		cin >> select;
		if (select == 0)
		{
			break;
		}//0退出程序
		else
		{
			system("CLS");
			switch (select)//功能选择
			{
			case 1:
			{
				string s;
				string temp = "", str = "";//保存解码后的字符串
				system("color 02");//颜色变化
				ifstream fc("e:\\encode.txt");
				if (!fc.is_open())
				{
					cout << "文件打开失败!" << endl;
					break;
				}
				fc >> s;
				for (int i = 0; i < s.size(); i++)
				{
					temp = temp + s[i];
					for (int j = 0; j < n; j++)
					{
						if (temp == huffTree[j].code)
						{
							str = str + huffTree[j].ch;
							temp = "";
							break;
						}
						else if (i == s.size() - 1 && j == n - 1 && temp != "")//全部遍历后没有
						{
							str = "解码错误！";
						}
					}
				}
				fc.close();
				cout << endl;
				cout << "译码为" << endl << str << endl;

				int o;
				while (true)//输入错误后可重新输入
				{
					cout << "\n\n\n是否保存为文件？(输入1保存，输入0返回上一级)\n" << endl;
					cout << "请输入:";
					cin >> o;
					if (o != 0 && o != 1)continue;//输入错误进行循环
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//退出循环，返回主菜单
						}
						if (o == 1)//将编码保存在文件中
						{
							ofstream fc("e:\\decode.txt");
							if (!fc.is_open())  //将数据存入新的文件
							{
								cout << "\n\n\n保存失败！请重试！";
								cout << "按任意键继续......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n保存成功！" << endl << "按任意键返回主菜单..." << endl;//清屏后返回主菜单
								_getch();
								system("CLS");
								break;
							}
						}
					}
				}
				break;
			}
			case 2:
			{
				string s;
				string temp = "", str = "";//保存解码后的字符串
				system("color 02");
				cout << "请输入需要解码的序列" << endl;
				cin >> s;
				for (int i = 0; i < s.size(); i++)
				{
					temp = temp + s[i];
					for (int j = 0; j < n; j++)
					{
						if (temp == huffTree[j].code)
						{
							str = str + huffTree[j].ch;
							temp = "";
							break;
						}
						else if (i == s.size() - 1 && j == n - 1 && temp != "")//全部遍历后没有
						{
							str = "解码错误！";
						}
					}
				}
				system("CLS");
				cout << "解码后的编码为：" << str << endl;


				int o;
				while (true)//输入错误后可重新输入
				{
					cout << "\n\n\n是否保存为文件？(输入1保存，输入0返回上一级)\n" << endl;
					cout << "请输入:";
					cin >> o;
					if (o != 0 && o != 1)continue;//输入错误进行循环
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//退出循环，返回主菜单
						}
						if (o == 1)//将编码保存在文件中
						{
							ofstream fc("e:\\decode.txt", ios::app);
							if (!fc.is_open())  //将数据存入新的文件
							{
								cout << "\n\n\n保存失败！请重试！";
								cout << "按任意键继续......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n保存成功！" << endl << "按任意键返回主菜单..." << endl;//清屏后返回主菜单
								_getch();
								system("CLS");
								break;
							}
						}
					}
				}
				break;
			}

			default:
			{
				system("color 2E");
				cout << "\n\n\n输入错误，请重新输入！\n";
				cin >> select;
				system("CLS");
				break;
			}
			}
		}
	}
	system("CLS");
}


//打印哈夫曼编码
void Print(element huffTree[])
{
	for (int i = 0; i < 27; i++)
	{

		cout << "字符 " << huffTree[i].ch << " 的编码：";
		cout << huffTree[i].code;
		cout << endl;
	}
	system("pause");
	system("CLS");
}


//中序遍历
void InOrder(element huffTree[], int i, int p[53], int& num)
{
	if (huffTree[i].lchild != -1)
	{//中序遍历左子树
		InOrder(huffTree, huffTree[i].lchild, p, num);
	}
	p[num++] = i;//将中序遍历序列储存到数组中
	if (huffTree[i].rchild != -1)
	{//中序遍历右子树
		InOrder(huffTree, huffTree[i].rchild, p, num);
	}
}

//查找树的深度
void Deep(element huffTree[], int i)
{
	if (huffTree[i].lchild != -1)   //对左子树进行遍历
	{
		deep[huffTree[i].lchild] = deep[i] + 1;//深度为其双亲结点的深度加一
		Deep(huffTree, huffTree[i].lchild);
	}
	if (huffTree[i].rchild != -1)   //对右子树进行遍历
	{
		deep[huffTree[i].rchild] = deep[i] + 1;//深度为其双亲结点的深度加一
		Deep(huffTree, huffTree[i].rchild);
	}
}

//打印哈夫曼树
void Printtree(element huffTree[])
{
	for (int i = 27; i < 53; i++)//将哈夫曼树中所有新生结点的data域置为*，代表着该节点为新生结点
	{
		huffTree[i].ch = '*';
	}

	int tree[53], j, k, l, temp, num = 0;
	Deep(huffTree, 52);             //求树中每个节点的深度
	temp = deep[0];
	for (int i = 0; i < 53; i++)			//求出哈夫曼树的最大深度，赋值给temp
	{
		if (temp < deep[i])
			temp = deep[i];
	}
	InOrder(huffTree, 52, tree, num);        //中序遍历哈夫曼树，将各结点顺序编号储存在数组tree[]中
	for (int i = 0; i <= temp; i++)			//每一层进行循环，直至达到最大深度temp
	{
		cout << endl << endl;
		int prior = 0;				         //间隔prior初始化
		for (k = 0; k < num; k++)			//从左往右数的位置k
		{
			for (j = 52; j >= 0; j--)      //枚举每一个数据
			{
				if (deep[j] == i && tree[k] == j)//层数符合且位置的下标对应
				{
					for (l = prior; l < k + 1; l++) //空出间隔，使打印出的树更加直观
						cout << " ";
					prior = k + 2;			   //更新间隔
					cout << huffTree[j].ch;//输出该结点的ch域
				}
			}
		}
	}
	cout << endl;
	cout << "\n\n\n打印哈夫曼树成功！" << endl << "按任意键返回主菜单..." << endl;
	system("pause");
	system("CLS");
}


//密码
string Getpassword(char rch)
{
	string ret;
	char ch;
	ch = _getch();
	while (ch != '\n' && ch != '\r')
	{
		_putch(rch);
		ret += ch;
		ch = _getch();
	}

	return ret;

}

