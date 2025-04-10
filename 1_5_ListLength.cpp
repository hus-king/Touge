#include "def.h"
status ListLength(SqList L) //求线性表的长度
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能求长
    return L.length; //返回线性表的长度
}
int main() {
	SqList L;
	int f,i,j,c=0;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
    	L.length=10;
		j=ListLength(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表求表长");
    }
    else {
    	L.elem=(ElemType *) malloc(sizeof(ElemType));
    	scanf("%d",&i);
     	while (i) {
         ++c;
         scanf("%d",&i);
		}
		L.length=c;
		j=ListLength(L);
		printf("%d", j);
		free(L.elem);
	}
	return 1;
}