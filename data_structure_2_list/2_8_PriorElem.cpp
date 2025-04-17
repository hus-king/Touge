#include "def.h"
status PriorElem(LinkList L,ElemType e,int &pre) //查找线性表中元素e的前驱
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L->next==NULL) return ERROR; //线性表为空，不能查找
    LNode *p=L->next; //指向第一个结点
    int j=1; //计数器
    while (p && p->data!=e) { //遍历链表
        pre=p->data; //保存前驱元素
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (j==1 || p==NULL) return ERROR; //未找到元素e或没有前驱元素
    return OK; //返回成功
}
int main() {
	LinkList L;
	int f,i,j,e,pre;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=PriorElem(L,e,pre);
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
		j=PriorElem(L,e,pre);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",pre);
	}
	return 1;
}