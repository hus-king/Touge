#include "def.h"
BiTNode *GetSibling(BiTree T, int e)
{
    if (T==NULL) return NULL;
    if (T->lchild && T->lchild->data.key==e) return T->rchild;
    if (T->rchild && T->rchild->data.key==e) return T->lchild;
    BiTNode *p=GetSibling(T->lchild,e);
    if (p) return p;
    p=GetSibling(T->rchild,e);
    return p;
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

int main()
{
DEF definition[100];
BiTree T;
int ans,i=0,e;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
	scanf("%d",&e);
	BiTNode *p=GetSibling(T,e);
	if(p) printf("%d,%s",p->data.key,p->data.others);
	else printf("无兄弟结点");
	return 1;
}
