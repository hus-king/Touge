#include "def.h"
#include "string.h"
#include <cstring>

// 辅助函数：递归保存节点
void saveNode(BiTree T, FILE* fp) {
    if (T == NULL) {
        fputc(0, fp);
        return;
    }
    fputc(1, fp);
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    saveNode(T->lchild, fp);
    saveNode(T->rchild, fp);
}

status SaveBiTree(BiTree T, const char FileName[]) {
    FILE* fp;
    if ((fp = fopen(FileName, "wb")) == NULL) return ERROR;
    saveNode(T, fp);
    fclose(fp);
    return OK;
}

// 辅助函数：递归加载节点
void loadNode(BiTree& T, FILE* fp) {
    int flag = fgetc(fp);
    if (flag == 0) {
        T = NULL;
        return;
    }
    T = (BiTNode*)malloc(sizeof(BiTNode));
    fread(&T->data, sizeof(TElemType), 1, fp);
    loadNode(T->lchild, fp);
    loadNode(T->rchild, fp);
}

status LoadBiTree(BiTree& T, const char FileName[]) {
    FILE* fp;
    if ((fp = fopen(FileName, "rb")) == NULL) return ERROR;
    loadNode(T, fp);
    fclose(fp);
    return OK;
}

typedef struct {
    int pos;
    TElemType data; 
} DEF;
status DestroyBiTree(BiTree &T)
{
   if (T)
   {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
   }
   return OK;
}
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
TElemType e;
int ans,i=0,key;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(T,definition);
//char FileName[20];
//strcpy( FileName,"step13/test.dat");
SaveBiTree(T,"step13/test.dat");
DestroyBiTree(T);
LoadBiTree(T,"step13/test.dat");
PreOrderTraverse(T);
printf("\n");
InOrderTraverse(T);
return 1;
}
