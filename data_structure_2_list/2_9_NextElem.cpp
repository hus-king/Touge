#include "def.h"
status NextElem(LinkList L,ElemType e,int &next) //查找线性表中元素e的后继
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    LNode *p=L->next; //指向第一个结点
    while (p && p->data!=e) { //遍历链表
        p=p->next; //指向下一个结点
    }
    if (p==NULL || p->next==NULL) return ERROR; //未找到元素e或没有后继元素
    next=p->next->data; //获取后继元素
    return OK; //返回成功
}
int main() {
	LinkList L;
	int f,i,j,e,next;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=NextElem(L,e,next); 
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
		scanf("%d",&e);
		j=NextElem(L,e,next);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",next);
	}
	return 1;
}