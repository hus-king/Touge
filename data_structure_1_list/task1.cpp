/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
    ElemType * elem;
    int length;
    int listsize;
}SqList;

/* Function declarations */
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

/*--------------------------------------------*/
int main(void) {
    SqList L;  
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList    8. PriorElem\n");
        printf("    	  3. ClearList      9. NextElem \n");
        printf("    	  4. ListEmpty     10. ListInsert\n");
        printf("    	  5. ListLength    11. ListDelete\n");
        printf("    	  6. GetElem       12. ListTraverse\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~12]:");
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
            case 0:
                break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

/* Function implementations */
status InitList(SqList& L) {
    if (L.elem) return INFEASTABLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L) {
    if (!L.elem) return INFEASTABLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

status ClearList(SqList& L) {
    if (!L.elem) return INFEASTABLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L) {
    if (!L.elem) return INFEASTABLE;
    return L.length == 0 ? OK : ERROR;
}

int ListLength(SqList L) {
    if (!L.elem) return INFEASTABLE;
    return L.length;
}

status GetElem(SqList L, int i, ElemType& e) {
    if (!L.elem) return INFEASTABLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

status LocateElem(SqList L, ElemType e) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}

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

status ListTraverse(SqList L) {
    if (!L.elem) return INFEASTABLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

