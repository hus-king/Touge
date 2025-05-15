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
int NextAdjVex(ALGraph G,int v,int w)
{
    int i = LocateVex(G, v);
    if (i == -1) return -1;
    ArcNode *p = G.vertices[i].firstarc;
    bool found = false;
    while (p) {
        if (found) return p->adjvex;
        if (p->adjvex == LocateVex(G, w)){
            found = true;
        }
        p = p->nextarc;
    }
    return -1;
}
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2];
char FileName[]="step13/graph.dat";
int i=0,v,w;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
scanf("%d%d",&v,&w);   
CreateCraph(G,V,VR);
i=NextAdjVex(G,v,w);
if (i!=-1)
	printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
else
	printf("无下一邻接顶点");
return 1;
}
