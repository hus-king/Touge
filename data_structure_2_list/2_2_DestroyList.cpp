#include "def.h"
#include "string.h"
#include "ctype.h"
#define free free0
#undef free
struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(LNode));
    free(p);
}
status DestroyList(LinkList &L)
{
    if (L==NULL) return INFEASIBLE;
    LinkList p,q;
    p=L->next;
    free(L);
    while (p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L=NULL;
    return OK;
}


int main()
{
	LinkList L,tail;
	int f,i,j;
	scanf("%d",&f);
	if (f==0)
	{
		L=NULL;
		j=DestroyList(L);
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
		j=DestroyList(L);
		if (j==OK && !L)
        {
            for(i=0;i<pm.len_used;i++)
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
