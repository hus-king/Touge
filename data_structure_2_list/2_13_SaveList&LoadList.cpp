#include "def.h"
#include "string.h"
status SaveList(LinkList L,char FileName[]) //将线性表写入文件
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能写入
    FILE *fp=fopen(FileName,"w"); //打开文件
    if (!fp) return ERROR; //打开失败
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        fprintf(fp,"%d ",p->data); //写入数据
        p=p->next; //指向下一个结点
    }
    fclose(fp); //关闭文件
    return OK; //返回成功
}
status LoadList(LinkList &L,char FileName[]) //从文件中读取线性表
{
    if (L) return INFEASIBLE; //线性表已存在，不能读取
    FILE *fp=fopen(FileName,"r"); //打开文件
    if (!fp) return ERROR; //打开失败
    L=(LinkList)malloc(sizeof(LNode)); //分配头结点空间
    if (!L) return OVERFLOW; //内存分配失败
    L->next=NULL; //初始化头结点的next指针为NULL
    LNode *p=L; //指向当前结点
    int data;
    while (fscanf(fp,"%d",&data)==1) { //读取数据
        LNode *s=(LNode*)malloc(sizeof(LNode)); //分配新结点空间
        if (!s) return OVERFLOW; //内存分配失败
        s->data=data; //设置数据域
        s->next=NULL; //设置next指针为NULL
        p->next=s; //将新结点链接到链表中
        p=s; //移动到新结点
    }
    fclose(fp); //关闭文件
    return OK; //返回成功
}
int main() {
	LinkList L;
	int f,i=0,j,e;
	FILE *fp;
	char FileName[30];
	strcpy(FileName,"src/step13/list.dat");
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=SaveList(L,"src/step13/list.dat");
		if (j==INFEASIBLE) printf("INFEASIBLE\n");
    	else printf("不能对不存在的线性表进行写文件操作！\n");
    	
    	L=(LinkList) malloc(sizeof(LNode));
    	L->next=NULL;
        j=LoadList(L,"");
        if (j==INFEASIBLE) printf("INFEASIBLE\n");
        else printf("不能对已存在的线性表进行写操作！否则会覆盖原数据，造成数据丢失\n");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		j=SaveList(L,"src/step13/list.dat");
		if(j==OK) printf("OK\n");
    	while(L)
    	{
        	s = L->next;
            L->data=0;
        	free(L);
        	L = s;
    	}
		j=LoadList(L,"src/step13/list.dat");
		if(j==OK) printf("OK\n");
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}