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

void Select(element huffTree[], int* a, int* b, int n);//��Ȩֵ��С������a��b  
void Huff_Tree(element huffTree[], double w[], string ch[], int n);//�������㷨
void Huff_Code(element huffTree[], int n);//����������
void Sethuffman();//������������
void Huff_Encode(element huffTree[], int n);//����
void Huff_Decode(element huffTree[], int n);//����
void Print(element huffTree[]);//��ӡ����������
void InOrder(element huffTree[], int i, int p[53], int& num);//�����������
void Deep(element huffTree[], int i);//�����������
void Printtree(element huffTree[]);//��ӡ��������
string Getpassword(char rch);//����


int main()
{
	system("color 0C");
	string password;
	cout << endl << endl << endl;
	cout << "      ----------------------------------------------------------------------------------\n";
	cout << "      |                                      ���������룺                              | \n";
	cout << "      ---------------------------------------------------------------------------------- \n";
	cout << "                                               ";
	password = Getpassword('*');
	cout << endl << endl;
	if (password == "2019")
	{
		system("CLS");
		cout << endl << endl << endl << endl << endl;
		cout << "                                        ��ӭʹ��!" << endl << endl << endl << endl;
		Sleep(1000);
		Sethuffman();//��ʼ����������
		system("CLS");//����
		int function;
		while (true)
		{
			//�׽���
			system("color 2e");
			cout << "                                                                                     ";
			cout << "                                                                                     ";
			cout << "                                                                                     ";
			cout << "\n\n                          ��ӭ�����������Ϣ�շ�վ!:-)    \n\n\n";
			cout << "      -----------------------------------------------------------------------\n\n";
			cout << "                          ��ѡ����Ҫ�Ĺ���(�������0~4)                      \n\n";
			cout << "                                1.����                                       \n";
			cout << "                                2.����                                       \n";
			cout << "                                3.�鿴�����                                   \n";
			cout << "                                4.�鿴��������                                 \n";
			cout << "                                0.�˳�����                                   \n\n";
			cout << "      ------------------------------------------------------------------------ \n";
			cout << endl << endl;
			cout << "��������ţ�  ";
			cin >> function;
			if (function == 0)break;//0�˳�����
			else
			{
				system("CLS");
				switch (function)//����ѡ��
				{
				case 1:
				{
					system("color 3E");//��ɫ�仯
					Huff_Encode(huffTree, n);
					break;//���ܽ����󷵻���ҳ��
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
					Print(huffTree);//���ô�ӡ�������
					break;
				}
				case 4:
				{
					system("color 3F");
					Printtree(huffTree);//���ô�ӡ������������
					break;
				}

				default:
				{
					system("color 2E");
					cout << "\n\n\n����������������룡\n";
					cin >> function;
					system("CLS");
					break;
				}
				}
			}
		}
	}
	else//����������󣬳����˳�
	{
		system("CLS");
		cout << endl << endl << endl << endl;
		cout << "                              �����������" << endl << endl << endl;
		system("pause");
		return 0;
	}

	system("pause");
	return 0;
}


//��Ȩֵ��С������a��b
void Select(element huffTree[], int* a, int* b, int n)
{
	int i;
	double weight = 0; //����С����
	for (i = 0; i < n; i++)
	{
		if (huffTree[i].parent != -1)     //�жϽڵ��Ƿ��Ѿ�ѡ��
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
	weight = 0; //�ҵڶ�С����
	for (i = 0; i < n; i++)
	{
		if (huffTree[i].parent != -1 || (i == *a))//�ų���ѡ������
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
	if (huffTree[*a].lchild < huffTree[*b].lchild)  //С���������
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

//�������㷨
void Huff_Tree(element huffTree[], double w[], string ch[], int n)
{
	for (int i = 0; i < 2 * n - 1; i++) //��ʼ����
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
		Select(huffTree, &i1, &i2, k); //��i1��i2�ڵ�ϳɽڵ�k
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
}

//����������
void Huff_Code(element huffTree[], int n)
{
	int i, j, k;
	string s = "";
	for (i = 0; i < n; i++)
	{
		s = "";
		j = i;
		while (huffTree[j].parent != -1) //��Ҷ�������ҵ����ڵ�
		{
			k = huffTree[j].parent;
			if (j == huffTree[k].lchild) //����Ǹ������ӣ����Ϊ0
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
			huffTree[i].code += s[l]; //�������
		}
	}
}

//������������
void Sethuffman()
{
	string str[] = { "A", "B", "C", "D", "E" ,"F", "G", "H", "I", "J" ,"K", "L", "M", "N", "O" ,"P", "Q", "R", "S", "T" ,"U", "V", "W", "X", "Y" ,"Z"," " };
	double w[] = { 6.3,1.05,2.3,3.5,10.5,2.21,1.1,4.7,5.4,0.1,0.3,2.9,2.1,5.9,6.44,1.75,0.1,5.3,5.2,7.1,2.25,0.8,1.2,0.2,1.2,0.1,20 };
	Huff_Tree(huffTree, w, str, n);
	Huff_Code(huffTree, n);
}


//����
void Huff_Encode(element huffTree[], int n)
{
	int select;
	const char* p;
	while (true)
	{
		system("color 3E");
		cout << "                                ��ѡ����ļ����뻹���ֶ�����" << endl << endl;
		cout << "                                1.���ļ�����                                       \n";
		cout << "                                2.�ֶ�����                                        \n";
		cout << "                                0.����������                                 \n\n";
		cout << endl;
		cout << "                                ������    ";
		cin >> select;

		if (select == 0)
		{
			break;
		}//0�˳�����
		else
		{
			system("CLS");
			switch (select)//����ѡ��
			{
			case 1:
			{
				string cd, str;
				system("color 02");//��ɫ�仯
				ifstream fc("e:\\decode.txt");
				if (!fc.is_open())
				{
					cout << "�ļ���ʧ��!" << endl;
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
				cout << "����Ϊ" << endl << str << endl;

				int o;
				while (true)//�����������������
				{
					cout << "\n\n\n�Ƿ񱣴�Ϊ�ļ���(����1���棬����0������һ��)\n" << endl;
					cout << "������  ";
					cin >> o;
					if (o != 0 && o != 1)continue;//����������ѭ��
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//�˳�ѭ��
							break;
						}
						if (o == 1)//�����뱣�����ļ���
						{
							ofstream fc("e:\\encode.txt");
							if (!fc.is_open())  //�����ݴ����µ��ļ�
							{
								cout << "\n\n\n����ʧ�ܣ������ԣ�";
								cout << "�����������......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n����ɹ���" << endl << "��������������˵�..." << endl;//�����󷵻����˵�
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
				cout << "��������Ҫ������Ķ�" << endl;
				getline(cin, a);    //������뻺������Ч�������Ϊ�˲�����һ���س�����Ҳ�ɽ������getline�н��������ĳɳ��˻س���������ַ�
				getline(cin, cd);  //��ȡ���ո���ַ���
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
				cout << "����Ϊ" << endl << str << endl;

				int o;
				while (true)//�����������������
				{
					cout << "\n\n\n�Ƿ񱣴�Ϊ�ļ���(����1���棬����0������һ��)\n" << endl;
					cout << "������  ";
					cin >> o;
					if (o != 0 && o != 1)continue;//����������ѭ��
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//�˳�ѭ��
						}
						if (o == 1)//�����뱣�����ļ���
						{
							ofstream fc("e:\\encode.txt", ios::app);
							if (!fc.is_open())  //�����ݴ����µ��ļ�
							{
								cout << "\n\n\n����ʧ�ܣ������ԣ�";
								cout << "�����������......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n����ɹ���" << endl << "��������������˵�..." << endl;//�����󷵻����˵�
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
				cout << "\n\n\n����������������룡\n";
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


//����
void Huff_Decode(element huffTree[], int n)
{
	int select;
	while (true)
	{
		system("color 3E");
		cout << "                                ��ѡ����ļ����뻹���ֶ�����" << endl << endl;
		cout << "                                1.���ļ�����                                       \n";
		cout << "                                2.�ֶ�����                                        \n";
		cout << "                                0.����������                                 \n\n";
		cout << endl;
		cout << "                                ������    ";
		cin >> select;
		if (select == 0)
		{
			break;
		}//0�˳�����
		else
		{
			system("CLS");
			switch (select)//����ѡ��
			{
			case 1:
			{
				string s;
				string temp = "", str = "";//����������ַ���
				system("color 02");//��ɫ�仯
				ifstream fc("e:\\encode.txt");
				if (!fc.is_open())
				{
					cout << "�ļ���ʧ��!" << endl;
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
						else if (i == s.size() - 1 && j == n - 1 && temp != "")//ȫ��������û��
						{
							str = "�������";
						}
					}
				}
				fc.close();
				cout << endl;
				cout << "����Ϊ" << endl << str << endl;

				int o;
				while (true)//�����������������
				{
					cout << "\n\n\n�Ƿ񱣴�Ϊ�ļ���(����1���棬����0������һ��)\n" << endl;
					cout << "������:";
					cin >> o;
					if (o != 0 && o != 1)continue;//����������ѭ��
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//�˳�ѭ�����������˵�
						}
						if (o == 1)//�����뱣�����ļ���
						{
							ofstream fc("e:\\decode.txt");
							if (!fc.is_open())  //�����ݴ����µ��ļ�
							{
								cout << "\n\n\n����ʧ�ܣ������ԣ�";
								cout << "�����������......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n����ɹ���" << endl << "��������������˵�..." << endl;//�����󷵻����˵�
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
				string temp = "", str = "";//����������ַ���
				system("color 02");
				cout << "��������Ҫ���������" << endl;
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
						else if (i == s.size() - 1 && j == n - 1 && temp != "")//ȫ��������û��
						{
							str = "�������";
						}
					}
				}
				system("CLS");
				cout << "�����ı���Ϊ��" << str << endl;


				int o;
				while (true)//�����������������
				{
					cout << "\n\n\n�Ƿ񱣴�Ϊ�ļ���(����1���棬����0������һ��)\n" << endl;
					cout << "������:";
					cin >> o;
					if (o != 0 && o != 1)continue;//����������ѭ��
					else
					{
						if (o == 0)
						{
							system("CLS");
							break;//�˳�ѭ�����������˵�
						}
						if (o == 1)//�����뱣�����ļ���
						{
							ofstream fc("e:\\decode.txt", ios::app);
							if (!fc.is_open())  //�����ݴ����µ��ļ�
							{
								cout << "\n\n\n����ʧ�ܣ������ԣ�";
								cout << "�����������......";
								_getch();
								system("CLS");
							}
							else
							{
								fc << str;
								fc.close();
								system("CLS");
								cout << "\n\n\n����ɹ���" << endl << "��������������˵�..." << endl;//�����󷵻����˵�
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
				cout << "\n\n\n����������������룡\n";
				cin >> select;
				system("CLS");
				break;
			}
			}
		}
	}
	system("CLS");
}


//��ӡ����������
void Print(element huffTree[])
{
	for (int i = 0; i < 27; i++)
	{

		cout << "�ַ� " << huffTree[i].ch << " �ı��룺";
		cout << huffTree[i].code;
		cout << endl;
	}
	system("pause");
	system("CLS");
}


//�������
void InOrder(element huffTree[], int i, int p[53], int& num)
{
	if (huffTree[i].lchild != -1)
	{//�������������
		InOrder(huffTree, huffTree[i].lchild, p, num);
	}
	p[num++] = i;//������������д��浽������
	if (huffTree[i].rchild != -1)
	{//�������������
		InOrder(huffTree, huffTree[i].rchild, p, num);
	}
}

//�����������
void Deep(element huffTree[], int i)
{
	if (huffTree[i].lchild != -1)   //�����������б���
	{
		deep[huffTree[i].lchild] = deep[i] + 1;//���Ϊ��˫�׽�����ȼ�һ
		Deep(huffTree, huffTree[i].lchild);
	}
	if (huffTree[i].rchild != -1)   //�����������б���
	{
		deep[huffTree[i].rchild] = deep[i] + 1;//���Ϊ��˫�׽�����ȼ�һ
		Deep(huffTree, huffTree[i].rchild);
	}
}

//��ӡ��������
void Printtree(element huffTree[])
{
	for (int i = 27; i < 53; i++)//������������������������data����Ϊ*�������Ÿýڵ�Ϊ�������
	{
		huffTree[i].ch = '*';
	}

	int tree[53], j, k, l, temp, num = 0;
	Deep(huffTree, 52);             //������ÿ���ڵ�����
	temp = deep[0];
	for (int i = 0; i < 53; i++)			//������������������ȣ���ֵ��temp
	{
		if (temp < deep[i])
			temp = deep[i];
	}
	InOrder(huffTree, 52, tree, num);        //������������������������˳���Ŵ���������tree[]��
	for (int i = 0; i <= temp; i++)			//ÿһ�����ѭ����ֱ���ﵽ������temp
	{
		cout << endl << endl;
		int prior = 0;				         //���prior��ʼ��
		for (k = 0; k < num; k++)			//������������λ��k
		{
			for (j = 52; j >= 0; j--)      //ö��ÿһ������
			{
				if (deep[j] == i && tree[k] == j)//����������λ�õ��±��Ӧ
				{
					for (l = prior; l < k + 1; l++) //�ճ������ʹ��ӡ����������ֱ��
						cout << " ";
					prior = k + 2;			   //���¼��
					cout << huffTree[j].ch;//����ý���ch��
				}
			}
		}
	}
	cout << endl;
	cout << "\n\n\n��ӡ���������ɹ���" << endl << "��������������˵�..." << endl;
	system("pause");
	system("CLS");
}


//����
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

