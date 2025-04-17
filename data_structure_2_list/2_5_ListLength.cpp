#include "def.h"
status ListLength(LinkList L) //求线性表的长度
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能求长
    int len=0;
    LNode *p=L->next; //从第一个结点开始
    while (p) { //遍历链表
        len++;
        p=p->next; //指向下一个结点
    }
    return len; //返回线性表的长度
}
int main() {
	LinkList L;
	int f,i,j;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListLength(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表求表长");
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
		j=ListLength(L);
		printf("%d", j);
	}
	return 1;
}