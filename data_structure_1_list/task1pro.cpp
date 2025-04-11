#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // ���� std::sort

/*---------���峣��������---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // ����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct {  // ˳���˳��ṹ���Ķ���
    ElemType* elem;
    int length;
    int listsize;
} SqList;

typedef struct {  // ���Ա�Ĺ������
    struct { char name[30];
        SqList L;    
    } elem[10];
    int length;
} LISTS;

/*---------��������---------*/
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

/*---------����ʵ��---------*/
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
    if (L.elem == NULL) return INFEASIBLE; // ���Ա�����
    if (L.length <= 1) return OK;          // ����Ϊ 0 �� 1�����跭ת
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

status RemoveNthFromEnd(SqList& L, int n) {
    if (L.elem == NULL) return INFEASIBLE; // ���Ա�����
    if (n <= 0 || n > L.length) return ERROR; // n ���Ϸ�
    int index = L.length - n; // ������ n ���ڵ������
    ElemType e; // ���ڴ洢��ɾ����Ԫ��
    return ListDelete(L, index + 1, e); // �������е�ɾ������
}

status sortList(SqList& L) {
    if (L.elem == NULL) return INFEASIBLE; // ���Ա�����
    std::sort(L.elem, L.elem + L.length);  // ʹ�� std::sort ����
    return OK;
}

status SaveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASIBLE; // ���Ա�����
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) return ERROR; // ���ļ�ʧ��
    fwrite(&L.length, sizeof(int), 1, fp); // д�����Ա���
    fwrite(L.elem, sizeof(ElemType), L.length, fp); // д�����Ա�Ԫ��
    fclose(fp);
    return OK;
}

status LoadListFromFile(SqList& L, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) return ERROR; // ���ļ�ʧ��
    if (L.elem != NULL) free(L.elem); // ������Ա��Ѵ��ڣ��ͷ�ԭ���ڴ�
    fread(&L.length, sizeof(int), 1, fp); // ��ȡ���Ա���
    L.elem = (ElemType*)malloc(L.length * sizeof(ElemType)); // �����ڴ�
    if (L.elem == NULL) {
        fclose(fp);
        return OVERFLOW; // �ڴ����ʧ��
    }
    fread(L.elem, sizeof(ElemType), L.length, fp); // ��ȡ���Ա�Ԫ��
    fclose(fp);
    L.listsize = L.length; // �������Ա�����
    return OK;
}

status AddList(LISTS& Lists, char ListName[]) {
    if (Lists.length >= 10) return OVERFLOW; // ����������Ա�����
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return ERROR; // �����ظ�
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    if (InitList(Lists.elem[Lists.length].L) != OK) return ERROR; // ��ʼ��ʧ��
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
    if (pos == -1) return ERROR; // δ�ҵ�
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
    return 0; // δ�ҵ�
}

/*---------�������Ա�����˵�---------*/
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
        printf("    ��ѡ����Ĳ���[0~16]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                if (InitList(L) == OK) printf("���Ա����ɹ���\n");
                else printf("���Ա���ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 2:
                if (DestroyList(L) == OK) printf("���Ա����ٳɹ���\n");
                else printf("���Ա�����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 3:
                if (ClearList(L) == OK) printf("���Ա���ճɹ���\n");
                else printf("���Ա����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 4:
                if (ListEmpty(L) == OK) printf("���Ա�Ϊ�գ�\n");
                else printf("���Ա�Ϊ�գ�\n");
                getchar(); getchar();
                break;
            case 5:
                printf("���Ա���Ϊ��%d\n", ListLength(L));
                getchar(); getchar();
                break;
            case 6: {
                int i;
                ElemType e;
                printf("������Ҫ��ȡ��Ԫ��λ�ã�");
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK) printf("��%d��Ԫ��Ϊ��%d\n", i, e);
                else printf("��ȡԪ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 7: {
                ElemType e;
                printf("������Ҫ���ҵ�Ԫ��ֵ��");
                scanf("%d", &e);
                int pos = LocateElem(L, e);
                if (pos != ERROR) printf("Ԫ��%d��λ��Ϊ��%d\n", e, pos);
                else printf("δ�ҵ�Ԫ�أ�\n");
                getchar(); getchar();
                break;
            }
            case 8: {
                ElemType cur, pre;
                printf("�����뵱ǰԪ��ֵ��");
                scanf("%d", &cur);
                if (PriorElem(L, cur, pre) == OK) printf("Ԫ��%d��ǰ��Ϊ��%d\n", cur, pre);
                else printf("δ�ҵ�ǰ����\n");
                getchar(); getchar();
                break;
            }
            case 9: {
                ElemType cur, next;
                printf("�����뵱ǰԪ��ֵ��");
                scanf("%d", &cur);
                if (NextElem(L, cur, next) == OK) printf("Ԫ��%d�ĺ��Ϊ��%d\n", cur, next);
                else printf("δ�ҵ���̣�\n");
                getchar(); getchar();
                break;
            }
            case 10: {
                int i;
                ElemType e;
                printf("���������λ�ú�Ԫ��ֵ��");
                scanf("%d %d", &i, &e);
                if (ListInsert(L, i, e) == OK) printf("����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 11: {
                int i;
                ElemType e;
                printf("������Ҫɾ����Ԫ��λ�ã�");
                scanf("%d", &i);
                if (ListDelete(L, i, e) == OK) printf("ɾ���ɹ���ɾ����Ԫ��Ϊ��%d\n", e);
                else printf("ɾ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 12:
                if (ListTraverse(L) == OK) printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 13:
                if (reverseList(L) == OK) printf("����ת�ɹ���\n");
                else printf("����תʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 14: {
                int n;
                printf("������Ҫɾ���ĵ����� n ���ڵ㣺");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("ɾ���ɹ���\n");
                else printf("ɾ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 15:
                if (sortList(L) == OK) printf("��������ɹ���\n");
                else printf("��������ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 16: {
                char filename[100];
                printf("�����뱣�����ص��ļ�����");
                scanf("%s", filename);
                int choice;
                printf("1. ���浽�ļ�\n2. ���ļ�����\n��ѡ�������");
                scanf("%d", &choice);
                if (choice == 1) {
                    if (SaveListToFile(L, filename) == OK) printf("����ɹ���\n");
                    else printf("����ʧ�ܣ�\n");
                } else if (choice == 2) {
                    if (LoadListFromFile(L, filename) == OK) printf("���سɹ���\n");
                    else printf("����ʧ�ܣ�\n");
                } else {
                    printf("��Чѡ��\n");
                }
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

/*---------������---------*/
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
        printf("    ��ѡ����Ĳ���[0~5]:");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char name[30];
                printf("�����������Ա�����ƣ�");
                scanf("%s", name);
                if (AddList(Lists, name) == OK) printf("���Ա� '%s' ��ӳɹ���\n", name);
                else printf("���Ա����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("������Ҫ�Ƴ������Ա����ƣ�");
                scanf("%s", name);
                if (RemoveList(Lists, name) == OK) printf("���Ա� '%s' �Ƴ��ɹ���\n", name);
                else printf("���Ա��Ƴ�ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("������Ҫ���ҵ����Ա����ƣ�");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) printf("���Ա� '%s' ��λ��Ϊ��%d\n", name, pos);
                else printf("δ�ҵ����Ա� '%s'��\n");
                getchar(); getchar();
                break;
            }
            case 4: {
                if (Lists.length == 0) {
                    printf("��ǰû�����Ա�\n");
                } else {
                    printf("��ǰ���Ա��б�\n");
                    for (int i = 0; i < Lists.length; i++) {
                        printf("  %d. %s\n", i + 1, Lists.elem[i].name);
                    }
                }
                getchar(); getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("������Ҫ���������Ա����ƣ�");
                scanf("%s", name);
                int pos = LocateList(Lists, name);
                if (pos > 0) {
                    printf("���л������Ա� '%s'��\n", name);
                    SingleListMenu(Lists.elem[pos - 1].L);
                } else {
                    printf("δ�ҵ����Ա� '%s'��\n");
                }
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

