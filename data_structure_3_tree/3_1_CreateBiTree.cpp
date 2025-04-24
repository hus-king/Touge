#include "def.h"
status CreateBiTree(BiTree &T, TElemType definition[]) 
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
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
TElemType definition[100];
BiTree T;
int ans,i=0;
do {
	scanf("%d%s",&definition[i].key,definition[i].others);
} while (definition[i++].key!=-1);
ans=CreateBiTree(T,definition);
if (ans==OK)
{
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
}
else printf("关键字不唯一");
return 1;
}
//测试输入 1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null
//预期输出
// 1,a 2,b 3,c 4,d 5,e
// 2,b 1,a 4,d 3,c 5,e