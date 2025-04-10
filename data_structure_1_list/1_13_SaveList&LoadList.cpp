#include "def.h"
#include "string.h"
status SaveList(SqList L,char FileName[])
{
    FILE *fp;
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能写文件
    if ((fp=fopen(FileName,"w"))==NULL) return ERROR; //打开文件失败
    for (int i=0;i<L.length;i++)
        fprintf(fp,"%d ",L.elem[i]); //写入线性表的元素
    fclose(fp); //关闭文件
    return OK; //写文件成功
}
status LoadList(SqList &L,char FileName[])
{
    FILE *fp;
    if ((fp=fopen(FileName,"r"))==NULL) return ERROR; //打开文件失败
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); //申请空间
    if (!L.elem) return OVERFLOW; //申请失败
    L.listsize=LIST_INIT_SIZE; //设置线性表的空间容量初值
    L.length=0; //设置元素个数初始值
    while (fscanf(fp,"%d",&L.elem[L.length])==1) //读入线性表的元素
        L.length++; //线性表长度加1
    fclose(fp); //关闭文件
    return OK; //读文件成功
}
int main()
{
SqList L;
FILE *fp;
//char FileName[30];
int f,i=0,j,e;
//strcpy(FileName,"src/step13/list.dat");
scanf("%d",&f);
if (!f)
{
    	L.elem=NULL;
   		j=SaveList(L,"src/step13/list.dat");
   		if (j!=INFEASIBLE) printf("不能对不存在的线性表进行写文件操作！");
    	else 
      {
    		 L.elem=(ElemType *) malloc(sizeof(ElemType));
   			 j=LoadList(L,"src/step13/list.dat");
   			 if (j!=INFEASIBLE) printf("不能对已存在的线性表进行读文件操作！");
    	    else printf("INFEASIBLE"); 
    		 free(L.elem);
      }
}
else
     {
        L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        L.listsize= LIST_INIT_SIZE;
        scanf("%d",&e);
        while (e)
        {
            L.elem[i++]=e;
            scanf("%d",&e);
        }
        L.length=i;
        j=SaveList(L,"src/step13/list.dat");
   		free(L.elem); 
		L.elem=NULL;
        j=LoadList(L,"src/step13/list.dat");
        printf("%d\n",L.length);
        for(i=0;i<L.length;i++) 
            printf("%d ",L.elem[i]);
     }
return 1;
}
