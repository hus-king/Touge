#include "def.h"
BiTNode *LocateNode(BiTree T, int e)
{
    if (T==NULL) return NULL;
    if (T->data.key==e) return T;
    BiTNode *p=LocateNode(T->lchild,e);
    if (p) return p;
    p=LocateNode(T->rchild,e);
    return p;
}

// 	scanf("%d%d%s",&key,&e.key,e.others);
// ans=Assign(T,key,e);
// 3 2 new
status Assign(BiTree &T,KeyType e,TElemType value){
    BiTNode *p=LocateNode(T,e);
    if (p==NULL) return ERROR;
    BiTNode *q=LocateNode(T,value.key);
    if (q && q!=p) return ERROR; // 不能有相同的关键字
    TElemType old=p->data;
    p->data=value;
    value=old;
    return OK;
}
typedef struct {
    int pos;
    TElemType data;
} DEF;
status CreateBiTree(BiTree &T,DEF definition[])
{
    int i=0,j;
    static BiTNode *p[100];
    while (j=definition[i].pos)
    {
    	p[j]=(BiTNode *)malloc(sizeof(BiTNode));
        p[j]->data=definition[i].data;
        p[j]->lchild=NULL;
        p[j]->rchild=NULL;
        if (j!=1)
       	    if (j%2)   p[j/2]->rchild=p[j];  
       	    else      p[j/2]->lchild=p[j];
        i++;
    }
    T=p[1];
    return OK;
}

void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf(" %d,%s",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf(" %d,%s",T->data.key,T->data.others);
        InOrderTraverse(T->rchild);
    }
}
//1 1 a  2 2 b  3 3 c     6  4 d   7  5 e   0  0 null 3 2 new
int main()
{
DEF definition[100];
BiTree T;
TElemType e;
int ans,i=0,key;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
	scanf("%d%d%s",&key,&e.key,e.others);
	ans=Assign(T,key,e);
	if (ans==OK)
	{
	    PreOrderTraverse(T);
	    printf("\n");
	    InOrderTraverse(T);
	}
	else printf("赋值操作失败");
	return 1;
}
