/**********************************************
-----���ӿƼ���ѧ��ɽѧԺ-14���B��-����
-----����ϵͳ�γ����-�������������м��㷨
-----�������䣺2712220318@qq.com
-----Github��ַ��https://github.com/ZSCDumin
-----���ڣ�2017-05-12 21:19
**********************************************/

#include<iostream>
using namespace std;

const int p = 4;  //������
const int r = 3;  //��Դ��

/***************
   ���뺯��
****************/
void input(int max[p][r], int allocation[p][r], int need[p][r], int available[r])
{
	//cout << "������Դ����������:\n";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> max[i][j];
		}
	}
	//cout << "�����ѷ�����Դ����:\n";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> allocation[i][j];
		}
	}
	//���㻹����Դ����
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	//cout << "����ϵͳ��ǰʣ����Դ����:\n";
	for (int j = 0; j < r; j++)
	{
		cin >> available[j];
	}
}

/***************************************************************
�ȽϺ������ȽϽ��Ϊm�е�Ԫ��ȫ����n�е�Ԫ�ط���1�����򷵻�0��
****************************************************************/
int com(int m[r], int n[r])
{
	int flag = 0;
	for (int i = 0; i < r; i++)
		if (m[i] < n[i])
		{
			flag = 1;
			break;
		}
	if (flag == 1)	
		return 0;
	else 
		return 1;
}

/***************
��ȫ�Լ��麯��
****************/
int stest(int allocation[p][r], int need[p][r], int available[r]) //���䣬���󣬿��þ���
{
	int flag = 0, flag1 = 0;
	int need_t[r], finish[p];
	for (int i = 0; i < p; i++) //��ʼ��finish����
		finish[i] = 0;  
	cout << "�����������£�\n";
	for (int k = 0; k < p; k++) //ȫ������ֱ��ʵ�ֻ򲻿���ʵ��
	{
		for (int i = 0; i < p; i++)
		{
			if (finish[i] == 1)
				continue;
			else
			{
				if (com(available, need[i]))
				{
					finish[i] = 1;//finishΪ1,��ʾavailable����ĳһ����
					cout << i + 1 << '\t';
					flag = 1;
					for (int l = 0; l < r; l++) //�����ͷ���Դ
						available[l] = available[l] + allocation[i][l];
					break;
				}
			}
			if (flag == 1)  //��ʾi����˳��ִ��������´�ʣ�µĽ��̼������ҵ�һ�����������Ľ���
				break;
		}
	}
	cout << '\n';
	for (int l = 0; l < p; l++)
	{
		if (finish[l] == 0)
			flag1 = 1;//flag1��־finish[i]�Ƿ���0����
	}
	if (flag1 == 0)  //��flag1=0ʱ����ȫ
		return 1;
	else
		return 0;
}


/*************************
������̺�İ�ȫ�Լ��麯��
**************************/
void rtest(int allocation[p][r], int need[p][r], int available[r], int req[r], int n)
{
	if (com(available, req) && com(need[n], req))//�������ĳ����Դ��С�ڸý��̶Ը���Դ�������������ϵͳ��ǰ����Դ������
	{
		for (int j = 0; j < r; j++)
		{
			allocation[n][j] = allocation[n][j] + req[j]; //�����Ѿ�ӵ�и���Դ������
			need[n][j] = need[n][j] - req[j];  //�ý��̶Ը���Դ���������������
			available[j] = available[j] - req[j];//ϵͳ��ǰ����Դ����������
		}
		if (stest(allocation, need, available))//������а�ȫ�Լ��ͨ��
			cout << "�����" << n + 1 << "������������Դ��\n";
		else
		{
			cout << "������" << n + 1 << "������������Դ��\n";
			cout << "�ָ���ǰ״̬��\n";
			for (int j = 0; j < r; j++)
			{
				allocation[n][j] = allocation[n][j] - req[j];//�����Ѿ�ӵ�и���Դ������ 
				need[n][j] = need[n][j] + req[j];//�ý��̶Ը���Դ���������������
				available[j] = available[j] + req[j];//ϵͳ��ǰ����Դ����������
			}
		}
	}
	else
		cout << "������Դ������\n";
}

void main()
{
	freopen("r2.txt","r",stdin);

	int n; //��ʾ��n������������Դ
	int max[p][r], allocation[p][r], need[p][r], available[r], request[r]; //��Դ�����������ѷ�����Դ���󣬻�����Դ����ϵͳ������Դ����������Դ����

	input(max, allocation, need, available);//�������ݺ���

	if (stest(allocation, need, available) == 1)//����ʼ״̬�Ƿ�ȫ
	{
		cout << "***********************\n";
		cout << "��ʼ״̬��ȫ��\n";
		cout << "***********************\n";
	}
	else
	{
		cout << "***********************\n";
		cout << "��ʼ״̬����ȫ��\n";
		cout << "***********************\n";
		return;
	}

	//cout << "��n������������Դ��������n��ֵ��\n";
	cin >> n;

	//cout << "������������Դ����:\n";
	for (int j = 0; j < r; j++)
		cin >> request[j];

	rtest(allocation, need, available, request, n-1);//������Դ�����
}