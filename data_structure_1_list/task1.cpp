/* ���Ա�˳��ṹ����ϵͳ */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // ���� std::sort

/*---------��������---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; // ����Ԫ�����Ͷ���

/*---------���Ա�ṹ����---------*/
#define LIST_INIT_SIZE 100 // ��ʼ����ռ��С
#define LISTINCREMENT  10  // ��������ռ��С
typedef struct {  // ˳���˳��ṹ���Ķ���
    ElemType * elem; // ����Ԫ�ش洢�ռ�Ļ�ַ
    int length;      // ��ǰ����
    int listsize;    // ��ǰ����Ĵ洢����
} SqList;

/*---------��������---------*/
status InitList(SqList& L); // ��ʼ�����Ա�
status DestroyList(SqList& L); // �������Ա�
status ClearList(SqList& L); // ������Ա�
status ListEmpty(SqList L); // �ж����Ա��Ƿ�Ϊ��
int ListLength(SqList L); // ��ȡ���Ա���
status GetElem(SqList L, int i, ElemType& e); // ��ȡ���Ա��е�i��Ԫ��
status LocateElem(SqList L, ElemType e); // ����Ԫ��e��λ��
status PriorElem(SqList L, ElemType cur, ElemType& pre_e); // ��ȡԪ�ص�ǰ��
status NextElem(SqList L, ElemType cur, ElemType& next_e); // ��ȡԪ�صĺ��
status ListInsert(SqList& L, int i, ElemType e); // �ڵ�i��λ�ò���Ԫ��
status ListDelete(SqList& L, int i, ElemType& e); // ɾ����i��λ�õ�Ԫ��
status ListTraverse(SqList L); // �������Ա�
status reverseList(SqList& L); // ��ת���Ա�
status RemoveNthFromEnd(SqList& L, int n); // ɾ��������n��Ԫ��
status sortList(SqList& L); // �����Ա�����
status SaveListToFile(SqList L, const char* filename); // �������Ա��ļ�
status LoadListFromFile(SqList& L, const char* filename); // ���ļ��������Ա�

/*--------------------------------------------*/
int main(void) {
    SqList L;  
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      ���Ա�˳��ṹ�����˵� \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. ��ʼ�����Ա�       9. ��ȡԪ�غ��\n");
        printf("    	  2. �������Ա�       10. ����Ԫ��\n");
        printf("    	  3. ������Ա�       11. ɾ��Ԫ��\n");
        printf("    	  4. �ж����Ա��Ƿ�Ϊ�� 12. �������Ա�\n");
        printf("    	  5. ��ȡ���Ա���   13. ��ת���Ա�\n");
        printf("    	  6. ��ȡָ��Ԫ��     14. ɾ��������n��Ԫ��\n");
        printf("    	  7. ����Ԫ��λ��     15. �����Ա�����\n");
        printf("    	  8. ��ȡԪ��ǰ��     16. ����/�������Ա�\n");
        printf("    	  0. �˳�\n");
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
            case 13: {
                if (reverseList(L) == OK) printf("����ת�ɹ���\n");
                else printf("����תʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 14: {
                int n;
                printf("������Ҫɾ���ĵ����� n ���ڵ㣺");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("ɾ���ɹ���\n");
                else printf("ɾ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
            case 15: {
                if (sortList(L) == OK) printf("��������ɹ���\n");
                else printf("��������ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            }
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

status reverseList(SqList& L) {
    if (L.elem == NULL) return INFEASTABLE; // ���Ա�����
    if (L.length <= 1) return OK;          // ����Ϊ 0 �� 1�����跭ת
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

status RemoveNthFromEnd(SqList& L, int n) {
    if (L.elem == NULL) return INFEASTABLE; // ���Ա�����
    if (n <= 0 || n > L.length) return ERROR; // n ���Ϸ�
    int index = L.length - n; // ������ n ���ڵ������
    ElemType e; // ���ڴ洢��ɾ����Ԫ��
    return ListDelete(L, index + 1, e); // �������е�ɾ������
}

status sortList(SqList& L) {
    if (L.elem == NULL) return INFEASTABLE; // ���Ա�����
    std::sort(L.elem, L.elem + L.length);  // ʹ�� std::sort ����
    return OK;
}

status SaveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASTABLE; // ���Ա�����
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

