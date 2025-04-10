#include "def.h"
status ListDelete(SqList &L,int i,ElemType &e) //删除线性表的第i个元素
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能删除
    if (i<1 || i>L.length) return ERROR; //i不合法
    e=L.elem[i-1]; //获取第i个元素
    for (ElemType *q=&L.elem[i-1]; q<&L.elem[L.length-1]; q++) *q=*(q+1); //将第i+1个元素及其后面的元素前移一位
    L.length--; //线性表长度减1
    return OK; //删除成功
}
int main() {
	SqList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=ListDelete(L,1,e); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("不能对不存在的线性表进行删除操作！");
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
		scanf("%d",&i);
		j=ListDelete(L,i,e);
		if(j==ERROR) printf("ERROR\n");
		if(j==OK) printf("OK\n%d\n",e);
		for(i=0;i<L.length;i++)
        	printf("%d ",L.elem[i]);
		free(L.elem);
	}
	return 1;
}