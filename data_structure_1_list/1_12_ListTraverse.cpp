#include "def.h"
status ListTraverse(SqList L) //遍历线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能遍历
    if (L.length==0) return OK; //线性表为空，遍历成功
    for (int i=0;i<L.length;i++)
        printf("%d ",L.elem[i]); //输出线性表的元素
    return OK; //遍历成功
}
int main() {
	SqList L;
	int f,i,j;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=ListTraverse(L); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表进行遍历操作！");
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
		j=ListTraverse(L);
		if(j==OK && !L.length) printf("空线性表\n");
		free(L.elem);
	}
	return 1;
}