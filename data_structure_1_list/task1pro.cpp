#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // ���� std::sort
#include <unordered_map> // ���� std::unordered_map

/*---------���峣��������---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // ����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100 // ��ʼ����ռ��С
#define LISTINCREMENT  10  // ��������ռ��С

// ˳���˳��ṹ���Ķ���
typedef struct {
    ElemType* elem = NULL; // ����Ԫ�ش洢�ռ�Ļ�ַ
    int length;     // ��ǰ����
    int listsize;   // ��ǰ����Ĵ洢����
} SqList;

// ���Ա�Ĺ������
typedef struct {
    struct {
        char name[30]; // ���Ա�����
        SqList L;      // ���Ա�
    } elem[10];        // ������ 10 �����Ա�
    int length;        // ��ǰ��������Ա�����
} LISTS;

/*---------��������---------*/
status InitList(SqList& L); // ��ʼ�����Ա�
status DestroyList(SqList& L); // �������Ա�
status ClearList(SqList& L); // ������Ա�
status ListEmpty(SqList L); // �ж����Ա��Ƿ�Ϊ��
int ListLength(SqList L); // ��ȡ���Ա���
status GetElem(SqList L, int i, ElemType& e); // ��ȡ���Ա��е� i ��Ԫ��
status LocateElem(SqList L, ElemType e); // ����Ԫ�� e ��λ��
status PriorElem(SqList L, ElemType cur, ElemType& pre_e); // ��ȡԪ�ص�ǰ��
status NextElem(SqList L, ElemType cur, ElemType& next_e); // ��ȡԪ�صĺ��
status ListInsert(SqList& L, int i, ElemType e); // �ڵ� i ��λ�ò���Ԫ��
status ListDelete(SqList& L, int i, ElemType& e); // ɾ���� i ��λ�õ�Ԫ��
status ListTraverse(SqList L); // �������Ա�
status reverseList(SqList& L); // ��ת���Ա�
status RemoveNthFromEnd(SqList& L, int n); // ɾ�������� n ��Ԫ��
status sortList(SqList& L); // �����Ա�����
status SaveListToFile(SqList L, const char* filename); // �������Ա��ļ�
status LoadListFromFile(SqList& L, const char* filename); // ���ļ��������Ա�
status AddList(LISTS& Lists, char ListName[]); // ������Ա�
status RemoveList(LISTS& Lists, char ListName[]); // �Ƴ����Ա�
int LocateList(LISTS Lists, char ListName[]); // �������Ա�λ��
status MaxSubArray(SqList L); // ��������������
status SubArrayNum(SqList L, int k); // ��ΪK��������

/*---------����ʵ��---------*/

// ��ʼ�����Ա�
status InitList(SqList& L) {
    if (L.elem) return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

// �������Ա�
status DestroyList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

// ������Ա�
status ClearList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

// �ж����Ա��Ƿ�Ϊ��
status ListEmpty(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length == 0 ? OK : ERROR;
}

// ��ȡ���Ա���
int ListLength(SqList L) {
    if (!L.elem) return INFEASIBLE;
    return L.length;
}

// ��ȡ���Ա��е� i ��Ԫ��
status GetElem(SqList L, int i, ElemType& e) {
    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

// ����Ԫ�� e ��λ��
status LocateElem(SqList L, ElemType e) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}

// ��ȡԪ�ص�ǰ��
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

// ��ȡԪ�صĺ��
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

// �ڵ� i ��λ�ò���Ԫ��
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

// ɾ���� i ��λ�õ�Ԫ��
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

// �������Ա�
status ListTraverse(SqList L) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
    return OK;
}

// ��ת���Ա�
status reverseList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length / 2; i++) {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[L.length - 1 - i];
        L.elem[L.length - 1 - i] = temp;
    }
    return OK;
}

// ɾ�������� n ��Ԫ��
status RemoveNthFromEnd(SqList& L, int n) {
    if (!L.elem) return INFEASIBLE;
    if (n <= 0 || n > L.length) return ERROR;
    int index = L.length - n;
    ElemType e;
    return ListDelete(L, index + 1, e);
}

// �����Ա�����
status sortList(SqList& L) {
    if (!L.elem) return INFEASIBLE;
    std::sort(L.elem, L.elem + L.length);
    return OK;
}

// �������Ա��ļ�
status SaveListToFile(SqList L, const char* filename) {
    if (!L.elem) return INFEASIBLE;
    FILE* fp = fopen(filename, "wb");
    if (!fp) return ERROR;
    fwrite(&L.length, sizeof(int), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}

// ���ļ��������Ա�
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

// ������Ա�
status AddList(LISTS& Lists, char ListName[]) {
    if (Lists.length >= 10) return ERROR; // ����������Ա���������
    strcpy(Lists.elem[Lists.length].name, ListName); // �������Ա�����
    if (InitList(Lists.elem[Lists.length].L) != OK) return ERROR; // ��ʼ�����Ա�
    Lists.length++; // �������Ա�����
    return OK;
}

// �Ƴ����Ա�
status RemoveList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) { // �ҵ�ƥ������Ա�
            DestroyList(Lists.elem[i].L); // �������Ա�
            for (int j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1]; // �ƶ��������Ա�
            }
            Lists.length--; // �������Ա�����
            return OK;
        }
    }
    return ERROR; // δ�ҵ�ָ�����Ƶ����Ա�
}

// �������Ա�λ��
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            return i + 1; // �������Ա�� 1-based ����
        }
    }
    return 0; // δ�ҵ�
}

// ��������������
status MaxSubArray(SqList L) {
    if (!L.elem) return INFEASIBLE;
    int maxSum = L.elem[0], currentSum = L.elem[0];
    for (int i = 1; i < L.length; i++) {
        currentSum = std::max(L.elem[i], currentSum + L.elem[i]);
        maxSum = std::max(maxSum, currentSum);
    }
    printf("��������������Ϊ��%d\n", maxSum);
    return OK;
}

// ��ΪK��������
status SubArrayNum(SqList L, int k) {
    if (!L.elem) return INFEASIBLE;
    int count = 0, sum = 0;
    std::unordered_map<int, int> prefixSum;
    prefixSum[0] = 1; // ��ʼ��ǰ׺��Ϊ0�����
    for (int i = 0; i < L.length; i++) {
        sum += L.elem[i];
        if (prefixSum.find(sum - k) != prefixSum.end()) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    printf("��Ϊ%d�����������Ϊ��%d\n", k, count);
    return OK;
}

/*---------�������Ա�����˵�---------*/
// �ṩ�������Ա�����в���
void SingleListMenu(SqList& L) {
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("�������Ա�����˵� \n");
        printf("-------------------------------------------------\n");
        printf("%-4d%-20s%-4d%s\n", 1, "��ʼ�����Ա�", 9, "��ȡԪ�غ��");
        printf("%-4d%-20s%-4d%s\n", 2, "�������Ա�", 10, "����Ԫ��");
        printf("%-4d%-20s%-4d%s\n", 3, "������Ա�", 11, "ɾ��Ԫ��");
        printf("%-4d%-20s%-4d%s\n", 4, "�ж����Ա��Ƿ�Ϊ��", 12, "�������Ա�");
        printf("%-4d%-20s%-4d%s\n", 5, "��ȡ���Ա���", 13, "��������������");
        printf("%-4d%-20s%-4d%s\n", 6, "��ȡָ��Ԫ��", 14, "��ΪK��������");
        printf("%-4d%-20s%-4d%s\n", 7, "����Ԫ��λ��", 15, "�����Ա�����");
        printf("%-4d%-20s%-4d%s\n", 8, "��ȡԪ��ǰ��", 16, "����/�������Ա�");
        printf("%-4d%-20s\n",0,"�˳�");
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
                if (MaxSubArray(L) == OK) printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 14: {
                int k;
                printf("������Ŀ���K��");
                scanf("%d", &k);
                if (SubArrayNum(L, k) == OK) printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
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
// �ṩ������Ա�Ĺ�����
int main() {
    LISTS Lists;
    Lists.length = 0; // ��ʼ�����Ա������
    int op = 1;

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      ������Ա����˵� \n");
        printf("-------------------------------------------------\n");
        printf("1. ������Ա�       4. ��ʾ�������Ա�\n");
        printf("2. �Ƴ����Ա�       5. �����������Ա�\n");
        printf("3. �������Ա�       0. �˳�\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~5]:");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char name[30];
                printf("�����������Ա�����ƣ�");
                scanf("%s", name);
            
                // ��������Ƿ��ظ�
                if (LocateList(Lists, name) > 0) {
                    printf("���Ա����� '%s' �Ѵ��ڣ����ʧ�ܣ�\n", name);
                } else {
                    if (AddList(Lists, name) == OK) {
                        printf("���Ա� '%s' ��ӳɹ���\n", name);
                    } else {
                        printf("���Ա����ʧ�ܣ�\n");
                    }
                }
            
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
                else printf("δ�ҵ����Ա� '%s'��\n",name);
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
                    printf("δ�ҵ����Ա� '%s'��\n",name);
                }
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}

