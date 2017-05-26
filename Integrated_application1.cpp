#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//自定义关键字类型
typedef int KeyType;
//自定义其他关键字类型
typedef int OtherKeyType;
//自定义数据类型
typedef struct {
	KeyType key;
	OtherKeyType otherKey;
}DataType;
//定义二叉树的存储结构
typedef struct node {
	DataType elem;
	struct node *lchild;
	struct node *rchild;
}*BinTree;

#define manx 10000
#define xxx  -999	//此数字表示未知参数 
KeyType a[manx];	//留作输出时折半查找使用

//下面声明函数
void BinTreeInsert(BinTree *t,KeyType k);//插入函数
void InOrder(BinTree t,int i);//中序遍历二叉树
int	 BinSearch_1(int *s,int low,int high,KeyType key);	//递归
int  BinSearch_2(int *s,int low,int high,KeyType key);	//非递归 
int main()
{
	//默认值数据为10个 
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
		printf("\n二叉树中有3元素\n");
	else printf("\n二叉树中没有3元素\n");
	printf("递归查找成功\n");
	if(BinSearch_2(a,1,10,11) == 1)
		printf("二叉树中有11元素\n");
	else printf("二叉树中没有11元素\n"); 
	printf("非递归查找成功\n");
}
//函数实现
void BinTreeInsert(BinTree *t,KeyType k)//插入函数
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
void InOrder(BinTree t,int i)//中序遍历二叉树
{
	if(t != NULL)
	{
		InOrder(t->lchild,i);
		Visit(t->elem.key);
		a[i++] = t->elem.key;
		InOrder(t->rchild,i);
	}
}
int	 BinSearch_1(int *s,int low,int high,KeyType key)	//递归
{
	/*返回0表示查找失败，返回1表示查找成功*/
	int middle = ( low + high ) / 2;	
	if(low > high)	return 0;
	else if(key == s[middle])	return 1;
	else if(key > s[middle])
		return (BinSearch_1(s,middle + 1,high,key));
	else	return (BinSearch_1(s,low,middle - 1,key));
}
int  BinSearch_2(int *s,int low,int high,KeyType key)	//非递归 
{
	/*返回0表示查找失败，返回1表示查找成功*/
	int middle = ( low + high ) / 2;
	while(low > high)
	{
		if(s[middle] == key)	return 1;
		else if(s[middle] > key) low = middle + 1;
		else high = middle - 1;
	}
	return 0;
}
