#include "def.h"
status PriorElem(SqList L,ElemType e,int &pre) //查找线性表中元素e的前驱
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L.length==0) return ERROR; //线性表为空，不能查找
    for (int i=1;i<L.length;i++)
        if (L.elem[i]==e) { pre=L.elem[i-1]; return OK; } //返回元素e的前驱
    return ERROR; //未找到元素e
}
int main() {
	SqList L;
	int f,i,j,e,pre;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		L.length=3;
		j=PriorElem(L,e,pre); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表查找前驱元素");
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
		j=PriorElem(L,e,pre);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",pre);
		free(L.elem);
	}
	return 1;
}