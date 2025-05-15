#include "def.h"

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
int LocateVex(ALGraph G, KeyType u){
    for(int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key == u)
            return i;
    }
    return -1;
}
status PutVex(ALGraph &G, int u, VertexType value)
{
    int i = LocateVex(G, u);
    if (i == -1) return ERROR; // 顶点不存在
    // 检查关键字是否重复
    for (int j = 0; j < G.vexnum; j++) {
        if (j != i && G.vertices[j].data.key == value.key)
            return ERROR;
    }
    G.vertices[i].data = value;
    return OK;
}
int main()
{
ALGraph G;
VertexType V[21],value;
KeyType VR[100][2];
char FileName[]="step13/graph.dat";
int i=0,u;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
scanf("%d",&u);   
scanf("%d%s",&value.key,value.others);
CreateCraph(G,V,VR);
i=PutVex(G,u,value);
if (i==OK)
   for(i=0;i<G.vexnum;i++)
     printf(" %d %s",G.vertices[i].data.key,G.vertices[i].data.others);
else
	printf("赋值操作失败");
return 1;
}
