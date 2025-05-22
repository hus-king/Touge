status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
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

status DestroyGraph(ALGraph &G){
    int i;
    for(i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p) {
            ArcNode *q = p->nextarc;
            free(p);
            p = q;
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}
status LocateVex(ALGraph G, KeyType u){
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
int FirstAdjVex(ALGraph G, int u)
{
    int i = LocateVex(G, u);
    if (i == -1) return -1; // 顶点不存在
    ArcNode *p = G.vertices[i].firstarc;
    if (p) return p->adjvex; // 返回第一个邻接顶点
    return -1; // 没有邻接顶点
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
status InsertVex(ALGraph &G, VertexType value)
{
    // 检查顶点个数是否已满
    if (G.vexnum >= MAX_VERTEX_NUM)
        return ERROR;
    // 检查关键字是否重复
    for (int j = 0; j < G.vexnum; j++) {
        if (G.vertices[j].data.key == value.key)
            return ERROR;
    }
    // 插入新顶点
    G.vertices[G.vexnum].data = value;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
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
status InsertArc(ALGraph &G,KeyType v,KeyType w){
    int i,j;
    ArcNode *p, *q;
    for(i=0;i<G.vexnum;i++)
        if (G.vertices[i].data.key==v) break;
    if (i==G.vexnum) return ERROR;
    for(j=0;j<G.vexnum;j++)
        if (G.vertices[j].data.key==w) break;
    if (j==G.vexnum) return ERROR;
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
        if (p->adjvex==j) return ERROR;
    // v->w首插
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=j; p->nextarc=G.vertices[i].firstarc; G.vertices[i].firstarc=p;
    // w->v首插
    q=(ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex=i; q->nextarc=G.vertices[j].firstarc; G.vertices[j].firstarc=q;
    G.arcnum++;
    return OK;
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
status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    int visited[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            // 入队并访问
            queue[rear++] = v;
            visited[v] = 1;
            visit(G.vertices[v].data);
            while (front < rear) {
                int u = queue[front++];
                for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
                    if (!visited[p->adjvex]) {
                        queue[rear++] = p->adjvex;
                        visited[p->adjvex] = 1;
                        visit(G.vertices[p->adjvex].data);
                    }
                }
            }
        }
    }
    return OK;
}
status SaveGraph(ALGraph G, char FileName[]) {
    FILE *fp = fopen(FileName, "w");
    if (!fp) return ERROR;

    for (int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 -1\n");

    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            if (i < p->adjvex)
                fprintf(fp, "%d %d\n", G.vertices[i].data.key, G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
    }
    fprintf(fp, "-1 -1\n");

    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph &G, char FileName[]) {
    FILE *fp = fopen(FileName, "r");
    if (!fp) return ERROR;

    int i = 0;
    KeyType key;
    char others[20];

    while (fscanf(fp, "%d %s", &key, others) != EOF && key != -1) {
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        i++;
    }
    G.vexnum = i;

    KeyType v1, v2;
    while (fscanf(fp, "%d %d", &v1, &v2) != EOF && v1 != -1) {
        int one = -1, two = -1;
        for (int j = 0; j < G.vexnum; j++) {
            if (G.vertices[j].data.key == v1) one = j;
            if (G.vertices[j].data.key == v2) two = j;
        }

        if (one == -1 || two == -1) continue;

        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = two;
        p->nextarc = G.vertices[one].firstarc;
        G.vertices[one].firstarc = p;

        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = one;
        p->nextarc = G.vertices[two].firstarc;
        G.vertices[two].firstarc = p;
    }

    fclose(fp);
    return OK;
}