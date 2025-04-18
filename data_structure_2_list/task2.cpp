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

// ��ʼ�����Ա�
status InitList(LinkList &L) {
    if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) return OVERFLOW;
    L->next = NULL;
    return OK;
}

// �������Ա�
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

// ������Ա�
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

// �п����Ա�
status ListEmpty(LinkList L) {
    if (L==NULL) return INFEASIBLE;
    if (L->next==NULL) return OK;
    else return ERROR;
}

// �����Ա���
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

// ��ȡ��i��Ԫ��
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

// ����Ԫ��e��λ��
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

// ����Ԫ��e��ǰ��
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

// ����Ԫ��e�ĺ��
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

// �ڵ�i��λ�ò���Ԫ��e
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

// ɾ����i��Ԫ��
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

// �������Ա�
status ListTraverse(LinkList L) {
    if (L==NULL) return INFEASIBLE;
    LNode *p=L->next;
    while (p) {
        printf("%d ",p->data);
        p=p->next;
    }
    return OK;
}

// �������Ա��ļ�
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

// ���ļ��������Ա�
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

// ����ת
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

// ɾ��������n�����
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

// ��������
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

// ���ٽ��������������ٽ����Իس�Ϊ������
void QuickCreateList(LinkList &L) {
    if (L) ClearList(L);
    else InitList(L);
    printf("������Ԫ�أ��Իس���������");
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

// ������ṹ��
typedef struct {
    struct {
        char name[30]; // ���Ա�����
        LinkList L;    // ���Ա�
    } elem[10];        // ������ 10 �����Ա�
    int length;        // ��ǰ��������Ա�����
} LISTS;

// �������Ա�����λ�ã�1��ʼ����δ�ҵ�����0
int LocateList(LISTS &Lists, const char name[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, name) == 0)
            return i + 1;
    }
    return 0;
}

// ������Ա�
status AddList(LISTS &Lists, const char name[]) {
    if (Lists.length >= 10) return ERROR;
    strcpy(Lists.elem[Lists.length].name, name);
    Lists.elem[Lists.length].L = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}

// �Ƴ����Ա�
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

// ��������˵�
void SingleListMenu(LinkList &L) {
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      ����������˵�\n");
        printf("-------------------------------------------------\n");
        printf(" 1. ��ʼ����        10. ����Ԫ��\n");
        printf(" 2. ���ٱ�          11. ɾ��Ԫ��\n");
        printf(" 3. ��ձ�          12. ������\n");
        printf(" 4. �пձ�          13. ����ת\n");
        printf(" 5. ���          14. ɾ��������n��\n");
        printf(" 6. ��ȡԪ��        15. ���浽�ļ�\n");
        printf(" 7. ����Ԫ��λ��    16. ���ļ�����\n");
        printf(" 8. ����ǰ��Ԫ��    17. ��������\n");
        printf(" 9. ���Һ��Ԫ��    18. ���ٽ���\n");
        printf(" 0. �����ϼ�\n");
        printf("-------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0~18]:");
        scanf("%d", &op);
        int i, ret, e, pre, next, n;
        char filename[100];
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
                ret = ListEmpty(L);
                if (ret == OK) printf("���Ա�Ϊ�գ�\n");
                else if (ret == ERROR) printf("���Ա��գ�\n");
                else printf("���Ա����ڣ�\n");
                getchar(); getchar();
                break;
            case 5:
                ret = ListLength(L);
                if (ret >= 0) printf("���Ա���Ϊ��%d\n", ret);
                else printf("���Ա����ڣ�\n");
                getchar(); getchar();
                break;
            case 6:
                printf("������Ҫ��ȡ��Ԫ��λ��i��");
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK) printf("��%d��Ԫ��Ϊ��%d\n", i, e);
                else printf("��ȡԪ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 7:
                printf("������Ҫ���ҵ�Ԫ��ֵe��");
                scanf("%d", &e);
                ret = LocateElem(L, e);
                if (ret > 0) printf("Ԫ��%d�����Ա��е�λ��Ϊ��%d\n", e, ret);
                else if (ret == ERROR) printf("δ�ҵ���Ԫ�أ�\n");
                else printf("���Ա����ڣ�\n");
                getchar(); getchar();
                break;
            case 8:
                printf("������Ҫ����ǰ����Ԫ��ֵ��");
                scanf("%d", &e);
                if (PriorElem(L, e, pre) == OK) printf("Ԫ��%d��ǰ��Ϊ��%d\n", e, pre);
                else printf("����ǰ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 9:
                printf("������Ҫ���Һ�̵�Ԫ��ֵ��");
                scanf("%d", &e);
                if (NextElem(L, e, next) == OK) printf("Ԫ��%d�ĺ��Ϊ��%d\n", e, next);
                else printf("���Һ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 10:
                printf("���������λ��i��Ԫ��ֵe��");
                scanf("%d%d", &i, &e);
                if (ListInsert(L, i, e) == OK) printf("����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 11:
                printf("������Ҫɾ����Ԫ��λ��i��");
                scanf("%d", &i);
                if (ListDelete(L, i, e) == OK) printf("ɾ���ɹ�����ɾԪ��Ϊ��%d\n", e);
                else printf("ɾ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 12:
                printf("\n-----------����Ԫ��-----------------------\n");
                if (ListTraverse(L) == OK) printf("\n------------------ end ------------------------\n");
                else printf("���Ա����ڻ�Ϊ�գ�\n");
                getchar(); getchar();
                break;
            case 13:
                if (reverseList(L) == OK) printf("����ת�ɹ���\n");
                else printf("����תʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 14:
                printf("������Ҫɾ���ĵ�����n���ڵ�n��");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) printf("ɾ���ɹ���\n");
                else printf("ɾ��ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 15:
                printf("������Ҫ������ļ�����");
                scanf("%s", filename);
                if (SaveList(L, filename) == OK) printf("����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 16:
                printf("������Ҫ���ص��ļ�����");
                scanf("%s", filename);
                if (LoadList(L, filename) == OK) printf("���سɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 17:
                if (sortList(L) == OK) printf("����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar(); getchar();
                break;
            case 18:
                QuickCreateList(L);
                printf("���ٽ�����ɣ�\n");
                getchar();
                break;
            case 0:
                break;
        }
    }
}

// ������������
int main() {
    LISTS Lists;
    Lists.length = 0;
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
                else printf("δ�ҵ����Ա� '%s'��\n", name);
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
                    printf("δ�ҵ����Ա� '%s'��\n", name);
                    getchar();
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
