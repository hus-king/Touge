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
int LocateVex(ALGraph G, KeyType u){
    for(int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key == u)
            return i;
    }
    return -1;
}
status DeleteVex(ALGraph &G,KeyType v){
    // 保证图中至少有一个顶点
    if (G.vexnum <= 1) return ERROR;
    int i = LocateVex(G, v);
    if (i == -1) return ERROR; // 顶点不存在

    // 1. 释放自身的所有弧结点（不减arcnum）
    ArcNode *p = G.vertices[i].firstarc;
    while (p) {
        ArcNode *q = p->nextarc;
        free(p);
        p = q;
    }
    G.vertices[i].firstarc = NULL;

    // 2. 删除其他顶点邻接表中指向该顶点的弧，并修正adjvex
    for (int j = 0; j < G.vexnum; j++) {
        if (j == i) continue;
        ArcNode *prev = NULL, *curr = G.vertices[j].firstarc;
        while (curr) {
            if (curr->adjvex == i) {
                ArcNode *toDel = curr;
                if (prev == NULL) {
                    G.vertices[j].firstarc = curr->nextarc;
                } else {
                    prev->nextarc = curr->nextarc;
                }
                curr = curr->nextarc;
                free(toDel);
                G.arcnum--; // 只在这里减arcnum
            } else {
                // 如果指向被删顶点之后的顶点，编号要减一
                if (curr->adjvex > i) {
                    curr->adjvex--;
                }
                prev = curr;
                curr = curr->nextarc;
            }
        }
    }

    // 3. 顶点数组前移
    for (int j = i; j < G.vexnum - 1; j++) {
        G.vertices[j] = G.vertices[j + 1];
    }
    G.vexnum--;
    return OK;
}
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2];
int i=0,j,v,del_arcs=0,arcs,vexs;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(G,V,VR);
scanf("%d",&v);
for(i=0;i<G.vexnum;i++)
    if (G.vertices[i].data.key==v) break;
if (i<G.vexnum)
{
    ArcNode *p;
    arcs=G.arcnum;
    vexs=G.vexnum;
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
    {
        pm.pused[pm.len_used++]=p;
        del_arcs++;
    }
    for(j=0;j<G.vexnum;j++)
    {
        for(p=G.vertices[j].firstarc;p;p=p->nextarc)
            if (p->adjvex==i)
                pm.pused[pm.len_used++]=p;
    }
}
i=DeleteVex(G,v);
if (i==OK && G.arcnum==arcs-del_arcs&&vexs==G.vexnum+1&&pm.len_used==pm.len_free)
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
     ArcNode *p=G.vertices[i].firstarc;
     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
	}
}
else printf("删除顶点操作失败");
return 1;
}

