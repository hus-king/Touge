/* 线性表顺序结构操作系统 */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // 用于 std::sort

/*---------常量定义---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; // 数据元素类型定义

/*---------线性表结构定义---------*/
#define LIST_INIT_SIZE 100 // 初始分配空间大小
#define LISTINCREMENT  10  // 增量分配空间大小
typedef struct {  // 顺序表（顺序结构）的定义
    ElemType * elem; // 数据元素存储空间的基址
    int length;      // 当前长度
    int listsize;    // 当前分配的存储容量
} SqList;

/*---------函数声明---------*/
status InitList(SqList& L); // 初始化线性表
status DestroyList(SqList& L); // 销毁线性表
status ClearList(SqList& L); // 清空线性表
status ListEmpty(SqList L); // 判断线性表是否为空
int ListLength(SqList L); // 获取线性表长度
status GetElem(SqList L, int i, ElemType& e); // 获取线性表中第i个元素
status LocateElem(SqList L, ElemType e); // 查找元素e的位置
status PriorElem(SqList L, ElemType cur, ElemType& pre_e); // 获取元素的前驱
status NextElem(SqList L, ElemType cur, ElemType& next_e); // 获取元素的后继
status ListInsert(SqList& L, int i, ElemType e); // 在第i个位置插入元素
status ListDelete(SqList& L, int i, ElemType& e); // 删除第i个位置的元素
status ListTraverse(SqList L); // 遍历线性表
status reverseList(SqList& L); // 翻转线性表
status RemoveNthFromEnd(SqList& L, int n); // 删除倒数第n个元素
status sortList(SqList& L); // 对线性表排序
status SaveListToFile(SqList L, const char* filename); // 保存线性表到文件
status LoadListFromFile(SqList& L, const char* filename); // 从文件加载线性表

/*--------------------------------------------*/
int main(void) {
    SqList L;  
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      线性表顺序结构操作菜单 \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 初始化线性表       9. 获取元素后继\n");
        printf("    	  2. 销毁线性表       10. 插入元素\n");
        printf("    	  3. 清空线性表       11. 删除元素\n");
        printf("    	  4. 判断线性表是否为空 12. 遍历线性表\n");
        printf("    	  5. 获取线性表长度   13. 翻转线性表\n");
        printf("    	  6. 获取指定元素     14. 删除倒数第n个元素\n");
        printf("    	  7. 查找元素位置     15. 对线性表排序\n");
        printf("    	  8. 获取元素前驱     16. 保存/加载线性表\n");
        printf("    	  0. 退出\n");
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
            case 13: {
                if (reverseList(L) == OK) printf("链表翻转成功！\n");
                else printf("链表翻转失败！\n");
                getchar(); getchar();
                break;
            }
            case 14: {
                int n;
                printf("请输入要删除的倒数第 n 个节点：");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("删除成功！\n");
                else printf("删除失败！\n");
                getchar(); getchar();
                break;
            }
            case 15: {
                if (sortList(L) == OK) printf("链表排序成功！\n");
                else printf("链表排序失败！\n");
                getchar(); getchar();
                break;
            }
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
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

/* Function implementations */
// 初始化线性表
status InitList(SqList& L) {
    if (L.elem) return INFEASTABLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

// 销毁线性表
status DestroyList(SqList& L) {
    if (!L.elem) return INFEASTABLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

// 清空线性表
status ClearList(SqList& L) {
    if (!L.elem) return INFEASTABLE;
    L.length = 0;
    return OK;
}

// 判断线性表是否为空
status ListEmpty(SqList L) {
    if (!L.elem) return INFEASTABLE;
    return L.length == 0 ? OK : ERROR;
}

// 获取线性表长度
int ListLength(SqList L) {
    if (!L.elem) return INFEASTABLE;
    return L.length;
}

// 获取线性表中第 i 个元素
status GetElem(SqList L, int i, ElemType& e) {
    if (!L.elem) return INFEASTABLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

// 查找元素 e 的位置
status LocateElem(SqList L, ElemType e) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}

// 获取元素的前驱
status PriorElem(SqList L, ElemType cur, ElemType& pre_e) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == cur) {
            pre_e = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

// 获取元素的后继
status NextElem(SqList L, ElemType cur, ElemType& next_e) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == cur) {
            next_e = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

// 在第 i 个位置插入元素
status ListInsert(SqList& L, int i, ElemType e) {
    if (!L.elem) return INFEASTABLE;
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

// 删除第 i 个位置的元素
status ListDelete(SqList& L, int i, ElemType& e) {
    if (!L.elem) return INFEASTABLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    for (int j = i; j < L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return OK;
}

// 遍历线性表
status ListTraverse(SqList L) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

// 翻转线性表
status reverseList(SqList& L) {
    if (L.elem == NULL) return INFEASTABLE;
    if (L.length <= 1) return OK;
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

// 删除倒数第 n 个元素
status RemoveNthFromEnd(SqList& L, int n) {
    if (L.elem == NULL) return INFEASTABLE;
    if (n <= 0 || n > L.length) return ERROR;
    int index = L.length - n;
    ElemType e;
    return ListDelete(L, index + 1, e);
}

// 对线性表排序
status sortList(SqList& L) {
    if (L.elem == NULL) return INFEASTABLE;
    std::sort(L.elem, L.elem + L.length);
    return OK;
}

// 保存线性表到文件
status SaveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASTABLE;
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) return ERROR;
    fwrite(&L.length, sizeof(int), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}

// 从文件加载线性表
status LoadListFromFile(SqList& L, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) return ERROR;
    if (L.elem != NULL) free(L.elem);
    fread(&L.length, sizeof(int), 1, fp);
    L.elem = (ElemType*)malloc(L.length * sizeof(ElemType));
    if (L.elem == NULL) {
        fclose(fp);
        return OVERFLOW;
    }
    fread(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    L.listsize = L.length;
    return OK;
}

