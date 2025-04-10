#include "def.h"
status LocateElem(SqList L,ElemType e) //查找线性表中元素e的位置
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    for (int i=0;i<L.length;i++)
        if (L.elem[i]==e) return i+1; //返回元素e的位置
    return ERROR; //未找到元素e
}
int main() {
	SqList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		L.length=3;
		j=LocateElem(L,e); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表查找元素");
		
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
		j=LocateElem(L,e);
		if(j==ERROR) printf("ERROR");
		else printf("%d",j);
		free(L.elem);
	}
	return 1;
}