#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // 用于 std::sort

/*---------定义常量和类型---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct {  // 顺序表（顺序结构）的定义
    ElemType* elem;
    int length;
    int listsize;
} SqList;

typedef struct {  // 线性表的管理表定义
    struct { char name[30];
        SqList L;    
    } elem[10];
    int length;
} LISTS;

/*---------函数声明---------*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType& e);
status LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType cur, ElemType& pre_e);
status NextElem(SqList L, ElemType cur, ElemType& next_e);
status ListInsert(SqList& L, int i, ElemType e);
status ListDelete(SqList& L, int i, ElemType& e);
status ListTraverse(SqList L);
status reverseList(SqList& L);
status RemoveNthFromEnd(SqList& L, int n);
status sortList(SqList& L);
status SaveListToFile(SqList L, const char* filename);
status LoadListFromFile(SqList& L, const char* filename);
status AddList(LISTS& Lists, char ListName[]);
status RemoveList(LISTS& Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);

/*---------函数实现---------*/
status InitList(SqList& L) {
    if (L.elem) return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

status ClearList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length == 0 ? OK : ERROR;
}

int ListLength(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length;
}

status GetElem(SqList L, int i, ElemType& e) {
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

status LocateElem(SqList L, ElemType e) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}

status PriorElem(SqList L, ElemType cur, ElemType& pre_e) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == cur) {
            pre_e = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L, ElemType cur, ElemType& next_e) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == cur) {
            next_e = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

status ListInsert(SqList& L, int i, ElemType e) {
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length + 1) return ERROR;
    if (L.length >= L.listsize) {
        ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) return OVERFLOW;
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    for (int j = L.length - 1; j >= i - 1; j--) {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}

status ListDelete(SqList& L, int i, ElemType& e) {
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    for (int j = i; j < L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return OK;
}

status ListTraverse(SqList L) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

status reverseList(SqList& L) {
    if (L.elem == NULL) return INFEASIBLE; // 线性表不存在
    if (L.length <= 1) return OK;          // 长度为 0 或 1，无需翻转
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

status RemoveNthFromEnd(SqList& L, int n) {
    if (L.elem == NULL) return INFEASIBLE; // 线性表不存在
    if (n <= 0 || n > L.length) return ERROR; // n 不合法
    int index = L.length - n; // 倒数第 n 个节点的索引
    ElemType e; // 用于存储被删除的元素
    return ListDelete(L, index + 1, e); // 调用已有的删除函数
}

status sortList(SqList& L) {
    if (L.elem == NULL) return INFEASIBLE; // 线性表不存在
    std::sort(L.elem, L.elem + L.length);  // 使用 std::sort 排序
    return OK;
}

status SaveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASIBLE; // 线性表不存在
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) return ERROR; // 打开文件失败
    fwrite(&L.length, sizeof(int), 1, fp); // 写入线性表长度
    fwrite(L.elem, sizeof(ElemType), L.length, fp); // 写入线性表元素
    fclose(fp);
    return OK;
}

status LoadListFromFile(SqList& L, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) return ERROR; // 打开文件失败
    if (L.elem != NULL) free(L.elem); // 如果线性表已存在，释放原有内存
    fread(&L.length, sizeof(int), 1, fp); // 读取线性表长度
    L.elem = (ElemType*)malloc(L.length * sizeof(ElemType)); // 分配内存
    if (L.elem == NULL) {
        fclose(fp);
        return OVERFLOW; // 内存分配失败
    }
    fread(L.elem, sizeof(ElemType), L.length, fp); // 读取线性表元素
    fclose(fp);
    L.listsize = L.length; // 更新线性表容量
    return OK;
}

status AddList(LISTS& Lists, char ListName[]) {
    if (Lists.length >= 10) return OVERFLOW; // 超过最大线性表数量
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return ERROR; // 名称重复
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    if (InitList(Lists.elem[Lists.length].L) != OK) return ERROR; // 初始化失败
    Lists.length++;
    return OK;
}

status RemoveList(LISTS& Lists, char ListName[]) {
    int pos = -1;
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) return ERROR; // 未找到
    DestroyList(Lists.elem[pos].L);
    for (int i = pos; i < Lists.length - 1; i++) {
        Lists.elem[i] = Lists.elem[i + 1];
    }
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0; // 未找到
}

/*---------单个线性表操作菜单---------*/
void SingleListMenu(SqList& L) {
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       9. NextElem\n");
        printf("    	  2. DestroyList   10. ListInsert\n");
        printf("    	  3. ClearList     11. ListDelete\n");
        printf("    	  4. ListEmpty     12. ListTraverse\n");
        printf("    	  5. ListLength    13. ReverseList\n");
        printf("    	  6. GetElem       14. RemoveNth\n");
        printf("    	  7. LocateElem    15. SortList\n");
        printf("    	  8. PriorElem     16. Save/Load\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                if (InitList(L) == OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                getchar(); getchar();
                break;
            case 2:
                if (DestroyList(L) == OK) printf("线性表销毁成功！\n");
                else printf("线性表销毁失败！\n");
                getchar(); getchar();
                break;
            case 3:
                if (ClearList(L) == OK) printf("线性表清空成功！\n");
                else printf("线性表清空失败！\n");
                getchar(); getchar();
                break;
            case 4:
                if (ListEmpty(L) == OK) printf("线性表为空！\n");
                else printf("线性表不为空！\n");
                getchar(); getchar();
                break;
            case 5:
                printf("线性表长度为：%d\n", ListLength(L));
                getchar(); getchar();
                break;
            case 6: {
                int i;
                ElemType e;
                printf("请输入要获取的元素位置：");
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK) printf("第%d个元素为：%d\n", i, e);
                else printf("获取元素失败！\n");
                getchar(); getchar();
                break;
            }
            case 7: {
                ElemType e;
                printf("请输入要查找的元素值：");
                scanf("%d", &e);
                int pos = LocateElem(L, e);
                if (pos != ERROR) printf("元素%d的位置为：%d\n", e, pos);
                else printf("未找到元素！\n");
                getchar(); getchar();
                break;
            }
            case 8: {
                ElemType cur, pre;
                printf("请输入当前元素值：");
                scanf("%d", &cur);
                if (PriorElem(L, cur, pre) == OK) printf("元素%d的前驱为：%d\n", cur, pre);
                else printf("未找到前驱！\n");
                getchar(); getchar();
                break;
            }
            case 9: {
                ElemType cur, next;
                printf("请输入当前元素值：");
                scanf("%d", &cur);
                if (NextElem(L, cur, next) == OK) printf("元素%d的后继为：%d\n", cur, next);
                else printf("未找到后继！\n");
                getchar(); getchar();
                break;
            }
            case 10: {
                int i;
                ElemType e;
                printf("请输入插入位置和元素值：");
                scanf("%d %d", &i, &e);
                if (ListInsert(L, i, e) == OK) printf("插入成功！\n");
                else printf("插入失败！\n");
                getchar(); getchar();
                break;
            }
            case 11: {
                int i;
                ElemType e;
                printf("请输入要删除的元素位置：");
                scanf("%d", &i);
                if (ListDelete(L, i, e) == OK) printf("删除成功，删除的元素为：%d\n", e);
                else printf("删除失败！\n");
                getchar(); getchar();
                break;
            }
            case 12:
                if (ListTraverse(L) == OK) printf("遍历成功！\n");
                else printf("遍历失败！\n");
                getchar(); getchar();
                break;
            case 13:
                if (reverseList(L) == OK) printf("链表翻转成功！\n");
                else printf("链表翻转失败！\n");
                getchar(); getchar();
                break;
            case 14: {
                int n;
                printf("请输入要删除的倒数第 n 个节点：");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("删除成功！\n");
                else printf("删除失败！\n");
                getchar(); getchar();
                break;
            }
            case 15:
                if (sortList(L) == OK) printf("链表排序成功！\n");
                else printf("链表排序失败！\n");
                getchar(); getchar();
                break;
            case 16: {
                char filename[100];
                printf("请输入保存或加载的文件名：");
                scanf("%s", filename);
                int choice;
                printf("1. 保存到文件\n2. 从文件加载\n请选择操作：");
                scanf("%d", &choice);
                if (choice == 1) {
                    if (SaveListToFile(L, filename) == OK) printf("保存成功！\n");
                    else printf("保存失败！\n");
                } else if (choice == 2) {
                    if (LoadListFromFile(L, filename) == OK) printf("加载成功！\n");
                    else printf("加载失败！\n");
                } else {
                    printf("无效选择！\n");
                }
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

/*---------主函数---------*/
int main() {
    LISTS Lists;
    Lists.length = 0;
    int op = 1;

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Multiple Linear Table Management \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. AddList       4. ShowLists\n");
        printf("    	  2. RemoveList    5. OperateSingleList\n");
        printf("    	  3. LocateList    0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char name[30];
                printf("请输入新线性表的名称：");
                scanf("%s", name);
                if (AddList(Lists, name) == OK) printf("线性表 '%s' 添加成功！\n", name);
                else printf("线性表添加失败！\n");
                getchar(); getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("请输入要移除的线性表名称：");
                scanf("%s", name);
                if (RemoveList(Lists, name) == OK) printf("线性表 '%s' 移除成功！\n", name);
                else printf("线性表移除失败！\n");
                getchar(); getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("请输入要查找的线性表名称：");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) printf("线性表 '%s' 的位置为：%d\n", name, pos);
                else printf("未找到线性表 '%s'！\n");
                getchar(); getchar();
                break;
            }
            case 4: {
                if (Lists.length == 0) {
                    printf("当前没有线性表！\n");
                } else {
                    printf("当前线性表列表：\n");
                    for (int i = 0; i < Lists.length; i++) {
                        printf("  %d. %s\n", i + 1, Lists.elem[i].name);
                    }
                }
                getchar(); getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("请输入要操作的线性表名称：");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) {
                    printf("已切换到线性表 '%s'！\n", name);
                    SingleListMenu(Lists.elem[pos - 1].L);
                } else {
                    printf("未找到线性表 '%s'！\n");
                }
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

