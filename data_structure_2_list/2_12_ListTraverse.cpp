#include "def.h"
status ListTraverse(LinkList L) //遍历线性表
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能遍历
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        printf("%d ",p->data); //输出当前结点的数据域
        p=p->next; //指向下一个结点
    }
    return OK; //返回成功
}
int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListTraverse(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表进行遍历操作！");
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
		j=ListTraverse(L);
		if(j==OK && L->next==NULL) printf("空线性表");
	}
	return 1;
}