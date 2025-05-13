#include "def.h"
status CreateBiTree(BiTree &T, TElemType definition[]) 
{
    static int idx = 0;
    static int keys[1000] = {0}; // 用于记录已出现的key
    static int key_cnt = 0;

    TElemType e = definition[idx++];

    if (e.key == 0 || e.key == -1) {
        T = NULL;
        return OK;
    }

    // 检查关键字唯一性（0/null不计入）
    for (int i = 0; i < key_cnt; i++) {
        if (keys[i] == e.key) {
            return ERROR;
        }
    }
    keys[key_cnt++] = e.key;

    T = (BiTree)malloc(sizeof(BiTNode));
    if (!T) return OVERFLOW;
    T->data = e;

    if (CreateBiTree(T->lchild, definition) == ERROR) return ERROR;
    if (CreateBiTree(T->rchild, definition) == ERROR) return ERROR;
    return OK;
}
void DestroyBiTree(BiTree &T) {
    if (T) {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
    }
}
status ClearBiTree(BiTree &T)
{
    if (T) {
        ClearBiTree(T->lchild);
        ClearBiTree(T->rchild);
        free(T);
        T=NULL;
    }
    return OK;
}
status BiTreeDepth(BiTree T)
{
    if (T==NULL) return 0;
    else {
        int l=BiTreeDepth(T->lchild);
        int r=BiTreeDepth(T->rchild);
        return (l>r)?(l+1):(r+1);
    }
}
BiTNode *LocateNode(BiTree T, int e)
{
    if (T==NULL) return NULL;
    if (T->data.key==e) return T;
    BiTNode *p=LocateNode(T->lchild,e);
    if (p) return p;
    p=LocateNode(T->rchild,e);
    return p;
}
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
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild,visit);
        PreOrderTraverse(T->rchild,visit);
    }
    return OK;
}
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree)){
    if (T)
    {
        InOrderTraverse(T->lchild,visit);
        visit(T);
        InOrderTraverse(T->rchild,visit);
    }
    return OK;
}
status PostOrderTraverse(BiTree T,void (*visit)(BiTree)){
    if (T)
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        visit(T);
    }
    return OK;
}
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