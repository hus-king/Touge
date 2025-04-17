#include "def.h"
status ListInsert(LinkList &L, int i, ElemType e) // 在第i个位置插入元素e
{
    if (L == NULL) return INFEASIBLE; // 线性表不存在，不能插入
    if (i < 1) return ERROR; // i不合法

    LNode *p = L; // 指向头结点
    int j = 0; // 计数器，从头结点开始计数
    while (p && j < i - 1) { // 遍历链表，找到第i-1个结点
        p = p->next; // 指向下一个结点
        j++; // 计数器加1
    }
    if (!p || j != i - 1) return ERROR; // 未找到第i-1个位置或位置不合法

    LNode *s = (LNode *)malloc(sizeof(LNode)); // 申请新结点空间
    if (!s) return ERROR; // 内存分配失败
    s->data = e; // 设置新结点的数据域
    s->next = p->next; // 将新结点的next指针指向原来的第i个结点
    p->next = s; // 将原来的第i-1个结点的next指针指向新结点
    return OK; // 返回成功
}
int main() {
	LinkList L;
	int f,i,j,e,next;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListInsert(L,1,1);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("不能对不存在的线性表进行插入操作！");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		scanf("%d%d",&i,&e);
		j=ListInsert(L,i,e);
		printf("%s\n", j==OK? "OK" : j==ERROR? "ERROR" : "");
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}