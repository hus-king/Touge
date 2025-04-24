#include "def.h"
#include "ctype.h"
#include "string.h"
#define free free0
#undef free
status DeleteNode(BiTree &T, KeyType e) {
    if (T == NULL) return ERROR;
    // 如果当前节点就是要删除的节点
    if (T->data.key == e) {
        BiTNode *del = T;
        // 度为0
        if (T->lchild == NULL && T->rchild == NULL) {
            T = NULL;
        }
        // 度为1（只有右孩子）
        else if (T->lchild == NULL) {
            T = T->rchild;
        }
        // 度为1（只有左孩子）
        else if (T->rchild == NULL) {
            T = T->lchild;
        }
        // 度为2
        else {
            BiTNode *lc = T->lchild;
            BiTNode *rc = T->rchild;
            T = lc;
            // 找到左子树最右节点
            BiTNode *p = lc;
            while (p->rchild) p = p->rchild;
            p->rchild = rc;
        }
        free(del);
        return OK;
    }
    // 在左子树递归删除
    if (T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
    // 在右子树递归删除
    if (T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
    return ERROR;
}
int freed=FALSE;
KeyType e;
void free0(void *p)
{
    if (((BiTree)p)->data.key==e)
        freed=TRUE;
    memset(p,0,sizeof(BiTNode));
    free(p);
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
    int ans,i=0;
    do {
        scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(T,definition);
	scanf("%d",&e);
	ans=DeleteNode(T,e);
	if (ans==OK )
	{
		if (freed==FALSE)
        {
            printf("未正确释放空间");
            return 1;
        }
	    PreOrderTraverse(T);
	    printf("\n");
	    InOrderTraverse(T);
	}
	else printf("删除操作失败");
	return 1;
}
