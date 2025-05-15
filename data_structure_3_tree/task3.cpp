#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <cstring>
#include "my.h"
#define MAX_TREE_NUM 10
// ========== 辅助：层序遍历 ==========
typedef struct QueueNode {
    BiTree data;
    struct QueueNode* next;
} QueueNode, *QueuePtr;

typedef struct {
    QueuePtr front, rear;
} LinkQueue;

void InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QueueNode));
    Q.front->next = NULL;
}
int QueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}
void EnQueue(LinkQueue &Q, BiTree x) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QueueNode));
    p->data = x; p->next = NULL;
    Q.rear->next = p; Q.rear = p;
}
int DeQueue(LinkQueue &Q, BiTree &x) {
    if (Q.front == Q.rear) return 0;
    QueuePtr p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    free(p);
    return 1;
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T) return OK;
    LinkQueue Q; InitQueue(Q);
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        BiTree p;
        DeQueue(Q, p);
        visit(p);
        if (p->lchild) EnQueue(Q, p->lchild);
        if (p->rchild) EnQueue(Q, p->rchild);
    }
    return OK;
}

// 15. 最大路径和（根到叶最大路径和）
int MaxPathSum(BiTree T) {
    if (!T) return 0;
    int l = MaxPathSum(T->lchild);
    int r = MaxPathSum(T->rchild);
    // 叶子节点
    if (!T->lchild && !T->rchild) return T->data.key;
    // 只有左或右
    if (!T->lchild) return r + T->data.key;
    if (!T->rchild) return l + T->data.key;
    // 两边都有
    return (l > r ? l : r) + T->data.key;
}

// 16. 最近公共祖先
BiTNode* LowestCommonAncestor(BiTree T, int e1, int e2) {
    if (!T) return NULL;
    if (T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if (left && right) return T;
    return left ? left : right;
}

// 17. 翻转二叉树
void InvertTree(BiTree T) {
    if (!T) return;
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

// 19. 直观打印二叉树
void PrintTree(BiTree T, int depth = 0, char prefix = ' ') {
    if (!T) return;
    PrintTree(T->rchild, depth + 1, '/');
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%c%d(%s)\n", prefix, T->data.key, T->data.others);
    PrintTree(T->lchild, depth + 1, '\\');
}

// ========== 多二叉树管理结构体 ==========
typedef struct {
    struct {
        char name[30]; // 二叉树名称
        BiTree T;      // 二叉树指针
    } elem[MAX_TREE_NUM];
    int length; // 当前管理的二叉树数量
} TREES;
// 查找二叉树，返回位置（1开始），未找到返回0
int LocateTree(TREES &Trees, const char name[]) {
    for (int i = 0; i < Trees.length; i++) {
        if (strcmp(Trees.elem[i].name, name) == 0)
            return i + 1;
    }
    return 0;
}

// 添加二叉树
status AddTree(TREES &Trees, const char name[]) {
    if (Trees.length >= MAX_TREE_NUM) return ERROR;
    strcpy(Trees.elem[Trees.length].name, name);
    Trees.elem[Trees.length].T = NULL;
    Trees.length++;
    return OK;
}

// 移除二叉树
status RemoveTree(TREES &Trees, const char name[]) {
    int pos = LocateTree(Trees, name);
    if (pos == 0) return ERROR;
    if (Trees.elem[pos - 1].T) DestroyBiTree(Trees.elem[pos - 1].T);
    for (int i = pos; i < Trees.length; i++) {
        Trees.elem[i - 1] = Trees.elem[i];
    }
    Trees.length--;
    return OK;
}

// 单棵二叉树操作菜单
void SingleTreeMenu(BiTree &T) {
    int op = 1;
    while (op) {
        system("clear");
        printf("\n\n");
        printf("      单棵二叉树操作菜单\n");
        printf("-------------------------------------------------\n");
        printf(" 1. 创建二叉树       10. 删除结点\n");
        printf(" 2. 销毁二叉树       11. 前序遍历\n");
        printf(" 3. 清空二叉树       12. 中序遍历\n");
        printf(" 4. 判空二叉树       13. 后序遍历\n");
        printf(" 5. 求二叉树深度     14. 层序遍历\n");
        printf(" 6. 查找结点         15. 最大路径和\n");
        printf(" 7. 结点赋值         17. 翻转二叉树\n");
        printf(" 8. 获得兄弟结点     16. 最近公共祖先\n");
        printf(" 9. 插入结点         18. 保存/加载二叉树\n");
        printf(" 0. 返回上级         19. 直观打印二叉树\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~19]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: { // 创建二叉树
                TElemType definition[100];
                int i = 0;
                printf("请一次性输入结点的key和others(以 -1 null 结束)\n");
                while (1) {
                    scanf("%d", &definition[i].key);
                    scanf("%s", definition[i].others);
                    if (definition[i].key == -1) break;
                    i++;
                }
                // 补充最后一个 -1 null
                i++;
                int ans = CreateBiTree(T, definition);
                if (ans == OK) {
                    printf("二叉树创建成功！\n");
                } else {
                    printf("二叉树创建失败（关键字不唯一）！\n");
                }
                getchar();
                break;
            }
            case 2: { // 销毁二叉树
                if (T) {
                    DestroyBiTree(T);
                    T = NULL;
                    printf("二叉树销毁成功！\n");
                } else printf("二叉树不存在！\n");
                getchar();
                break;
            }
            case 3: { // 清空二叉树
                if (T) {
                    ClearBiTree(T);
                    printf("二叉树已清空！\n");
                } else printf("二叉树不存在！\n");
                getchar();
                break;
            }
            case 4: { // 判空
                if (!T) printf("二叉树为空！\n");
                else printf("二叉树不空！\n");
                getchar();
                break;
            }
            case 5: { // 深度
                if (!T) printf("二叉树不存在！\n");
                else printf("二叉树深度为：%d\n", BiTreeDepth(T));
                getchar();
                break;
            }
            case 6: { // 查找结点
                int key;
                printf("请输入要查找的关键字：");
                scanf("%d", &key);
                BiTNode *p = LocateNode(T, key);
                if (p) printf("找到结点：key=%d, others=%s\n", p->data.key, p->data.others);
                else printf("未找到该结点！\n");
                getchar();
                getchar();
                break;
            }
            case 7: { // 结点赋值
                int key;
                TElemType val;
                printf("请输入要赋值的结点关键字：");
                scanf("%d", &key);
                printf("请输入新值 key: ");
                scanf("%d", &val.key);
                printf("请输入新值 others: ");
                scanf("%s", val.others);
                if (Assign(T, key, val) == OK) printf("赋值成功！\n");
                else printf("赋值失败（关键字冲突或不存在）！\n");
                getchar();
                getchar();
                break;
            }
            case 8: { // 获得兄弟结点
                int key;
                printf("请输入要查找兄弟的结点关键字：");
                scanf("%d", &key);
                BiTNode *sib = GetSibling(T, key);
                if (sib) printf("兄弟结点：key=%d, others=%s\n", sib->data.key, sib->data.others);
                else printf("无兄弟结点！\n");
                getchar();
                getchar();
                break;
            }
            case 9: { // 插入结点
                int e, LR;
                TElemType val;
                printf("请输入父结点：");
                scanf("%d", &e);
                printf("请输入插入方向（0左，1右）：");
                scanf("%d", &LR);
                printf("请输入新结点 key: ");
                scanf("%d", &val.key);
                printf("请输入新结点 others: ");
                scanf("%s", val.others);
                if (InsertNode(T, e, LR, val) == OK) printf("插入成功！\n");
                else printf("插入失败（关键字冲突或父结点不存在）！\n");
                getchar();getchar();
                break;
            }
            case 10: { // 删除结点
                int key;
                printf("请输入要删除的结点关键字：");
                scanf("%d", &key);
                if (DeleteNode(T, key) == OK) printf("删除成功！\n");
                else printf("删除失败（结点不存在）！\n");
                getchar();getchar();
                break;
            }
            case 11: { // 前序遍历
                printf("前序遍历：");
                PreOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 12: { // 中序遍历
                printf("中序遍历：");
                InOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 13: { // 后序遍历
                printf("后序遍历：");
                PostOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 14: { // 层序遍历
                printf("层序遍历：");
                LevelOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 15: { // 最大路径和
                if (!T) printf("二叉树不存在！\n");
                else printf("根到叶最大路径和为：%d\n", MaxPathSum(T));
                getchar();
                break;
            }
            case 16: { // 最近公共祖先
                int e1, e2;
                printf("请输入两个结点的关键字：");
                scanf("%d%d", &e1, &e2);
                BiTNode* lca = LowestCommonAncestor(T, e1, e2);
                if (lca)
                    printf("最近公共祖先：key=%d, others=%s\n", lca->data.key, lca->data.others);
                else
                    printf("未找到最近公共祖先！\n");
                getchar();
                getchar();
                break;
            }
            case 17: { // 翻转二叉树
                if (!T) printf("二叉树不存在！\n");
                else {
                    InvertTree(T);
                    printf("二叉树已翻转！\n");
                }
                getchar();
                break;
            }
            case 18: { // 保存/加载二叉树
                int subop;
                char filename[100];
                printf("1. 保存二叉树到文件\n2. 从文件加载二叉树\n请选择：");
                scanf("%d", &subop);
                printf("请输入文件名：");
                scanf("%s", filename);
                if (subop == 1) {
                    if (SaveBiTree(T, filename) == OK)
                        printf("保存成功！\n");
                    else
                        printf("保存失败！\n");
                } else if (subop == 2) {
                    if (LoadBiTree(T, filename) == OK)
                        printf("加载成功！\n");
                    else
                        printf("加载失败！\n");
                } else {
                    printf("无效操作！\n");
                }
                getchar();
                break;
            }
            case 19: { // 直观打印二叉树
                if (!T) {
                    printf("二叉树不存在！\n");
                } else {
                    printf("二叉树结构如下（右高左低）：\n");
                    PrintTree(T);
                }
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

// 多树管理主函数
int main() {
    TREES Trees;
    Trees.length = 0;
    int op = 1;
    while (op) {
        system("clear");
        printf("\n\n");
        printf("      多个二叉树管理菜单 \n");
        printf("-------------------------------------------------\n");
        printf("1. 添加二叉树       4. 显示所有二叉树\n");
        printf("2. 移除二叉树       5. 操作单个二叉树\n");
        printf("3. 查找二叉树       0. 退出\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: {
                char name[30];
                printf("请输入新二叉树的名称：");
                scanf("%s", name);
                if (LocateTree(Trees, name) > 0) {
                    printf("二叉树名称 '%s' 已存在，添加失败！\n", name);
                } else {
                    if (AddTree(Trees, name) == OK) {
                        printf("二叉树 '%s' 添加成功！\n", name);
                    } else {
                        printf("二叉树添加失败！\n");
                    }
                }
                getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("请输入要移除的二叉树名称：");
                scanf("%s", name);
                if (RemoveTree(Trees, name) == OK) printf("二叉树 '%s' 移除成功！\n", name);
                else printf("二叉树移除失败！\n");
                getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("请输入要查找的二叉树名称：");
                scanf("%s", name);
                int pos = LocateTree(Trees, name);
                if (pos > 0) printf("二叉树 '%s' 的位置为：%d\n", name, pos);
                else printf("未找到二叉树 '%s'！\n", name);
                getchar();
                break;
            }
            case 4: {
                if (Trees.length == 0) {
                    printf("当前没有二叉树！\n");
                } else {
                    printf("当前二叉树列表：\n");
                    for (int i = 0; i < Trees.length; i++) {
                        printf("  %d. %s\n", i + 1, Trees.elem[i].name);
                    }
                }
                getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("请输入要操作的二叉树名称：");
                scanf("%s", name);
                int pos = LocateTree(Trees, name);
                if (pos > 0) {
                    printf("已切换到二叉树 '%s'！\n", name);
                    SingleTreeMenu(Trees.elem[pos - 1].T);
                } else {
                    printf("未找到二叉树 '%s'！\n", name);
                }
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
