#include "def.h"
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)){
    BiTree queue[100];
    int front=0,rear=0;
    if (T==NULL) return ERROR;
    queue[rear++]=T;
    while (front!=rear)
    {
        T=queue[front++];
        visit(T);
        if (T->lchild) queue[rear++]=T->lchild;
        if (T->rchild) queue[rear++]=T->rchild;
    }
    return OK;
}
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
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
int ans,i=0;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
	LevelOrderTraverse(T,visit);
	return 1;
}