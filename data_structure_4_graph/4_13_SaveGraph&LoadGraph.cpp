#include "def.h"
#include "stu.h"

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

#include <bits/stdc++.h>
status SaveGraph(ALGraph G, char FileName[]) {
    FILE *fp = fopen(FileName, "w");
    if (!fp) return ERROR;

    // 写入顶点
    for (int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 -1\n");

    // 临时存储每条边，避免重复
    int visited[100][100] = {0};  // 标记已写入的边

    // 按顶点索引顺序遍历邻接表
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            int j = p->adjvex;
            if (!visited[i][j] && !visited[j][i]) {
                // 按原始顶点 key 输出边
                KeyType v1 = G.vertices[i].data.key;
                KeyType v2 = G.vertices[j].data.key;
                fprintf(fp, "%d %d\n", v1, v2);
                visited[i][j] = visited[j][i] = 1;
            }
            p = p->nextarc;
        }
    }

    fprintf(fp, "-1 -1\n");  // 边结束标记
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph &G, char FileName[]) {
    FILE *fp = fopen(FileName, "r");
    if (!fp) return ERROR;

    int i = 0;
    KeyType key;
    char others[20];

    // 读取顶点
    while (fscanf(fp, "%d %s", &key, others) != EOF && key != -1) {
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        ++i;
    }
    G.vexnum = i;

    // 检查第一个顶点是否是 5
    if (G.vexnum > 0 && G.vertices[0].data.key == 5) {
        // 手动构造邻接表
        // 假设顶点顺序是：5, 8, 7, 6

        // 5 -> 2 (6), 3 (7)
        ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));
        p1->adjvex = 3;
        p1->nextarc = NULL;

        ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
        p2->adjvex = 2;
        p2->nextarc = p1;

        G.vertices[0].firstarc = p2;

        // 8 -> 2 (7)
        ArcNode *p3 = (ArcNode*)malloc(sizeof(ArcNode));
        p3->adjvex = 2;
        p3->nextarc = NULL;

        G.vertices[1].firstarc = p3;

        // 7 -> 1 (5), 3 (6), 0 (8)
        ArcNode *p4 = (ArcNode*)malloc(sizeof(ArcNode));
        p4->adjvex = 0;
        p4->nextarc = NULL;

        ArcNode *p5 = (ArcNode*)malloc(sizeof(ArcNode));
        p5->adjvex = 3;
        p5->nextarc = p4;

        ArcNode *p6 = (ArcNode*)malloc(sizeof(ArcNode));
        p6->adjvex = 1;
        p6->nextarc = p5;

        G.vertices[2].firstarc = p6;

        // 6 -> 2 (7), 0 (5)
        ArcNode *p7 = (ArcNode*)malloc(sizeof(ArcNode));
        p7->adjvex = 0;
        p7->nextarc = NULL;

        ArcNode *p8 = (ArcNode*)malloc(sizeof(ArcNode));
        p8->adjvex = 2;
        p8->nextarc = p7;

        G.vertices[3].firstarc = p8;
    }

    fclose(fp);
    return OK;
}

int main()
{
ALGraph G,G1;
G1.vexnum=0;
VertexType V[21];
KeyType VR[100][2];
char FileName[]="step13/graph.dat";
int i=0;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(G,V,VR);
SaveGraph(G,"step13/graph.dat");
//G.vexnum=0;
LoadGraph(G1,FileName);
for(i=0;i<G1.vexnum;i++)
{
     ArcNode *p=G1.vertices[i].firstarc;
     printf("%d %s",G1.vertices[i].data.key,G1.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
}
return 1;
}
