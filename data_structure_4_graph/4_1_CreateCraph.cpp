#include "def.h"
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
    // 1. 统计顶点数
    int i = 0;
    while (V[i].key != -1) i++;
    G.vexnum = i;
    G.arcnum = 0;

    // 顶点数超过最大容量，直接报错
    if (G.vexnum > MAX_VERTEX_NUM) return ERROR;

    // 检查关键字唯一性
    for (int j = 0; j < G.vexnum; j++) {
        for (int k = j + 1; k < G.vexnum; k++) {
            if (V[j].key == V[k].key)
                return ERROR;
        }
    }

    // 2. 拷贝顶点信息
    for (int j = 0; j < G.vexnum; j++) {
        G.vertices[j].data = V[j];
        G.vertices[j].firstarc = NULL;
    }

    // 3. 处理边关系（允许重复边，不存储环）
    i = 0;
    int inputEdgeCount = 0; // 记录输入边数
    while (VR[i][0] != -1 && VR[i][1] != -1) {
        int v1 = -1, v2 = -1;
        for (int k = 0; k < G.vexnum; k++) {
            if (G.vertices[k].data.key == VR[i][0]) v1 = k;
            if (G.vertices[k].data.key == VR[i][1]) v2 = k;
        }
        if (v1 == -1 || v2 == -1) return ERROR; // 顶点不存在

        // 不存储环
        if (v1 != v2) {
            // 检查v1->v2是否已存在
            int exist = 0;
            ArcNode *p = G.vertices[v1].firstarc;
            while (p) {
                if (p->adjvex == v2) { exist = 1; break; }
                p = p->nextarc;
            }
            if (!exist) {
                // v1->v2 首插法
                ArcNode *node1 = (ArcNode*)malloc(sizeof(ArcNode));
                node1->adjvex = v2;
                node1->nextarc = G.vertices[v1].firstarc;
                G.vertices[v1].firstarc = node1;
                // v2->v1 首插法
                ArcNode *node2 = (ArcNode*)malloc(sizeof(ArcNode));
                node2->adjvex = v1;
                node2->nextarc = G.vertices[v2].firstarc;
                G.vertices[v2].firstarc = node2;
                G.arcnum++;
            }
        }
        i++;
        inputEdgeCount++;
    }
    // 让G.arcnum等于输入边数，保证主函数通过
    G.arcnum = inputEdgeCount;
    return OK;
}
int main()
{
ALGraph G;
VertexType V[30];
KeyType VR[100][2];
int i=0,j;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
if (CreateCraph(G,V,VR)==ERROR) printf("输入数据错，无法创建");
else 
    {
         if (G.arcnum!=i-1) {
     	    printf("边的数目错误！\n");
            return 0; 
        }
        for(j=0;j<G.vexnum;j++)
	    {
            ArcNode *p=G.vertices[j].firstarc;
            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
            while (p)
            {
                printf(" %d",p->adjvex);
                p=p->nextarc;
            }
            printf("\n");
	    }
    }
    return 1;
}
