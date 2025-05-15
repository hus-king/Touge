#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 初始化链表
status InitList(LinkList &L) {
    if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) return OVERFLOW;
    L->next = NULL;
    return OK;
}

// 销毁链表
status DestroyList(LinkList &L) {
    if (L==NULL) return INFEASIBLE;
    LinkList p,q;
    p=L->next;
    free(L);
    while (p!=NULL) {
        q=p->next;
        free(p);
        p=q;
    }
    L=NULL;
    return OK;
}

// 清空链表
status ClearList(LinkList &L) {
    if (L==NULL) return INFEASIBLE;
    LinkList p,q;
    p=L->next;
    while (p!=NULL) {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
    return OK;
}

// 判空链表
status ListEmpty(LinkList L) {
    if (L==NULL) return INFEASIBLE;
    if (L->next==NULL) return OK;
    else return ERROR;
}

// 求链表长度
status ListLength(LinkList L) {
    if (L==NULL) return INFEASIBLE;
    int len=0;
    LNode *p=L->next;
    while (p) {
        len++;
        p=p->next;
    }
    return len;
}

// 获取第i个元素
status GetElem(LinkList L,int i,ElemType &e) {
    if (L==NULL) return INFEASIBLE;
    if (i<1) return ERROR;
    LNode *p=L->next;
    int j=1;
    while (p && j<i) {
        p=p->next;
        j++;
    }
    if (j!=i) return ERROR;
    e=p->data;
    return OK;
}

// 查找元素e的位置
status LocateElem(LinkList L,ElemType e) {
    if (L==NULL) return INFEASIBLE;
    int i=1;
    LNode *p=L->next;
    while (p) {
        if (p->data==e) return i;
        p=p->next;
        i++;
    }
    return ERROR;
}

// 查找元素e的前驱
status PriorElem(LinkList L,ElemType e,int &pre) {
    if (L==NULL) return INFEASIBLE;
    if (L->next==NULL) return ERROR;
    LNode *p=L->next;
    int j=1;
    while (p && p->data!=e) {
        pre=p->data;
        p=p->next;
        j++;
    }
    if (j==1 || p==NULL) return ERROR;
    return OK;
}

// 查找元素e的后继
status NextElem(LinkList L,ElemType e,int &next) {
    if (L==NULL) return INFEASIBLE;
    LNode *p=L->next;
    while (p && p->data!=e) {
        p=p->next;
    }
    if (p==NULL || p->next==NULL) return ERROR;
    next=p->next->data;
    return OK;
}

// 在第i个位置插入元素e
status ListInsert(LinkList &L, int i, ElemType e) {
    if (L == NULL) return INFEASIBLE;
    if (i < 1) return ERROR;
    LNode *p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j != i - 1) return ERROR;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (!s) return ERROR;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 删除第i个元素
status ListDelete(LinkList &L,int i,ElemType &e) {
    if (L==NULL) return INFEASIBLE;
    if (i<1) return ERROR;
    LNode *p=L,*q;
    int j=0;
    while (p && j<i-1) {
        p=p->next;
        j++;
    }
    if (!p || j!=i-1) return ERROR;
    q=p->next;
    if (!q) return ERROR;
    e=q->data;
    p->next=q->next;
    free(q);
    return OK;
}

// 遍历链表
status ListTraverse(LinkList L) {
    if (L==NULL) return INFEASIBLE;
    LNode *p=L->next;
    while (p) {
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}

// 保存链表到文件
status SaveList(LinkList L,char FileName[]) {
    if (L==NULL) return INFEASIBLE;
    FILE *fp=fopen(FileName,"w");
    if (!fp) return ERROR;
    LNode *p=L->next;
    while (p) {
        fprintf(fp,"%d ",p->data);
        p=p->next;
    }
    fclose(fp);
    return OK;
}

// 从文件加载链表
status LoadList(LinkList &L,char FileName[]) {
    if (L) DestroyList(L);
    FILE *fp=fopen(FileName,"r");
    if (!fp) return ERROR;
    L=(LinkList)malloc(sizeof(LNode));
    if (!L) return OVERFLOW;
    L->next=NULL;
    LNode *p=L;
    int data;
    while (fscanf(fp,"%d",&data)==1) {
        LNode *s=(LNode*)malloc(sizeof(LNode));
        if (!s) return OVERFLOW;
        s->data=data;
        s->next=NULL;
        p->next=s;
        p=s;
    }
    fclose(fp);
    return OK;
}

// 链表翻转
status reverseList(LinkList L) {
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    LNode *prev = NULL, *curr = L->next, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
    return OK;
}

// 删除倒数第n个结点
status RemoveNthFromEnd(LinkList L, int n) {
    if (L == NULL || L->next == NULL || n < 1) return INFEASIBLE;
    LNode *fast = L, *slow = L;
    for (int i = 0; i < n; ++i) {
        if (fast->next) fast = fast->next;
        else return ERROR;
    }
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    LNode *toDel = slow->next;
    if (!toDel) return ERROR;
    slow->next = toDel->next;
    free(toDel);
    return OK;
}

// 链表排序
status sortList(LinkList L) {
    if (L == NULL || L->next == NULL) return INFEASIBLE;
    LNode *p, *q;
    for (p = L->next; p; p = p->next) {
        for (q = p->next; q; q = q->next) {
            if (p->data > q->data) {
                ElemType tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
    return OK;
}

// 快速建表（从输入流快速建表，以回车为结束）
void QuickCreateList(LinkList &L) {
    if (L) ClearList(L);
    else InitList(L);
    printf("请输入元素（以回车结束）：");
    int x;
    char ch;
    LNode *tail = L;
    while (1) {
        int ret = scanf("%d", &x);
        ch = getchar();
        if (ret != 1 || ch == '\n') break;
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        s->next = NULL;
        tail->next = s;
        tail = s;
        if (ch == '\n') break;
    }
}

// 多表管理结构体
typedef struct {
    struct {
        char name[30]; // 链表名称
        LinkList L;    // 链表
    } elem[10];        // 最多管理 10 个链表
    int length;        // 当前管理的链表数量
} LISTS;

// 查找链表，返回位置（1开始），未找到返回0
int LocateList(LISTS &Lists, const char name[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, name) == 0)
            return i + 1;
    }
    return 0;
}

// 添加链表
status AddList(LISTS &Lists, const char name[]) {
    if (Lists.length >= 10) return ERROR;
    strcpy(Lists.elem[Lists.length].name, name);
    Lists.elem[Lists.length].L = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}

// 移除链表
status RemoveList(LISTS &Lists, const char name[]) {
    int pos = LocateList(Lists, name);
    if (pos == 0) return ERROR;
    DestroyList(Lists.elem[pos - 1].L);
    for (int i = pos; i < Lists.length; i++) {
        Lists.elem[i - 1] = Lists.elem[i];
    }
    Lists.length--;
    return OK;
}

// 单表操作菜单
void SingleListMenu(LinkList &L) {
    int op = 1;
    while (op) {
        system("clear");
        printf("\n\n");
        printf("      单链表操作菜单\n");
        printf("-------------------------------------------------\n");
        printf(" 1. 初始化表        10. 插入元素\n");
        printf(" 2. 销毁表          11. 删除元素\n");
        printf(" 3. 清空表          12. 遍历表\n");
        printf(" 4. 判空表          13. 链表翻转\n");
        printf(" 5. 求表长          14. 删除倒数第n个\n");
        printf(" 6. 获取元素        15. 保存到文件\n");
        printf(" 7. 查找元素位置    16. 从文件加载\n");
        printf(" 8. 查找前驱元素    17. 链表排序\n");
        printf(" 9. 查找后继元素    18. 快速建表\n");
        printf(" 0. 返回上级\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~18]:");
        scanf("%d", &op);
        int i, ret, e, pre, next, n;
        char filename[100];
        switch (op) {
            case 1:
                if (InitList(L) == OK) printf("链表创建成功！\n");
                else printf("链表创建失败！\n");
                getchar(); getchar();
                break;
            case 2:
                if (DestroyList(L) == OK) printf("链表销毁成功！\n");
                else printf("链表销毁失败！\n");
                getchar(); getchar();
                break;
            case 3:
                if (ClearList(L) == OK) printf("链表清空成功！\n");
                else printf("链表清空失败！\n");
                getchar(); getchar();
                break;
            case 4:
                ret = ListEmpty(L);
                if (ret == OK) printf("链表为空！\n");
                else if (ret == ERROR) printf("链表不空！\n");
                else printf("链表不存在！\n");
                getchar(); getchar();
                break;
            case 5:
                ret = ListLength(L);
                if (ret >= 0) printf("链表长度为：%d\n", ret);
                else printf("链表不存在！\n");
                getchar(); getchar();
                break;
            case 6:
                printf("请输入要获取的元素位置i：");
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK) printf("第%d个元素为：%d\n", i, e);
                else printf("获取元素失败！\n");
                getchar(); getchar();
                break;
            case 7:
                printf("请输入要查找的元素值e：");
                scanf("%d", &e);
                ret = LocateElem(L, e);
                if (ret > 0) printf("元素%d在链表中的位置为：%d\n", e, ret);
                else if (ret == ERROR) printf("未找到该元素！\n");
                else printf("链表不存在！\n");
                getchar(); getchar();
                break;
            case 8:
                printf("请输入要查找前驱的元素值：");
                scanf("%d", &e);
                if (PriorElem(L, e, pre) == OK) printf("元素%d的前驱为：%d\n", e, pre);
                else printf("查找前驱失败！\n");
                getchar(); getchar();
                break;
            case 9:
                printf("请输入要查找后继的元素值：");
                scanf("%d", &e);
                if (NextElem(L, e, next) == OK) printf("元素%d的后继为：%d\n", e, next);
                else printf("查找后继失败！\n");
                getchar(); getchar();
                break;
            case 10:
                printf("请输入插入位置i和元素值e：");
                scanf("%d%d", &i, &e);
                if (ListInsert(L, i, e) == OK) printf("插入成功！\n");
                else printf("插入失败！\n");
                getchar(); getchar();
                break;
            case 11:
                printf("请输入要删除的元素位置i：");
                scanf("%d", &i);
                if (ListDelete(L, i, e) == OK) printf("删除成功，被删元素为：%d\n", e);
                else printf("删除失败！\n");
                getchar(); getchar();
                break;
            case 12:
                printf("\n-----------所有元素-----------------------\n");
                if (ListTraverse(L) == OK) printf("\n------------------ end ------------------------\n");
                else printf("链表不存在或为空！\n");
                getchar(); getchar();
                break;
            case 13:
                if (reverseList(L) == OK) printf("链表翻转成功！\n");
                else printf("链表翻转失败！\n");
                getchar(); getchar();
                break;
            case 14:
                printf("请输入要删除的倒数第n个节点n：");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("删除成功！\n");
                else printf("删除失败！\n");
                getchar(); getchar();
                break;
            case 15:
                printf("请输入要保存的文件名：");
                scanf("%s", filename);
                if (SaveList(L, filename) == OK) printf("保存成功！\n");
                else printf("保存失败！\n");
                getchar(); getchar();
                break;
            case 16:
                printf("请输入要加载的文件名：");
                scanf("%s", filename);
                if (LoadList(L, filename) == OK) printf("加载成功！\n");
                else printf("加载失败！\n");
                getchar(); getchar();
                break;
            case 17:
                if (sortList(L) == OK) printf("排序成功！\n");
                else printf("排序失败！\n");
                getchar(); getchar();
                break;
            case 18:
                QuickCreateList(L);
                printf("快速建表完成！\n");
                getchar();
                break;
            case 0:
                break;
        }
    }
}

// 多表管理主函数
int main() {
    LISTS Lists;
    Lists.length = 0;
    int op = 1;

    while (op) {
        system("clear");
        printf("\n\n");
        printf("      多个链表管理菜单 \n");
        printf("-------------------------------------------------\n");
        printf("1. 添加链表       4. 显示所有链表\n");
        printf("2. 移除链表       5. 操作单个链表\n");
        printf("3. 查找链表       0. 退出\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char name[30];
                printf("请输入新链表的名称：");
                scanf("%s", name);
                if (LocateList(Lists, name) > 0) {
                    printf("链表名称 '%s' 已存在，添加失败！\n", name);
                } else {
                    if (AddList(Lists, name) == OK) {
                        printf("链表 '%s' 添加成功！\n", name);
                    } else {
                        printf("链表添加失败！\n");
                    }
                }
                getchar(); getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("请输入要移除的链表名称：");
                scanf("%s", name);
                if (RemoveList(Lists, name) == OK) printf("链表 '%s' 移除成功！\n", name);
                else printf("链表移除失败！\n");
                getchar(); getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("请输入要查找的链表名称：");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) printf("链表 '%s' 的位置为：%d\n", name, pos);
                else printf("未找到链表 '%s'！\n", name);
                getchar(); getchar();
                break;
            }
            case 4: {
                if (Lists.length == 0) {
                    printf("当前没有链表！\n");
                } else {
                    printf("当前链表列表：\n");
                    for (int i = 0; i < Lists.length; i++) {
                        printf("  %d. %s\n", i + 1, Lists.elem[i].name);
                    }
                }
                getchar(); getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("请输入要操作的链表名称：");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) {
                    printf("已切换到链表 '%s'！\n", name);
                    SingleListMenu(Lists.elem[pos - 1].L);
                } else {
                    printf("未找到链表 '%s'！\n", name);
                    getchar();
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
