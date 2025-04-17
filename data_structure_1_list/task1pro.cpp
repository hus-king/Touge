#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // 用于 std::sort
#include <unordered_map> // 用于 std::unordered_map

/*---------定义常量和类型---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100 // 初始分配空间大小
#define LISTINCREMENT  10  // 增量分配空间大小

// 顺序表（顺序结构）的定义
typedef struct {
    ElemType* elem = NULL; // 数据元素存储空间的基址
    int length;     // 当前长度
    int listsize;   // 当前分配的存储容量
} SqList;

// 线性表的管理表定义
typedef struct {
    struct {
        char name[30]; // 线性表名称
        SqList L;      // 线性表
    } elem[10];        // 最多管理 10 个线性表
    int length;        // 当前管理的线性表数量
} LISTS;

/*---------函数声明---------*/
status InitList(SqList& L); // 初始化线性表
status DestroyList(SqList& L); // 销毁线性表
status ClearList(SqList& L); // 清空线性表
status ListEmpty(SqList L); // 判断线性表是否为空
int ListLength(SqList L); // 获取线性表长度
status GetElem(SqList L, int i, ElemType& e); // 获取线性表中第 i 个元素
status LocateElem(SqList L, ElemType e); // 查找元素 e 的位置
status PriorElem(SqList L, ElemType cur, ElemType& pre_e); // 获取元素的前驱
status NextElem(SqList L, ElemType cur, ElemType& next_e); // 获取元素的后继
status ListInsert(SqList& L, int i, ElemType e); // 在第 i 个位置插入元素
status ListDelete(SqList& L, int i, ElemType& e); // 删除第 i 个位置的元素
status ListTraverse(SqList L); // 遍历线性表
status reverseList(SqList& L); // 翻转线性表
status RemoveNthFromEnd(SqList& L, int n); // 删除倒数第 n 个元素
status sortList(SqList& L); // 对线性表排序
status SaveListToFile(SqList L, const char* filename); // 保存线性表到文件
status LoadListFromFile(SqList& L, const char* filename); // 从文件加载线性表
status AddList(LISTS& Lists, char ListName[]); // 添加线性表
status RemoveList(LISTS& Lists, char ListName[]); // 移除线性表
int LocateList(LISTS Lists, char ListName[]); // 查找线性表位置
status MaxSubArray(SqList L); // 最大连续子数组和
status SubArrayNum(SqList L, int k); // 和为K的子数组

/*---------函数实现---------*/

// 初始化线性表
status InitList(SqList& L) {
    if (L.elem) return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

// 销毁线性表
status DestroyList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

// 清空线性表
status ClearList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

// 判断线性表是否为空
status ListEmpty(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length == 0 ? OK : ERROR;
}

// 获取线性表长度
int ListLength(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length;
}

// 获取线性表中第 i 个元素
status GetElem(SqList L, int i, ElemType& e) {
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

// 查找元素 e 的位置
status LocateElem(SqList L, ElemType e) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}

// 获取元素的前驱
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

// 获取元素的后继
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

// 在第 i 个位置插入元素
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

// 删除第 i 个位置的元素
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

// 遍历线性表
status ListTraverse(SqList L) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

// 翻转线性表
status reverseList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

// 删除倒数第 n 个元素
status RemoveNthFromEnd(SqList& L, int n) {
    if (!L.elem) return INFEASIBLE;
    if (n <= 0 || n > L.length) return ERROR;
    int index = L.length - n;
    ElemType e;
    return ListDelete(L, index + 1, e);
}

// 对线性表排序
status sortList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    std::sort(L.elem, L.elem + L.length);
    return OK;
}

// 保存线性表到文件
status SaveListToFile(SqList L, const char* filename) {
    if (!L.elem) return INFEASIBLE;
    FILE* fp = fopen(filename, "wb");
    if (!fp) return ERROR;
    fwrite(&L.length, sizeof(int), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}

// 从文件加载线性表
status LoadListFromFile(SqList& L, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return ERROR;
    if (L.elem) free(L.elem);
    fread(&L.length, sizeof(int), 1, fp);
    L.elem = (ElemType*)malloc(L.length * sizeof(ElemType));
    if (!L.elem) {
        fclose(fp);
        return OVERFLOW;
    }
    fread(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    L.listsize = L.length;
    return OK;
}

// 添加线性表
status AddList(LISTS& Lists, char ListName[]) {
    if (Lists.length >= 10) return ERROR; // 超过最大线性表数量限制
    strcpy(Lists.elem[Lists.length].name, ListName); // 设置线性表名称
    if (InitList(Lists.elem[Lists.length].L) != OK) return ERROR; // 初始化线性表
    Lists.length++; // 增加线性表数量
    return OK;
}

// 移除线性表
status RemoveList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) { // 找到匹配的线性表
            DestroyList(Lists.elem[i].L); // 销毁线性表
            for (int j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1]; // 移动后续线性表
            }
            Lists.length--; // 减少线性表数量
            return OK;
        }
    }
    return ERROR; // 未找到指定名称的线性表
}

// 查找线性表位置
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            return i + 1; // 返回线性表的 1-based 索引
        }
    }
    return 0; // 未找到
}

// 最大连续子数组和
status MaxSubArray(SqList L) {
    if (!L.elem) return INFEASIBLE;
    int maxSum = L.elem[0], currentSum = L.elem[0];
    for (int i = 1; i < L.length; i++) {
        currentSum = std::max(L.elem[i], currentSum + L.elem[i]);
        maxSum = std::max(maxSum, currentSum);
    }
    printf("最大连续子数组和为：%d\n", maxSum);
    return OK;
}

// 和为K的子数组
status SubArrayNum(SqList L, int k) {
    if (!L.elem) return INFEASIBLE;
    int count = 0, sum = 0;
    std::unordered_map<int, int> prefixSum;
    prefixSum[0] = 1; // 初始化前缀和为0的情况
    for (int i = 0; i < L.length; i++) {
        sum += L.elem[i];
        if (prefixSum.find(sum - k) != prefixSum.end()) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    printf("和为%d的子数组个数为：%d\n", k, count);
    return OK;
}

/*---------单个线性表操作菜单---------*/
// 提供单个线性表的所有操作
void SingleListMenu(SqList& L) {
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("单个线性表操作菜单 \n");
        printf("-------------------------------------------------\n");
        printf("%-4d%-20s%-4d%s\n", 1, "初始化线性表", 9, "获取元素后继");
        printf("%-4d%-20s%-4d%s\n", 2, "销毁线性表", 10, "插入元素");
        printf("%-4d%-20s%-4d%s\n", 3, "清空线性表", 11, "删除元素");
        printf("%-4d%-20s%-4d%s\n", 4, "判断线性表是否为空", 12, "遍历线性表");
        printf("%-4d%-20s%-4d%s\n", 5, "获取线性表长度", 13, "最大连续子数组和");
        printf("%-4d%-20s%-4d%s\n", 6, "获取指定元素", 14, "和为K的子数组");
        printf("%-4d%-20s%-4d%s\n", 7, "查找元素位置", 15, "对线性表排序");
        printf("%-4d%-20s%-4d%s\n", 8, "获取元素前驱", 16, "保存/加载线性表");
        printf("%-4d%-20s\n",0,"退出");
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
                if (MaxSubArray(L) == OK) printf("操作成功！\n");
                else printf("操作失败！\n");
                getchar(); getchar();
                break;
            case 14: {
                int k;
                printf("请输入目标和K：");
                scanf("%d", &k);
                if (SubArrayNum(L, k) == OK) printf("操作成功！\n");
                else printf("操作失败！\n");
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
// 提供多个线性表的管理功能
int main() {
    LISTS Lists;
    Lists.length = 0; // 初始化线性表管理器
    int op = 1;

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      多个线性表管理菜单 \n");
        printf("-------------------------------------------------\n");
        printf("1. 添加线性表       4. 显示所有线性表\n");
        printf("2. 移除线性表       5. 操作单个线性表\n");
        printf("3. 查找线性表       0. 退出\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char name[30];
                printf("请输入新线性表的名称：");
                scanf("%s", name);
            
                // 检查名称是否重复
                if (LocateList(Lists, name) > 0) {
                    printf("线性表名称 '%s' 已存在，添加失败！\n", name);
                } else {
                    if (AddList(Lists, name) == OK) {
                        printf("线性表 '%s' 添加成功！\n", name);
                    } else {
                        printf("线性表添加失败！\n");
                    }
                }
            
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
                else printf("未找到线性表 '%s'！\n",name);
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
                    printf("未找到线性表 '%s'！\n",name);
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

