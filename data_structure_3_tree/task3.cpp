#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <cstring>
#include "my.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_TREE_NUM 10

typedef int status;
typedef int KeyType; 
typedef struct {
        KeyType  key;
        char others[20];
} TElemType; //������������Ͷ���

typedef struct BiTNode{  //����������Ķ���
        TElemType  data;
        struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

// ========== ������������� ==========
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

// 15. ���·���ͣ�����Ҷ���·���ͣ�
int MaxPathSum(BiTree T) {
    if (!T) return 0;
    int l = MaxPathSum(T->lchild);
    int r = MaxPathSum(T->rchild);
    // Ҷ�ӽڵ�
    if (!T->lchild && !T->rchild) return T->data.key;
    // ֻ�������
    if (!T->lchild) return r + T->data.key;
    if (!T->rchild) return l + T->data.key;
    // ���߶���
    return (l > r ? l : r) + T->data.key;
}

// 16. �����������
BiTNode* LowestCommonAncestor(BiTree T, int e1, int e2) {
    if (!T) return NULL;
    if (T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if (left && right) return T;
    return left ? left : right;
}

// 17. ��ת������
void InvertTree(BiTree T) {
    if (!T) return;
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

// ========== �����������ṹ�� ==========
typedef struct {
    struct {
        char name[30]; // ����������
        BiTree T;      // ������ָ��
    } elem[MAX_TREE_NUM];
    int length; // ��ǰ����Ķ���������
} TREES;

// ���Ҷ�����������λ�ã�1��ʼ����δ�ҵ�����0
int LocateTree(TREES &Trees, const char name[]) {
    for (int i = 0; i < Trees.length; i++) {
        if (strcmp(Trees.elem[i].name, name) == 0)
            return i + 1;
    }
    return 0;
}

// ��Ӷ�����
status AddTree(TREES &Trees, const char name[]) {
    if (Trees.length >= MAX_TREE_NUM) return ERROR;
    strcpy(Trees.elem[Trees.length].name, name);
    Trees.elem[Trees.length].T = NULL;
    Trees.length++;
    return OK;
}

// �Ƴ�������
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

// ���ö����������˵�
void SingleTreeMenu(BiTree &T) {
    int op = 1;
    while (op) {
        printf("\n\n");
        printf("      ���ö����������˵�\n");
        printf("-------------------------------------------------\n");
        printf(" 1. ����������       10. ɾ�����\n");
        printf(" 2. ���ٶ�����       11. ǰ�����\n");
        printf(" 3. ��ն�����       12. �������\n");
        printf(" 4. �пն�����       13. �������\n");
        printf(" 5. ����������     14. �������\n");
        printf(" 6. ���ҽ��         15. ���·����\n");
        printf(" 7. ��㸳ֵ         17. ��ת������\n");
        printf(" 8. ����ֵܽ��      16. �����������\n");
        printf(" 9. ������         18. ����/���ض�����\n");
        printf(" 0. �����ϼ�\n");
        printf("-------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0~18]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: { // ����������
                int n;
                printf("�������������");
                scanf("%d", &n);
                TElemType *def = (TElemType*)malloc(sizeof(TElemType) * (n*2));
                printf("����������%d������key��others��keyΪ-1��ʾ�ս�㣩��\n", n);
                for (int i = 0; i < n; ++i) {
                    printf("��%d����� key: ", i+1);
                    scanf("%d", &def[i].key);
                    if (def[i].key == -1) strcpy(def[i].others, "");
                    else {
                        printf("others: ");
                        scanf("%s", def[i].others);
                    }
                }
                if (CreateBiTree(T, def) == OK) printf("�����������ɹ���\n");
                else printf("����������ʧ�ܣ����ظ�key��ռ䲻�㣩��\n");
                free(def);
                getchar();
                break;
            }
            case 2: { // ���ٶ�����
                if (T) {
                    DestroyBiTree(T);
                    T = NULL;
                    printf("���������ٳɹ���\n");
                } else printf("�����������ڣ�\n");
                getchar();
                break;
            }
            case 3: { // ��ն�����
                if (T) {
                    ClearBiTree(T);
                    printf("����������գ�\n");
                } else printf("�����������ڣ�\n");
                getchar();
                break;
            }
            case 4: { // �п�
                if (!T) printf("������Ϊ�գ�\n");
                else printf("���������գ�\n");
                getchar();
                break;
            }
            case 5: { // ���
                if (!T) printf("�����������ڣ�\n");
                else printf("���������Ϊ��%d\n", BiTreeDepth(T));
                getchar();
                break;
            }
            case 6: { // ���ҽ��
                int key;
                printf("������Ҫ���ҵĹؼ��֣�");
                scanf("%d", &key);
                BiTNode *p = LocateNode(T, key);
                if (p) printf("�ҵ���㣺key=%d, others=%s\n", p->data.key, p->data.others);
                else printf("δ�ҵ��ý�㣡\n");
                getchar();
                break;
            }
            case 7: { // ��㸳ֵ
                int key;
                TElemType val;
                printf("������Ҫ��ֵ�Ľ��ؼ��֣�");
                scanf("%d", &key);
                printf("��������ֵ key: ");
                scanf("%d", &val.key);
                printf("��������ֵ others: ");
                scanf("%s", val.others);
                if (Assign(T, key, val) == OK) printf("��ֵ�ɹ���\n");
                else printf("��ֵʧ�ܣ��ؼ��ֳ�ͻ�򲻴��ڣ���\n");
                getchar();
                break;
            }
            case 8: { // ����ֵܽ��
                int key;
                printf("������Ҫ�����ֵܵĽ��ؼ��֣�");
                scanf("%d", &key);
                BiTNode *sib = GetSibling(T, key);
                if (sib) printf("�ֵܽ�㣺key=%d, others=%s\n", sib->data.key, sib->data.others);
                else printf("���ֵܽ�㣡\n");
                getchar();
                break;
            }
            case 9: { // ������
                int e, LR;
                TElemType val;
                printf("�����븸���ؼ��֣�-1��ʾ����Ϊ�¸�����");
                scanf("%d", &e);
                printf("��������뷽��0��1�ң�-1�¸�����");
                scanf("%d", &LR);
                printf("�������½�� key: ");
                scanf("%d", &val.key);
                printf("�������½�� others: ");
                scanf("%s", val.others);
                if (InsertNode(T, e, LR, val) == OK) printf("����ɹ���\n");
                else printf("����ʧ�ܣ��ؼ��ֳ�ͻ�򸸽�㲻���ڣ���\n");
                getchar();
                break;
            }
            case 10: { // ɾ�����
                int key;
                printf("������Ҫɾ���Ľ��ؼ��֣�");
                scanf("%d", &key);
                printf("δʵ��DeleteNode����������my.h�в���ʵ�֣�\n");
                getchar();
                break;
            }
            case 11: { // ǰ�����
                printf("ǰ�������");
                PreOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 12: { // �������
                printf("���������");
                InOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 13: { // �������
                printf("���������");
                PostOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 14: { // �������
                printf("���������");
                LevelOrderTraverse(T, visit);
                printf("\n");
                getchar();
                break;
            }
            case 15: { // ���·����
                if (!T) printf("�����������ڣ�\n");
                else printf("����Ҷ���·����Ϊ��%d\n", MaxPathSum(T));
                getchar();
                break;
            }
            case 16: { // �����������
                int e1, e2;
                printf("�������������Ĺؼ��֣�");
                scanf("%d%d", &e1, &e2);
                BiTNode* lca = LowestCommonAncestor(T, e1, e2);
                if (lca)
                    printf("����������ȣ�key=%d, others=%s\n", lca->data.key, lca->data.others);
                else
                    printf("δ�ҵ�����������ȣ�\n");
                getchar();
                break;
            }
            case 17: { // ��ת������
                if (!T) printf("�����������ڣ�\n");
                else {
                    InvertTree(T);
                    printf("�������ѷ�ת��\n");
                }
                getchar();
                break;
            }
            case 18: { // ����/���ض�����
                int subop;
                char filename[100];
                printf("1. ������������ļ�\n2. ���ļ����ض�����\n��ѡ��");
                scanf("%d", &subop);
                printf("�������ļ�����");
                scanf("%s", filename);
                if (subop == 1) {
                    if (SaveBiTree(T, filename) == OK)
                        printf("����ɹ���\n");
                    else
                        printf("����ʧ�ܣ�\n");
                } else if (subop == 2) {
                    if (LoadBiTree(T, filename) == OK)
                        printf("���سɹ���\n");
                    else
                        printf("����ʧ�ܣ�\n");
                } else {
                    printf("��Ч������\n");
                }
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

// ��������������
int main() {
    TREES Trees;
    Trees.length = 0;
    int op = 1;
    while (op) {
        printf("\n\n");
        printf("      �������������˵� \n");
        printf("-------------------------------------------------\n");
        printf("1. ��Ӷ�����       4. ��ʾ���ж�����\n");
        printf("2. �Ƴ�������       5. ��������������\n");
        printf("3. ���Ҷ�����       0. �˳�\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~5]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: {
                char name[30];
                printf("�������¶����������ƣ�");
                scanf("%s", name);
                if (LocateTree(Trees, name) > 0) {
                    printf("���������� '%s' �Ѵ��ڣ����ʧ�ܣ�\n", name);
                } else {
                    if (AddTree(Trees, name) == OK) {
                        printf("������ '%s' ��ӳɹ���\n", name);
                    } else {
                        printf("���������ʧ�ܣ�\n");
                    }
                }
                getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("������Ҫ�Ƴ��Ķ��������ƣ�");
                scanf("%s", name);
                if (RemoveTree(Trees, name) == OK) printf("������ '%s' �Ƴ��ɹ���\n", name);
                else printf("�������Ƴ�ʧ�ܣ�\n");
                getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("������Ҫ���ҵĶ��������ƣ�");
                scanf("%s", name);
                int pos = LocateTree(Trees, name);
                if (pos > 0) printf("������ '%s' ��λ��Ϊ��%d\n", name, pos);
                else printf("δ�ҵ������� '%s'��\n", name);
                getchar();
                break;
            }
            case 4: {
                if (Trees.length == 0) {
                    printf("��ǰû�ж�������\n");
                } else {
                    printf("��ǰ�������б�\n");
                    for (int i = 0; i < Trees.length; i++) {
                        printf("  %d. %s\n", i + 1, Trees.elem[i].name);
                    }
                }
                getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("������Ҫ�����Ķ��������ƣ�");
                scanf("%s", name);
                int pos = LocateTree(Trees, name);
                if (pos > 0) {
                    printf("���л��������� '%s'��\n", name);
                    SingleTreeMenu(Trees.elem[pos - 1].T);
                } else {
                    printf("δ�ҵ������� '%s'��\n", name);
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
