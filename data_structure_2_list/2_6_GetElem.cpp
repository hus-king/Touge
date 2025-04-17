#include "def.h"
status GetElem(LinkList L,int i,ElemType &e) //求线性表的第i个元素
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能求元素
    if (i<1) return ERROR; //i不合法
    LNode *p=L->next; //指向第一个结点
    int j=1; //计数器
    while (p && j<i) { //遍历链表
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (j!=i) return ERROR; //未找到第i个元素
    e=p->data; //获取第i个元素
    return OK; //获取成功
}
int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=GetElem(L,2,e);
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
		scanf("%d",&i);
		j=GetElem(L,i,e);
		if(j==OK) printf("OK\n%d",e);
		if(j==ERROR) printf("ERROR");
	}
	return 1;
}