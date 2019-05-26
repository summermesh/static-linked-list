// 静态链表

// 定义
#define MAXSIZE 1000
typedef struct
{
	int data;
	int cur; // 游标
}Component,StaticLinkList[MAXSIZE];

// 初始化
Status InitList(StaticLinkList space)
{
	for(int i=0;i<MAXSIZE-1;i++)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
	return true;
}

// 插入
int Malloc_SLL(StaticLinkList space)
{
	int i=space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return i;
}

// 在L中第i个元素之前插入新的数据元素e
Status ListInsert(StaticLinkList L,int i, int e)
{
	int j,k,l;
	k=MAXSIZE-1;
	if(i<1||ListLength(L)+1)
		return false;
	j=malloc_SSL(L);
	if(j)
	{
		L[j].data=e;
		for(l=1;l<=i-1;l++)
			k=L[k].cur;
		L[j].cur=L[k].cur;
		L[k].cur=j;
		return true;
	}
	return false;
}

// 删除
Status ListDelete(StaticLinkList L,int i)
{
	int j,k;
	if(i<1||i>ListLength(L))
		return false;
	k=MAXSIZE-1;
	for(j=1;j<=i-1;j++)
		k=L[k].cur;
	j=L[k].cur;
	L[k].cur=L[j].cur;
	Free_SSL(L,j);
	return true;
}