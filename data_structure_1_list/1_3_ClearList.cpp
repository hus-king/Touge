#include "def.h"
status ClearList(SqList &L) //清空线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能清空
    L.length=0; //设置元素个数初始值
    return OK; //清空成功
}
int main() {
	SqList L;
	int i,j;
	scanf("%d",&i);
	if (!i) { 
		L.elem=NULL;
		j=ClearList(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表清空");
    }
	else {
		L.elem=(ElemType *) malloc(sizeof(ElemType));
        L.length = 1;
		j=ClearList(L);
		if (L.length) printf("未正确清空");
		if (!L.elem)  printf("错误释放元素空间");
		if (j==OK) printf("OK");
		free(L.elem);
    }
	return 1;
}