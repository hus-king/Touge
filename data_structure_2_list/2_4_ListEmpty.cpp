#include "def.h"
status ListEmpty(LinkList L) //判线性表是否为空
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能判空
    if (L->next==NULL) return OK; //线性表为空
    else return ERROR; //线性表不空
}
int main() {
	LinkList L;
	int i,j;
	scanf("%d",&i);
	if (i==2) { 
		L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		j=ListEmpty(L);
		if (j==OK) printf("TRUE");
		else printf("未正确判空");
		free(L);
    }
	else if(i==1) {
		L=(LinkList) malloc(sizeof(LNode));
		L->next=(LNode*) malloc(sizeof(LNode));
		L->next->next=NULL;
		j=ListEmpty(L);
		if (j==ERROR) printf("FALSE");
		else printf("未正确判空");
		free(L->next);
		free(L);
    }
    else {
    	L=NULL;
		j=ListEmpty(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表判空");
	}
	return 1;
}