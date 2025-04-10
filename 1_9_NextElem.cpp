#include "def.h"
status NextElem(SqList L,ElemType e,int &next) //查找线性表中元素e的后继
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L.length==0) return ERROR; //线性表为空，不能查找
    for (int i=0;i<L.length-1;i++)
        if (L.elem[i]==e) { next=L.elem[i+1]; return OK; } //返回元素e的后继
    return ERROR; //未找到元素e
}
int main() {
	SqList L;
	int f,i,j,e,next;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		L.length=3;
		j=NextElem(L,e,next); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表查找后继元素");
	}
	else {
		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
		L.length=0;
		L.listsize= 10;
		scanf("%d",&i);
		while (i) {
			L.elem[L.length++]=i;
			scanf("%d",&i);
		}
		scanf("%d",&e);
		j=NextElem(L,e,next);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",next);
		free(L.elem);
	}
	return 1;
}