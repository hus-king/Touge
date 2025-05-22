#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "def.h"
#include "my.h"

#define MAX_GRAPH_NUM 10

// 多图管理结构体
typedef struct {
    struct {
        char name[30];
        ALGraph G;
    } elem[MAX_GRAPH_NUM];
    int length;
} GRAPHS;

// 查找图，返回位置（1开始），未找到返回0
int LocateGraph(GRAPHS &Graphs, const char name[]) {
    for (int i = 0; i < Graphs.length; i++) {
        if (strcmp(Graphs.elem[i].name, name) == 0)
            return i + 1;
    }
    return 0;
}

// 添加图
status AddGraph(GRAPHS &Graphs, const char name[]) {
    if (Graphs.length >= MAX_GRAPH_NUM) return ERROR;
    strcpy(Graphs.elem[Graphs.length].name, name);
    Graphs.elem[Graphs.length].G.vexnum = 0;
    Graphs.elem[Graphs.length].G.arcnum = 0;
    Graphs.length++;
    return OK;
}

// 移除图
status RemoveGraph(GRAPHS &Graphs, const char name[]) {
    int pos = LocateGraph(Graphs, name);
    if (pos == 0) return ERROR;
    DestroyGraph(Graphs.elem[pos - 1].G);
    for (int i = pos; i < Graphs.length; i++) {
        Graphs.elem[i - 1] = Graphs.elem[i];
    }
    Graphs.length--;
    return OK;
}

// 访问函数
void visit(VertexType v) {
    printf("%d(%s) ", v.key, v.others);
}

// 附加功能1：距离小于k的顶点集合（BFS实现）
void VerticesSetLessThanK(ALGraph &G, KeyType v, int k) {
    int idx = LocateVex(G, v);
    if (idx == -1) {
        printf("顶点不存在！\n");
        return;
    }
    int visited[MAX_VERTEX_NUM] = {0};
    int dist[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    queue[rear++] = idx;
    visited[idx] = 1;
    while (front < rear) {
        int u = queue[front++];
        for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
            int w = p->adjvex;
            if (!visited[w]) {
                dist[w] = dist[u] + 1;
                if (dist[w] < k) {
                    printf("%d(%s) ", G.vertices[w].data.key, G.vertices[w].data.others);
                    queue[rear++] = w;
                }
                visited[w] = 1;
            }
        }
    }
    printf("\n");
}

// 附加功能2：最短路径长度（BFS实现）
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w) {
    int start = LocateVex(G, v);
    int end = LocateVex(G, w);
    if (start == -1 || end == -1) return -1;
    int visited[MAX_VERTEX_NUM] = {0};
    int dist[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        int u = queue[front++];
        if (u == end) return dist[u];
        for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
            int v = p->adjvex;
            if (!visited[v]) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }
    return -1;
}

// 附加功能3：连通分量个数
int ConnectedComponentsNums(ALGraph &G) {
    int visited[MAX_VERTEX_NUM] = {0};
    int count = 0;
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            // BFS
            int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
            queue[rear++] = v;
            visited[v] = 1;
            while (front < rear) {
                int u = queue[front++];
                for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
                    int w = p->adjvex;
                    if (!visited[w]) {
                        queue[rear++] = w;
                        visited[w] = 1;
                    }
                }
            }
            count++;
        }
    }
    return count;
}

// 直观打印图（邻接表结构）
// 以每个顶点为一行，显示顶点及其所有邻接点
void PrintGraph(ALGraph &G) {
    printf("图的邻接表结构如下：\n");
    for (int i = 0; i < G.vexnum; i++) {
        printf("%d(%s):", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            printf(" -> %d(%s)", G.vertices[p->adjvex].data.key, G.vertices[p->adjvex].data.others);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// 单图操作菜单
void SingleGraphMenu(ALGraph &G) {
    int op = 1;
    while (op) {
        system("clear");
        printf("\n\n");
        printf("      单个图操作菜单\n");
        printf("-------------------------------------------------\n");
        printf(" 1. 创建图           9. 插入弧\n");
        printf(" 2. 销毁图           10. 删除弧\n");
        printf(" 3. 查找顶点         11. 保存/加载图\n");
        printf(" 4. 顶点赋值         12. 距离小于k的顶点集合\n");
        printf(" 5. 深度优先遍历     13. 顶点间最短路径长度\n");
        printf(" 6. 广度优先遍历     14. 图的连通分量个数\n");
        printf(" 7. 插入顶点         15. 图的文件保存/加载\n");
        printf(" 8. 删除顶点         16. 直观打印图\n");
        printf(" 0. 返回上级\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~16]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: { // 创建图
                VertexType V[MAX_VERTEX_NUM + 1];
                KeyType VR[MAX_VERTEX_NUM * MAX_VERTEX_NUM][2];
                int i = 0;
                printf("请依次输入顶点key和others(以 -1 nil 结束)\n");
                while (1) {
                    scanf("%d", &V[i].key);
                    scanf("%s", V[i].others);
                    if (V[i].key == -1) break;
                    i++;
                }
                V[i].key = -1; strcpy(V[i].others, "nil");
                i = 0;
                printf("请依次输入边的两个顶点key(以 -1 -1 结束)\n");
                while (1) {
                    scanf("%d%d", &VR[i][0], &VR[i][1]);
                    if (VR[i][0] == -1 && VR[i][1] == -1) break;
                    i++;
                }
                VR[i][0] = VR[i][1] = -1;
                int edgeInputCount = i;
                if (CreateGraph(G, V, VR) == OK) {
                    if (G.arcnum != edgeInputCount) {
                        printf("边的数目错误！\n");
                        getchar();
                        break;
                    }
                    printf("图创建成功！\n");
                    for (int j = 0; j < G.vexnum; j++) {
                        ArcNode *p = G.vertices[j].firstarc;
                        printf("%d %s", G.vertices[j].data.key, G.vertices[j].data.others);
                        while (p) {
                            printf(" %d", p->adjvex);
                            p = p->nextarc;
                        }
                        printf("\n");
                    }
                } else {
                    printf("图创建失败（关键字不唯一或边非法）！\n");
                }
                getchar();
                getchar();
                break;
            }
            case 2: { // 销毁图
                DestroyGraph(G);
                printf("图销毁成功！\n");
                getchar();
                getchar();
                break;
            }
            case 3: { // 查找顶点
                KeyType key;
                printf("请输入要查找的顶点关键字：");
                scanf("%d", &key);
                int pos = LocateVex(G, key);
                if (pos != -1)
                    printf("顶点位置为：%d\n", pos);
                else
                    printf("未找到该顶点！\n");
                getchar();
                getchar();
                break;
            }
            case 4: { // 顶点赋值
                KeyType key;
                VertexType value;
                printf("请输入要赋值的顶点关键字：");
                scanf("%d", &key);
                printf("请输入新值 key: ");
                scanf("%d", &value.key);
                printf("请输入新值 others: ");
                scanf("%s", value.others);
                if (PutVex(G, key, value) == OK)
                    printf("赋值成功！\n");
                else
                    printf("赋值失败（关键字冲突或不存在）！\n");
                getchar();
                getchar();
                break;
            }
            case 5: { // 深度优先遍历
                printf("深度优先遍历：");
                DFSTraverse(G, visit);
                printf("\n");
                getchar();
                break;
            }
            case 6: { // 广度优先遍历
                printf("广度优先遍历：");
                BFSTraverse(G, visit);
                printf("\n");
                getchar();
                break;
            }
            case 7: { // 插入顶点
                VertexType value;
                printf("请输入新顶点 key: ");
                scanf("%d", &value.key);
                printf("请输入新顶点 others: ");
                scanf("%s", value.others);
                if (InsertVex(G, value) == OK)
                    printf("插入成功！\n");
                else
                    printf("插入失败（关键字冲突或已满）！\n");
                getchar();
                getchar();
                break;
            }
            case 8: { // 删除顶点
                KeyType key;
                printf("请输入要删除的顶点关键字：");
                scanf("%d", &key);
                if (DeleteVex(G, key) == OK)
                    printf("删除成功！\n");
                else
                    printf("删除失败（顶点不存在或只剩一个顶点）！\n");
                getchar();
                getchar();
                break;
            }
            case 9: { // 插入弧
                KeyType v, w;
                printf("请输入插入弧的两个顶点关键字：");
                scanf("%d%d", &v, &w);
                if (InsertArc(G, v, w) == OK)
                    printf("插入成功！\n");
                else
                    printf("插入失败（顶点不存在或弧已存在）！\n");
                getchar();
                break;
            }
            case 10: { // 删除弧
                KeyType v, w;
                printf("请输入要删除弧的两个顶点关键字：");
                scanf("%d%d", &v, &w);
                if (DeleteArc(G, v, w) == OK)
                    printf("删除成功！\n");
                else
                    printf("删除失败（弧不存在）！\n");
                getchar();
                getchar();
                break;
            }
            case 11: { // 保存/加载图
                int subop;
                char filename[100];
                printf("1. 保存图到文件\n2. 从文件加载图\n请选择：");
                scanf("%d", &subop);
                printf("请输入文件名：");
                scanf("%s", filename);
                if (subop == 1) {
                    if (SaveGraph(G, filename) == OK)
                        printf("保存成功！\n");
                    else
                        printf("保存失败！\n");
                } else if (subop == 2) {
                    if (LoadGraph(G, filename) == OK)
                        printf("加载成功！\n");
                    else
                        printf("加载失败！\n");
                } else {
                    printf("无效操作！\n");
                }
                getchar();
                getchar();
                break;
            }
            case 12: { // 距离小于k的顶点集合
                KeyType v; int k;
                printf("请输入顶点关键字和距离k：");
                scanf("%d%d", &v, &k);
                printf("距离小于%d的顶点集合：", k);
                VerticesSetLessThanK(G, v, k);
                getchar();
                getchar();
                break;
            }
            case 13: { // 顶点间最短路径长度
                KeyType v, w;
                printf("请输入两个顶点关键字：");
                scanf("%d%d", &v, &w);
                int len = ShortestPathLength(G, v, w);
                if (len != -1)
                    printf("最短路径长度为：%d\n", len);
                else
                    printf("不可达！\n");
                getchar();
                getchar();
                break;
            }
            case 14: { // 图的连通分量个数
                printf("连通分量个数为：%d\n", ConnectedComponentsNums(G));
                getchar();
                break;
            }
            case 15: { // 图的文件保存/加载
                int subop;
                char filename[100];
                printf("1. 保存图到文件\n2. 从文件加载图\n请选择：");
                scanf("%d", &subop);
                printf("请输入文件名：");
                scanf("%s", filename);
                if (subop == 1) {
                    if (SaveGraph(G, filename) == OK)
                        printf("保存成功！\n");
                    else
                        printf("保存失败！\n");
                } else if (subop == 2) {
                    if (LoadGraph(G, filename) == OK)
                        printf("加载成功！\n");
                    else
                        printf("加载失败！\n");
                } else {
                    printf("无效操作！\n");
                }
                getchar();
                getchar();
                break;
            }
            case 16: { // 直观打印图
                PrintGraph(G);
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

// 多图管理主函数
int main() {
    GRAPHS Graphs;
    Graphs.length = 0;
    int op = 1;
    while (op) {
        system("clear");
        printf("\n\n");
        printf("      多个图管理菜单 \n");
        printf("-------------------------------------------------\n");
        printf("1. 添加图         4. 显示所有图\n");
        printf("2. 移除图         5. 操作单个图\n");
        printf("3. 查找图         0. 退出\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1: {
                char name[30];
                printf("请输入新图的名称：");
                scanf("%s", name);
                if (LocateGraph(Graphs, name) > 0) {
                    printf("图名称 '%s' 已存在，添加失败！\n", name);
                } else {
                    if (AddGraph(Graphs, name) == OK) {
                        printf("图 '%s' 添加成功！\n", name);
                    } else {
                        printf("图添加失败！\n");
                    }
                }
                getchar();
                break;
            }
            case 2: {
                char name[30];
                printf("请输入要移除的图名称：");
                scanf("%s", name);
                if (RemoveGraph(Graphs, name) == OK)
                    printf("图 '%s' 移除成功！\n", name);
                else
                    printf("图移除失败！\n");
                getchar();
                break;
            }
            case 3: {
                char name[30];
                printf("请输入要查找的图名称：");
                scanf("%s", name);
                int pos = LocateGraph(Graphs, name);
                if (pos > 0)
                    printf("图 '%s' 的位置为：%d\n", name, pos);
                else
                    printf("未找到图 '%s'！\n", name);
                getchar();
                break;
            }
            case 4: {
                if (Graphs.length == 0) {
                    printf("当前没有图！\n");
                } else {
                    printf("当前图列表：\n");
                    for (int i = 0; i < Graphs.length; i++) {
                        printf("  %d. %s\n", i + 1, Graphs.elem[i].name);
                    }
                }
                getchar();
                break;
            }
            case 5: {
                char name[30];
                printf("请输入要操作的图名称：");
                scanf("%s", name);
                int pos = LocateGraph(Graphs, name);
                if (pos > 0) {
                    printf("已切换到图 '%s'！\n", name);
                    SingleGraphMenu(Graphs.elem[pos - 1].G);
                } else {
                    printf("未找到图 '%s'！\n", name);
                }
                getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
