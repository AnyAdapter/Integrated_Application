#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//�Զ���ؼ�������
typedef int KeyType;
//�Զ��������ؼ�������
typedef int OtherKeyType;
//�Զ�����������
typedef struct {
	KeyType key;
	OtherKeyType otherKey;
}DataType;
//����������Ĵ洢�ṹ
typedef struct node {
	DataType elem;
	struct node *lchild;
	struct node *rchild;
}*BinTree;

#define manx 10000
#define xxx  -999	//�����ֱ�ʾδ֪���� 
KeyType a[manx];	//�������ʱ�۰����ʹ��

//������������
void BinTreeInsert(BinTree *t,KeyType k);//���뺯��
void InOrder(BinTree t,int i);//�������������
int	 BinSearch_1(int *s,int low,int high,KeyType key);	//�ݹ�
int  BinSearch_2(int *s,int low,int high,KeyType key);	//�ǵݹ� 
int main()
{
	//Ĭ��ֵ����Ϊ10�� 
	freopen("input5.txt","r",stdin);
	BinTree t;
	int i;
	KeyType k;
	for(i = 0 ; i < 10; i++)
	{
		scanf("%d",&k);
		BinTreeInsert(&t,k);
	}
	memset(a,xxx,sizeof(a));
	i = 0;
	InOrder(t,i);
	if(BinSearch_1(a,0,10,3) == 1)
		printf("\n����������3Ԫ��\n");
	else printf("\n��������û��3Ԫ��\n");
	printf("�ݹ���ҳɹ�\n");
	if(BinSearch_2(a,1,10,11) == 1)
		printf("����������11Ԫ��\n");
	else printf("��������û��11Ԫ��\n"); 
	printf("�ǵݹ���ҳɹ�\n");
}
//����ʵ��
void BinTreeInsert(BinTree *t,KeyType k)//���뺯��
{
	BinTree p;
	if(*t == NULL)	
	{
		p = (BinTree) malloc (sizeof(struct node));
		p->elem.key = k;
		p->lchild = p->rchild = NULL;
		*t = p;
		return ;
	}
	if( (*t)->elem.key == k)	return ;
	if( (*t)->elem.key > k)		BinTreeInsert(& ( (*t)->lchild ),k);
	if( (*t)->elem.key < k) 	BinTreeInsert(& ( (*t)->rchild ),k);
}
void Visit(KeyType k)
{
	printf("%d   ",k);
}
void InOrder(BinTree t,int i)//�������������
{
	if(t != NULL)
	{
		InOrder(t->lchild,i);
		Visit(t->elem.key);
		a[i++] = t->elem.key;
		InOrder(t->rchild,i);
	}
}
int	 BinSearch_1(int *s,int low,int high,KeyType key)	//�ݹ�
{
	/*����0��ʾ����ʧ�ܣ�����1��ʾ���ҳɹ�*/
	int middle = ( low + high ) / 2;	
	if(low > high)	return 0;
	else if(key == s[middle])	return 1;
	else if(key > s[middle])
		return (BinSearch_1(s,middle + 1,high,key));
	else	return (BinSearch_1(s,low,middle - 1,key));
}
int  BinSearch_2(int *s,int low,int high,KeyType key)	//�ǵݹ� 
{
	/*����0��ʾ����ʧ�ܣ�����1��ʾ���ҳɹ�*/
	int middle = ( low + high ) / 2;
	while(low > high)
	{
		if(s[middle] == key)	return 1;
		else if(s[middle] > key) low = middle + 1;
		else high = middle - 1;
	}
	return 0;
}
