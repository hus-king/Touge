#include "def.h"
#include "ctype.h"
#include "string.h"
#define free free0
#include "stu.h"
#undef free

struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(ArcNode));
    free(p);
}


status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
int i=0,j,one,two;
VertexType e;
do {
    G.vertices[i].data=V[i];
    G.vertices[i].firstarc=NULL;
} while (V[i++].key!=-1);
G.vexnum=i-1;
i=0;
while (VR[i][0]!=-1) {
    ArcNode *p;
    for(j=0;j<G.vexnum;j++)
        if (VR[i][0]==G.vertices[j].data.key)
        {
            one=j; break;
        }
    for(j=0;j<G.vexnum;j++)
        if (VR[i][1]==G.vertices[j].data.key)
        {
            two=j; break;
        }
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=two;p->nextarc=G.vertices[one].firstarc;G.vertices[one].firstarc=p;
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=one;p->nextarc=G.vertices[two].firstarc;G.vertices[two].firstarc=p;
    i++;
}
G.arcnum=i;
}
status DeleteArc(ALGraph &G,KeyType v,KeyType w){
    int i, j;
    ArcNode *p, *prev;
    // 查找顶点v和w的下标
    for(i=0; i<G.vexnum; i++)
        if(G.vertices[i].data.key == v) break;
    if(i == G.vexnum) return ERROR;
    for(j=0; j<G.vexnum; j++)
        if(G.vertices[j].data.key == w) break;
    if(j == G.vexnum) return ERROR;

    int found = 0;
    // 删除v->w
    prev = NULL;
    p = G.vertices[i].firstarc;
    while(p) {
        if(p->adjvex == j) {
            if(prev == NULL)
                G.vertices[i].firstarc = p->nextarc;
            else
                prev->nextarc = p->nextarc;
            free(p);
            found++;
            break;
        }
        prev = p;
        p = p->nextarc;
    }
    // 删除w->v
    prev = NULL;
    p = G.vertices[j].firstarc;
    while(p) {
        if(p->adjvex == i) {
            if(prev == NULL)
                G.vertices[j].firstarc = p->nextarc;
            else
                prev->nextarc = p->nextarc;
            free(p);
            found++;
            break;
        }
        prev = p;
        p = p->nextarc;
    }
    if(found == 2) {
        G.arcnum--;
        return OK;
    }
    return ERROR;
}
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2],v,w;
int i=0,j,k,arcs;
ArcNode *p;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(G,V,VR);
arcs=G.arcnum;
scanf("%d%d",&v,&w);
for(i=0;i<G.vexnum;i++)
    if (G.vertices[i].data.key==v) break;
for(j=0;j<G.vexnum;j++)
    if (G.vertices[j].data.key==w) break;
if (i<G.vexnum && j<G.vexnum)
{
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
        if (p->adjvex==j)
            pm.pused[pm.len_used++]=p;
    for(p=G.vertices[j].firstarc;p;p=p->nextarc)
        if (p->adjvex==i)
            pm.pused[pm.len_used++]=p;
}
i=DeleteArc(G,v,w);
if (i==OK && G.arcnum==arcs-1 && pm.len_free==pm.len_used)
{
    for(i=0;i<pm.len_used;i++)
    {
        for(j=0;j<pm.len_free;j++)
            if (pm.pused[i]==pm.pfree[j]) break;
        if (j>=pm.len_free)
        {
            printf("未正确释放表结点");
            return 1;
        }
    }
    for(i=0;i<G.vexnum;i++)
	{
     p=G.vertices[i].firstarc;
     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
	}
}
else printf("删除弧操作失败");
return 1;
}




