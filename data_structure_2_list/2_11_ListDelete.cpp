#include "def.h"
#include "ctype.h"
#include "string.h"
#define free free0
#undef free
status ListDelete(LinkList &L,int i,ElemType &e) //删除线性表的第i个元素
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能删除
    if (i<1) return ERROR; //i不合法
    LNode *p=L,*q; //p指向头结点，q指向要删除的结点
    int j=0; //计数器，从头结点开始计数
    while (p && j<i-1) { //遍历链表，找到第i-1个结点
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (!p || j!=i-1) return ERROR; //未找到第i-1个位置或位置不合法
    q=p->next; //q指向要删除的结点
    if (!q) return ERROR; //要删除的结点不存在
    e=q->data; //获取要删除的结点的数据域
    p->next=q->next; //将第i-1个结点的next指针指向第i+1个结点
    free(q); //释放要删除的结点的空间
    return OK; //返回成功
}
struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    free(p);
}

int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListDelete(L,1,e);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("不能对不存在的线性表进行删除操作！");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			pm.pused[pm.len_used++]=s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		scanf("%d",&i);
		j=ListDelete(L,i,e);
		if(j==ERROR) printf("ERROR\n");
		if(j==OK) {
            for(i=0;i<pm.len_used;i++)
                if (pm.pfree[0]==pm.pused[i]) break;
			if (pm.len_free!=1 || i>=pm.len_used)
            {
                printf("未正确释放数据元素空间");
                return 1;
            }
            printf("OK\n%d\n",e);
		}
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}
