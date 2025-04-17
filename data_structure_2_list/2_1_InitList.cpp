#include "def.h"
status InitList(LinkList &L) {
    if (L) return INFEASIBLE; // 如果 L 已经存在，则返回 INFEASIBLE
    L = (LinkList)malloc(sizeof(LNode)); // 分配头结点空间
    if (!L) return OVERFLOW; // 如果分配失败，返回 OVERFLOW
    L->next = NULL; // 初始化头结点的 next 指针为 NULL
    return OK; // 返回成功
}
int main() {
	LinkList L;
	int i,j;
	scanf("%d",&i);
	if (!i) { 
		L = NULL;
		j = InitList(L);
 		if (L==NULL) printf("可能没有正确分配表头节点空间");
		if (L->next!=NULL) printf("表头节点可能没有正确初始化");
		if (j==OK) printf("OK");
    }
	else {
		L=(LinkList)malloc(sizeof(LNode));
		j=InitList(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
		else printf("可能会对已经存在的线性表初始化");
		free(L);
	}
	return 1;
}