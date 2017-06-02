/*
	任意给出一组关键字（关键字的个数和值在运行时由键盘输入)
	分别采用直接插入排序、希尔排序和快速排序算法对其进行排序,
	并输出每个排序算法得到的序列到一个设计的哈希表中,
	并对其进行哈希查找。 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define manx 1000
#define P 13	//此数用于设计取模哈希函数，取值根据数据的大小进行修改，测试方便默认15组数据 
//自定义关键字类型
typedef int KeyType;
//自定义其他关键字类型
typedef int OtherKeyType;
//自定义数据类型
typedef struct vnode{
	KeyType key;
	bool falg;				//判断哈希冲突 
	OtherKeyType otherKey;	//待用扩展参数 
	struct vnode *next;		//留作设计哈希表函数使用 
}DataType;
//定义顺序表查找结构
typedef struct {
	DataType elem[manx + 1];	//首空间不使用 ，留作监督稍  
	int length;					//线性表的长度 
}LinearTable; 
//定义哈希表存储结构用来设计哈希查找
typedef struct node {
	DataType elem[manx + 1];	//首空间不使用 ，留作监督稍 
	int length;					//哈希表的线性表部分长度 
}HashTable;
//声明函数(排序算法全是从小到大有序)
void print_LinearTable(LinearTable *Table);	//输出LinearTable表测试函数 
void print_HashTable(HashTable *Table);		//输出HashTable表测试函数 
int  Hash(int d);	//取模哈希函数设计
void StraightInsertionSort(LinearTable *Table);	//直接插入排序
void ShellSort(LinearTable *Table,int gaps[],int t);	//Shell排序
void ShellInsert(LinearTable *Table,int gap);
void QuickSort(LinearTable *Table,int low,int high);	//快速排序
void HashInit(HashTable *Table);	//哈希初始化 
void HashInsert(HashTable *Table,KeyType key);	//哈希插入 
int  HashSearch(HashTable *Table,KeyType key);	//希尔查找
int FLAG = 0;
int main()
{
	freopen("input6.txt","r",stdin);
	int i,gaps[3] = {5,3,1};
	KeyType key;
	LinearTable *Linear_Table;
	HashTable   *Hash_Table;
	Linear_Table = (LinearTable *) malloc (sizeof(LinearTable));
	Hash_Table   = (HashTable  *) malloc (sizeof(HashTable));
	Linear_Table->length = 15;		//测试用例 
	Hash_Table->length = 15;			//测试用例 
	//直接插入排序测试 
	printf("直接插入排序测试\n");
	for(i = 1; i <= Linear_Table->length; i++)
	{
		scanf("%d",&key);
		Linear_Table->elem[i].key = key;
	}
	print_LinearTable(Linear_Table); 
	printf("\n");
	StraightInsertionSort(Linear_Table);
	print_LinearTable(Linear_Table); 
	printf("\n");
	//Shell排序测试
	printf("Shell排序测试\n");
	printf("FLAG = %d\n",FLAG);
	for(i = 1; i <= Linear_Table->length; i++)
	{
		scanf("%d",&key);
		Linear_Table->elem[i].key = key;
	}
	print_LinearTable(Linear_Table); 
	printf("\n");
	ShellSort(Linear_Table,gaps,3); 
	//ShellInsert(Linear_Table,1);
		//if(FLAG == 2)
	printf("FLAG = %d\n",FLAG);
	print_LinearTable(Linear_Table); 
	printf("\n");
	//快速排序测试 
	printf("快速排序测试\n");
	for(i = 1; i <= Linear_Table->length; i++)
	{
		scanf("%d",&key);
		Linear_Table->elem[i].key = key;
	}
	print_LinearTable(Linear_Table); 
	printf("\n");
	QuickSort(Linear_Table,1,15);
	print_LinearTable(Linear_Table); 
	printf("\n");
	printf("完成测试\n");
	printf("哈希函数测试开始\n");
	HashInit(Hash_Table);	//哈希初始化 
	for(i = 1; i <= Hash_Table->length; i++)
	{
		scanf("%d",&key);
		HashInsert(Hash_Table,key);
	}
	printf("输出设计的哈希表\n"); 
	print_HashTable(Hash_Table);
	printf("\n进行查找\n");
	for(i = 1; i <= Hash_Table->length; i++)
	{
		if(HashSearch(Hash_Table,i) == 1)
		{
			printf("%d在哈希表中\n",i);
		}
		else
			printf("%d不在哈希表中\n",i);
	}
	
	return 0;
}
int Hash(int d)	//取模哈希函数设计
{
	return (d % P); 
}
void StraightInsertionSort(LinearTable *Table)	//直接插入排序，low表示从什么地方有序
{
	int i,j;
	for(i = 2; i <= Table->length; i++)
	{
		Table->elem[0] = Table->elem[i]; 
		j = i - 1;
		while(Table->elem[0].key < Table->elem[j].key)
		{
			Table->elem[j + 1] = Table->elem[j];
			j--; 
		}
		Table->elem[j + 1] = Table->elem[0];
	} 
}
void ShellSort(LinearTable *Table,int gaps[],int t)	//Shell排序
{
	int k;
	for(k = 0; k < t; k++)
	{
		ShellInsert(Table,gaps[k]);
		//printf("%d\n",gaps[k]);
	}
}
void ShellInsert(LinearTable *Table,int gap)	//Shell单次插入排序 
{
	int i,j;
	for(i = gap + 1; i <= Table->length; i++)
	{
		if(Table->elem[i].key < Table->elem[i - gap].key)
		{
			Table->elem[0] = Table->elem[i];
			for(j = i - gap; j > 0 && Table->elem[0].key < Table->elem[j].key; j -= gap)
			{
				Table->elem[j + gap] = Table->elem[j];
			} 
			Table->elem[j + gap] = Table->elem[0]; 
		}
	}
	FLAG++;
}

void QuickSort(LinearTable *Table,int low,int high)	//快速排序
{
	Table->elem[0] = Table->elem[low];
	int i,j;
	i = low;
	j = high;
	if(i < j)
	{
		while(i < j && Table->elem[j].key >= Table->elem[0].key)
		{
			j--;
		}
		if(i < j)
			Table->elem[i++] = Table->elem[j];
		while(i < j && Table->elem[i].key < Table->elem[0].key)
		{
			i++;
		}
		if(i < j)
			Table->elem[j--] = Table->elem[i];
		Table->elem[i] = Table->elem[0];
		QuickSort(Table,low,i - 1);
		QuickSort(Table,i + 1,high);
	}
} 
void HashInit(HashTable *Table)	//哈希初始化 
{
	int i;
	for(i = 0; i <= Table->length; i++)
	{
		Table->elem[i].key  = -999;
		Table->elem[i].falg = false;	//将所有位标志位未使用 
		Table->elem[i].next = NULL;
	}
} 
void HashInsert(HashTable *Table,KeyType key)	//哈希插入 
{
	int d;
	d = Hash(key);
	struct vnode *p;
	if(Table->elem[d].falg == false)
	{
		Table->elem[d].key = key;
		Table->elem[d].falg = true;
	}
	else
	{
		p = (struct vnode *) malloc (sizeof(struct vnode));
		p->key = key;
		p->next = Table->elem[d].next;
		Table->elem[d].next = p;
	}
}
int HashSearch(HashTable *Table,KeyType key)	//哈希查找，返回1表示查找成功，返回0表示查找失败 
{
	int d;
	struct vnode *p;
	HashTable *q;
	q = Table;
	d = Hash(key);
	if(q->elem[d].key == key)	return 1;
	p = q->elem[d].next;
	while(p != NULL)
	{
		if(p->key == key) return 1;
		p = p->next;
	}
	return 0;
}
void print_LinearTable(LinearTable *Table)	//输出LinearTable表测试函数 
{
	int i;
	for(i = 1; i <= Table->length ;i++)
	{
		printf("%d   ",Table->elem[i].key);
	}
}
void print_HashTable(HashTable *Table)		//输出HashTable表测试函数 
{
	int i;
	struct vnode *p;
	for(i = 0; i <= Table->length ;i++)
	{
		printf("%d   ",Table->elem[i].key);
		p = Table->elem[i].next;
		while(p != NULL)
		{
			printf("%d   ",p->key);
			p = p->next;
		} 
	}
} 
