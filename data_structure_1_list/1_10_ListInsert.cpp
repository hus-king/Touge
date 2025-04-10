#include "def.h"
status ListInsert(SqList &L,int i,ElemType e) //在第i个位置插入元素e
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能插入
    if (i<1 || i>L.length+1) return ERROR; //i不合法
    if (L.length>=L.listsize) { //空间不足，申请扩展
        ElemType *newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType)); //申请扩展空间
        if (!newbase) return OVERFLOW; //申请失败
        L.elem=newbase; //扩展成功，更新基址
        L.listsize+=LISTINCREMENT; //更新线性表的空间容量
    }
    ElemType *q=&L.elem[i-1]; //指向第i个元素的位置
    for (ElemType *p=&L.elem[L.length-1]; p>=q; p--) *(p+1)=*p; //将第i个元素及其后面的元素后移一位
    *q=e; //插入新元素e
    L.length++; //线性表长度加1
    return OK; //插入成功
}
int main()
{
SqList L;
int f,i,j,e;
scanf("%d",&f);
if (!f)
	{
	    L.elem=NULL;
        j=ListInsert(L,1,1);
        if (j==INFEASIBLE) printf("INFEASIBLE");
        else printf("不能对不存在的线性表进行插入操作！");
	}

else
     {
     L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
     L.length=0;
     L.listsize= 10;
     scanf("%d",&i);
     while (i)
     {
         L.elem[L.length++]=i;
         scanf("%d",&i);
     }
     scanf("%d%d",&i,&e);
     j=ListInsert(L,i,e);
     printf("%s\n", j==OK? "OK" : j==ERROR? "ERROR" : "OVERFLOW");
     for(i=0;i<L.length;i++)
        printf("%d ",L.elem[i]);
     }
return 1;
}
