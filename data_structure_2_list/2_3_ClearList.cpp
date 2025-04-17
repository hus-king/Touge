#include "def.h"
#include "string.h"
#include "ctype.h"
#define free free0
#undef free
status ClearList(LinkList &L) //清空线性表
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能清空
    LinkList p,q;
    p=L->next; //指向第一个结点
    while (p!=NULL) //遍历链表
    {
        q=p->next; //保存下一个结点的地址
        free(p); //释放当前结点的空间
        p=q; //移动到下一个结点
    }
    L->next=NULL; //清空链表
    return OK; //清空成功
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


int main()
{
	LinkList L,tail;
	int f,i,j;
	scanf("%d",&f);
	if (f==0)
	{
		L=NULL;
		j=ClearList(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
		else printf("不能对不存在的线性表进行销毁操作！");
	}
	else
     {
		pm.pused[pm.len_used++]=tail=L=(LinkList) malloc(sizeof(LNode));
        scanf("%d",&f);
		while (f)
        {
            pm.pused[pm.len_used++]=tail->next=(LNode*) malloc(sizeof(LNode));
            tail=tail->next;
            tail->data=f;
            scanf("%d",&f);
        }
		tail->next=NULL;
		j=ClearList(L);
		if (j==OK && L && !L->next && pm.len_used==pm.len_free+1)
        {
            for(i=1;i<pm.len_used;i++)
            {
                for(j=0;j<pm.len_free;j++)
                    if (pm.pused[i]==pm.pfree[j])
                        break;
                if (j>=pm.len_free)
                {
                    printf("未正确释放数据元素空间");
                    return 1;
                }
            }
            printf("OK");
        }
        else printf("ERROR!");
     }
	return 1;
}
