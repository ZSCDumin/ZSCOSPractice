/**********************************************
-----电子科技大学中山学院-14软件B班-杜敏
-----操作系统课程设计-避免死锁的银行家算法
-----作者邮箱：2712220318@qq.com
-----Github地址：https://github.com/ZSCDumin
-----日期：2017-05-12 21:19
**********************************************/

#include<iostream>
using namespace std;

const int p = 4;  //进程数
const int r = 3;  //资源数

/***************
   输入函数
****************/
void input(int max[p][r], int allocation[p][r], int need[p][r], int available[r])
{
	//cout << "输入资源最大需求矩阵:\n";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> max[i][j];
		}
	}
	//cout << "输入已分配资源矩阵:\n";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			cin >> allocation[i][j];
		}
	}
	//计算还需资源矩阵
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	//cout << "输入系统当前剩余资源矩阵:\n";
	for (int j = 0; j < r; j++)
	{
		cin >> available[j];
	}
}

/***************************************************************
比较函数（比较结果为m中的元素全大于n中的元素返回1，否则返回0）
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
安全性检验函数
****************/
int stest(int allocation[p][r], int need[p][r], int available[r]) //分配，需求，可用矩阵
{
	int flag = 0, flag1 = 0;
	int need_t[r], finish[p];
	for (int i = 0; i < p; i++) //初始化finish数组
		finish[i] = 0;  
	cout << "分配序列如下：\n";
	for (int k = 0; k < p; k++) //全搜索，直至实现或不可能实现
	{
		for (int i = 0; i < p; i++)
		{
			if (finish[i] == 1)
				continue;
			else
			{
				if (com(available, need[i]))
				{
					finish[i] = 1;//finish为1,表示available满足某一进程
					cout << i + 1 << '\t';
					flag = 1;
					for (int l = 0; l < r; l++) //进程释放资源
						available[l] = available[l] + allocation[i][l];
					break;
				}
			}
			if (flag == 1)  //表示i进程顺利执行完后，重新从剩下的进程集合中找到一个满足条件的进程
				break;
		}
	}
	cout << '\n';
	for (int l = 0; l < p; l++)
	{
		if (finish[l] == 0)
			flag1 = 1;//flag1标志finish[i]是否有0存在
	}
	if (flag1 == 0)  //当flag1=0时，安全
		return 1;
	else
		return 0;
}


/*************************
申请进程后的安全性检验函数
**************************/
void rtest(int allocation[p][r], int need[p][r], int available[r], int req[r], int n)
{
	if (com(available, req) && com(need[n], req))//如果请求某个资源数小于该进程对该资源的最大需求数和系统当前该资源可用数
	{
		for (int j = 0; j < r; j++)
		{
			allocation[n][j] = allocation[n][j] + req[j]; //进程已经拥有该资源数增加
			need[n][j] = need[n][j] - req[j];  //该进程对该资源的最大需求数减少
			available[j] = available[j] - req[j];//系统当前该资源可用数减少
		}
		if (stest(allocation, need, available))//如果进行安全性检查通过
			cout << "允许第" << n + 1 << "个进程申请资源！\n";
		else
		{
			cout << "不允许" << n + 1 << "个进程申请资源！\n";
			cout << "恢复以前状态！\n";
			for (int j = 0; j < r; j++)
			{
				allocation[n][j] = allocation[n][j] - req[j];//进程已经拥有该资源数减少 
				need[n][j] = need[n][j] + req[j];//该进程对该资源的最大需求数增加
				available[j] = available[j] + req[j];//系统当前该资源可用数增加
			}
		}
	}
	else
		cout << "申请资源量出错！\n";
}

void main()
{
	freopen("r2.txt","r",stdin);

	int n; //表示第n个进程申请资源
	int max[p][r], allocation[p][r], need[p][r], available[r], request[r]; //资源最大需求矩阵，已分配资源矩阵，还需资源矩阵，系统可用资源矩阵，请求资源矩阵

	input(max, allocation, need, available);//输入数据函数

	if (stest(allocation, need, available) == 1)//检查初始状态是否安全
	{
		cout << "***********************\n";
		cout << "初始状态安全！\n";
		cout << "***********************\n";
	}
	else
	{
		cout << "***********************\n";
		cout << "初始状态不安全！\n";
		cout << "***********************\n";
		return;
	}

	//cout << "第n个进程申请资源，请输入n的值：\n";
	cin >> n;

	//cout << "请输入请求资源矩阵:\n";
	for (int j = 0; j < r; j++)
		cin >> request[j];

	rtest(allocation, need, available, request, n-1);//申请资源后检验
}