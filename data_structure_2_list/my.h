status InitList(LinkList &L) {
    if (L) return INFEASIBLE; // 如果 L 已经存在，则返回 INFEASIBLE
    L = (LinkList)malloc(sizeof(LNode)); // 分配头结点空间
    if (!L) return OVERFLOW; // 如果分配失败，返回 OVERFLOW
    L->next = NULL; // 初始化头结点的 next 指针为 NULL
    return OK; // 返回成功
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
status ClearList(LinkList &L) //清空线性表
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能清空
    LinkList p,q;
    p=L->next; //指向第一个结点
    while (p!=NULL) //遍历链表
    {
        q=p->next; //保存下一个结点的地址
        free(p); //释放当前结点的空间
        p=q; //移动到下一个结点
    }
    L->next=NULL; //清空链表
    return OK; //清空成功
}
status ListEmpty(LinkList L) //判线性表是否为空
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能判空
    if (L->next==NULL) return OK; //线性表为空
    else return ERROR; //线性表不空
}
status ListLength(LinkList L) //求线性表的长度
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能求长
    int len=0;
    LNode *p=L->next; //从第一个结点开始
    while (p) { //遍历链表
        len++;
        p=p->next; //指向下一个结点
    }
    return len; //返回线性表的长度
}
status GetElem(LinkList L,int i,ElemType &e) //求线性表的第i个元素
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能求元素
    if (i<1) return ERROR; //i不合法
    LNode *p=L->next; //指向第一个结点
    int j=1; //计数器
    while (p && j<i) { //遍历链表
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (j!=i) return ERROR; //未找到第i个元素
    e=p->data; //获取第i个元素
    return OK; //获取成功
}
status LocateElem(LinkList L,ElemType e) //查找线性表中元素e的位置
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    int i=1; //计数器
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        if (p->data==e) return i; //找到元素e，返回位置
        p=p->next; //指向下一个结点
        i++; //计数器加1
    }
    return ERROR; //未找到元素e
}
status PriorElem(LinkList L,ElemType e,int &pre) //查找线性表中元素e的前驱
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L->next==NULL) return ERROR; //线性表为空，不能查找
    LNode *p=L->next; //指向第一个结点
    int j=1; //计数器
    while (p && p->data!=e) { //遍历链表
        pre=p->data; //保存前驱元素
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (j==1 || p==NULL) return ERROR; //未找到元素e或没有前驱元素
    return OK; //返回成功
}
status NextElem(LinkList L,ElemType e,int &next) //查找线性表中元素e的后继
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能查找
    LNode *p=L->next; //指向第一个结点
    while (p && p->data!=e) { //遍历链表
        p=p->next; //指向下一个结点
    }
    if (p==NULL || p->next==NULL) return ERROR; //未找到元素e或没有后继元素
    next=p->next->data; //获取后继元素
    return OK; //返回成功
}
status ListInsert(LinkList &L, int i, ElemType e) // 在第i个位置插入元素e
{
    if (L == NULL) return INFEASIBLE; // 线性表不存在，不能插入
    if (i < 1) return ERROR; // i不合法

    LNode *p = L; // 指向头结点
    int j = 0; // 计数器，从头结点开始计数
    while (p && j < i - 1) { // 遍历链表，找到第i-1个结点
        p = p->next; // 指向下一个结点
        j++; // 计数器加1
    }
    if (!p || j != i - 1) return ERROR; // 未找到第i-1个位置或位置不合法

    LNode *s = (LNode *)malloc(sizeof(LNode)); // 申请新结点空间
    if (!s) return ERROR; // 内存分配失败
    s->data = e; // 设置新结点的数据域
    s->next = p->next; // 将新结点的next指针指向原来的第i个结点
    p->next = s; // 将原来的第i-1个结点的next指针指向新结点
    return OK; // 返回成功
}
status ListDelete(LinkList &L,int i,ElemType &e) //删除线性表的第i个元素
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能删除
    if (i<1) return ERROR; //i不合法
    LNode *p=L,*q; //p指向头结点，q指向要删除的结点
    int j=0; //计数器，从头结点开始计数
    while (p && j<i-1) { //遍历链表，找到第i-1个结点
        p=p->next; //指向下一个结点
        j++; //计数器加1
    }
    if (!p || j!=i-1) return ERROR; //未找到第i-1个位置或位置不合法
    q=p->next; //q指向要删除的结点
    if (!q) return ERROR; //要删除的结点不存在
    e=q->data; //获取要删除的结点的数据域
    p->next=q->next; //将第i-1个结点的next指针指向第i+1个结点
    free(q); //释放要删除的结点的空间
    return OK; //返回成功
}
status ListTraverse(LinkList L) //遍历线性表
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能遍历
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        printf("%d ",p->data); //输出当前结点的数据域
        p=p->next; //指向下一个结点
    }
    return OK; //返回成功
}
status SaveList(LinkList L,char FileName[]) //将线性表写入文件
{
    if (L==NULL) return INFEASIBLE; //线性表不存在，不能写入
    FILE *fp=fopen(FileName,"w"); //打开文件
    if (!fp) return ERROR; //打开失败
    LNode *p=L->next; //指向第一个结点
    while (p) { //遍历链表
        fprintf(fp,"%d ",p->data); //写入数据
        p=p->next; //指向下一个结点
    }
    fclose(fp); //关闭文件
    return OK; //返回成功
}
status LoadList(LinkList &L,char FileName[]) //从文件中读取线性表
{
    if (L) return INFEASIBLE; //线性表已存在，不能读取
    FILE *fp=fopen(FileName,"r"); //打开文件
    if (!fp) return ERROR; //打开失败
    L=(LinkList)malloc(sizeof(LNode)); //分配头结点空间
    if (!L) return OVERFLOW; //内存分配失败
    L->next=NULL; //初始化头结点的next指针为NULL
    LNode *p=L; //指向当前结点
    int data;
    while (fscanf(fp,"%d",&data)==1) { //读取数据
        LNode *s=(LNode*)malloc(sizeof(LNode)); //分配新结点空间
        if (!s) return OVERFLOW; //内存分配失败
        s->data=data; //设置数据域
        s->next=NULL; //设置next指针为NULL
        p->next=s; //将新结点链接到链表中
        p=s; //移动到新结点
    }
    fclose(fp); //关闭文件
    return OK; //返回成功
}