#include "def.h"
status GetElem(SqList L,int i,ElemType &e) //求线性表的第i个元素
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能求元素
    if (i<1 || i>L.length) return ERROR; //i不合法
    e=L.elem[i-1]; //获取第i个元素
    return OK; //获取成功
}
int main() {
	SqList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=GetElem(L,2,e); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表获取元素");
		
	}
	else {
		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
		L.length=0;
		L.listsize= 100;
		scanf("%d",&i);
		while (i) {
			L.elem[L.length++]=i;
			scanf("%d",&i);
		}
		scanf("%d",&i);
		j=GetElem(L,i,e);
		if(j==OK) printf("OK\n%d",e);
		if(j==ERROR) printf("ERROR");
		free(L.elem);
	}
	return 1;
}