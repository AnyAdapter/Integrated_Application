/*
	�������һ��ؼ��֣��ؼ��ֵĸ�����ֵ������ʱ�ɼ�������)
	�ֱ����ֱ�Ӳ�������ϣ������Ϳ��������㷨�����������,
	�����ÿ�������㷨�õ������е�һ����ƵĹ�ϣ����,
	��������й�ϣ���ҡ� 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define manx 1000
#define P 13	//�����������ȡģ��ϣ������ȡֵ�������ݵĴ�С�����޸ģ����Է���Ĭ��15������ 
//�Զ���ؼ�������
typedef int KeyType;
//�Զ��������ؼ�������
typedef int OtherKeyType;
//�Զ�����������
typedef struct vnode{
	KeyType key;
	bool falg;
	OtherKeyType otherKey;	//������չ���� 
	struct vnode *next;
}DataType;
//����˳�����ҽṹ
typedef struct {
	DataType elem[manx + 1];	//�׿ռ䲻ʹ�� 
	int length;
}LinearTable; 
//�����ϣ��洢�ṹ������ƹ�ϣ����
typedef struct node {
	DataType elem[manx + 1];	//�׿ռ䲻ʹ�� 
	int length;
}HashTable;
//��������(�����㷨ȫ�Ǵ�С��������)
void print_LinearTable(LinearTable *Table);	//���LinearTable����Ժ��� 
void print_HashTable(HashTable *Table);		//���HashTable����Ժ��� 
int  Hash(int d);	//ȡģ��ϣ�������
void StraightInsertionSort(LinearTable *Table,int low);	//ֱ�Ӳ�������
void ShellSort(LinearTable *Table,int gaps[],int t);	//Shell����
void ShellInsert(LinearTable *Table,int gap);
int  QuickSort1(LinearTable *Table,int low,int high);	//һ�˿�������
void QuickSort(LinearTable *Table,int low,int high);	//��������
void HashInit(HashTable *Table);	//��ϣ��ʼ�� 
void HashInsert(HashTable *Table,KeyType key);	//��ϣ���� 
int  HashSearch(HashTable *Table,KeyType key);	//ϣ������
int main()
{
	freopen("input6.txt","r",stdin);
	int i,gaps[3] = {5,3,1},t = 3;
	KeyType key;
	LinearTable Table;
	Table.length = 15;
	//ֱ�Ӳ���������� 
	for(i = 1; i <= 15; i++)
	{
		scanf("%d",&key);
		Table.elem[i].key = key;
	}
	StraightInsertionSort(&Table,2);
	print_LinearTable(&Table); 
	printf("\n");
	//Shell������� 
	for(i = 1; i <= 15; i++)
	{
		scanf("%d",&key);
		Table.elem[i].key = key;
	}
	ShellSort(&Table,gaps,t); 
	print_LinearTable(&Table); 
	printf("\n");
	//����������� 
	for(i = 1; i <= 15; i++)
	{
		scanf("%d",&key);
		Table.elem[i].key = key;
	}
	QuickSort(&Table,1,15);
	print_LinearTable(&Table); 
	printf("\n");
	return 0;
}
int Hash(int d)	//ȡģ��ϣ�������
{
	return (d % P); 
}
void StraightInsertionSort(LinearTable *Table,int low)	//ֱ�Ӳ�������low��ʾ��ʲô�ط�����
{
	int i,j;
	for(i = low; low <= Table->length; low++)
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
void ShellSort(LinearTable *Table,int gaps[],int t)	//Shell����
{
	int k;
	for(k = 0; k < t; k++)
		ShellInsert(Table,gaps[k]);
} 
void ShellInsert(LinearTable *Table,int gap)	//Shell���β������� 
{
	int i,j;
	for(i = gap + 1; i <= Table->length; i++)
	{
		if(Table->elem[i].key < Table->elem[i - gap].key)
		{
			Table->elem[0] = Table->elem[i];
			for(j = i - gap; j > 0 && Table->elem[0].key > Table->elem[j].key; j -= gap)
			{
				Table->elem[j + gap] = Table->elem[j];
			} 
			Table->elem[j + gap] = Table->elem[0]; 
		}
	}
}
int QuickSort1(LinearTable *Table,int low,int high)	//һ�˿�������
{
	KeyType pivotkey;
	Table->elem[0] = Table->elem[low];
	pivotkey = Table->elem[low].key;
	while(low < high)
	{
		while(low < high && Table->elem[high].key >= high)
			high--;
		Table->elem[low] = Table->elem[high];
		while(low < high && Table->elem[low].key <= pivotkey)
			low++;
		Table->elem[high] = Table->elem[low];
	} 
	Table->elem[low] = Table->elem[0];
	return low;
}
void QuickSort(LinearTable *Table,int low,int high)	//��������
{
	int pivotloc;
	if(low < high)
	{
		pivotloc = QuickSort1(Table,low,high);
		QuickSort(Table,low,pivotloc - 1);
		QuickSort(Table,pivotloc - 1,high);
	}
} 
void HashInit(HashTable *Table)	//��ϣ��ʼ�� 
{
	int i;
	for(i = 0; i < Table->length; i++)
	{
		Table->elem[i].falg = false;	//������λ��־λδʹ�� 
		Table->elem[i].next = NULL;
	}
} 
void HashInsert(HashTable *Table,KeyType key)	//��ϣ���� 
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
int HashSearch(HashTable *Table,KeyType key)	//��ϣ���ң�����1��ʾ���ҳɹ�������0��ʾ����ʧ�� 
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
void print_LinearTable(LinearTable *Table)	//���LinearTable����Ժ��� 
{
	int i;
	for(i = 1; i <= Table->length ;i++)
	{
		printf("%d   ",Table->elem[i].key);
	}
}
void print_HashTable(HashTable *Table)		//���HashTable����Ժ��� 
{
	int i;
	for(i = 1; i <= Table->length ;i++)
	{
		printf("%d   ",Table->elem[i].key);
	}
} 
