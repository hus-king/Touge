#include "def.h"
status LocateElem(LinkList L,ElemType e) //查找线性表中元素e的位置
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    int i=1; //计数器
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        if (p->data==e) return i; //找到元素e，返回位置
        p=p->next; //指向下一个结点
        i++; //计数器加1
    }
    return ERROR; //未找到元素e
}
int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=LocateElem(L,e);
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
		j=LocateElem(L,e);
		if(j==ERROR) printf("ERROR");
		else printf("%d",j);
	}
	return 1;
}