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
status InsertNode(BiTree &T, int e, int LR, TElemType value)
{
    BiTNode *t = LocateNode(T, value.key);
    if (t) return ERROR; // 不能有相同的关键字
    if (LR == -1) { // 插入为新根
        BiTNode *q = (BiTNode *)malloc(sizeof(BiTNode));
        q->data = value;
        q->lchild = NULL;
        q->rchild = T;
        T = q;
        return OK;
    }
    BiTNode *p = LocateNode(T, e);
    if (p == NULL) return ERROR;
    BiTNode *q = (BiTNode *)malloc(sizeof(BiTNode));
    q->data = value;
    if (LR == 0) {
        q->lchild = NULL;
        q->rchild = p->lchild;
        p->lchild = q;
    }
    else{
        q->rchild = p->rchild;
        q->lchild = NULL;
        p->rchild = q;
    }
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

int main()
{
DEF definition[100];
BiTree T;
TElemType c;
int ans,i=0,e,LR;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
	scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
	ans=InsertNode(T,e,LR,c);
	if (ans==OK)
	{
	    PreOrderTraverse(T);
	    printf("\n");
	    InOrderTraverse(T);
	}
	else printf("插入操作失败");
	return 1;
}