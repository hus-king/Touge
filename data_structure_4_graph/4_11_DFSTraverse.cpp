#include "def.h"
#include "stu.h"

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
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
}

void DFS(ALGraph &G, int v, int visited[], void (*visit)(VertexType)) {
    visit(G.vertices[v].data);
    visited[v] = 1;
    for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex, visited, visit);
        }
    }
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType)){
    int visited[MAX_VERTEX_NUM] = {0};
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            DFS(G, v, visited, visit);
        }
    }
    return OK;
}

int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2],v,w;
int i=0;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(G,V,VR);
DFSTraverse(G,visit);
return 1;
}
