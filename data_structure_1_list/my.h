#include "string.h"
status InitList(SqList &L)//初始化线性表
{
    if(L.elem) return INFEASIBLE; //线性表已经存在，不能重复初始化
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); //申请空间
    L.listsize=LIST_INIT_SIZE; //设置线性表的空间容量初值
    L.length=0; //设置元素个数初始值
    if (!L.elem) return INFEASIBLE; //申请失败
    else return OK; //申请成功
}
status DestroyList(SqList &L) //销毁线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能销毁
    free(L.elem); //释放线性表的存储空间
    L.elem=NULL; //将线性表置为空
    L.length=0; //设置元素个数初始值
    L.listsize=0; //设置线性表的空间容量初值
    return OK; //销毁成功
}
status ClearList(SqList &L) //清空线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能清空
    L.length=0; //设置元素个数初始值
    return OK; //清空成功
}
status ListEmpty(SqList L) //判线性表是否为空
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能判空
    if (L.length==0) return OK; //线性表为空
    else return ERROR; //线性表不空
}
status ListLength(SqList L) //求线性表的长度
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能求长
    return L.length; //返回线性表的长度
}
status GetElem(SqList L,int i,ElemType &e) //求线性表的第i个元素
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能求元素
    if (i<1 || i>L.length) return ERROR; //i不合法
    e=L.elem[i-1]; //获取第i个元素
    return OK; //获取成功
}
status LocateElem(SqList L,ElemType e) //查找线性表中元素e的位置
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    for (int i=0;i<L.length;i++)
        if (L.elem[i]==e) return i+1; //返回元素e的位置
    return ERROR; //未找到元素e
}
status PriorElem(SqList L,ElemType e,int &pre) //查找线性表中元素e的前驱
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L.length==0) return ERROR; //线性表为空，不能查找
    for (int i=1;i<L.length;i++)
        if (L.elem[i]==e) { pre=L.elem[i-1]; return OK; } //返回元素e的前驱
    return ERROR; //未找到元素e
}
status NextElem(SqList L,ElemType e,int &next) //查找线性表中元素e的后继
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能查找
    if (L.length==0) return ERROR; //线性表为空，不能查找
    for (int i=0;i<L.length-1;i++)
        if (L.elem[i]==e) { next=L.elem[i+1]; return OK; } //返回元素e的后继
    return ERROR; //未找到元素e
}
status ListInsert(SqList &L,int i,ElemType e) //在第i个位置插入元素e
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能插入
    if (i<1 || i>L.length+1) return ERROR; //i不合法
    if (L.length>=L.listsize) { //空间不足，申请扩展
        ElemType *newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType)); //申请扩展空间
        if (!newbase) return OVERFLOW; //申请失败
        L.elem=newbase; //扩展成功，更新基址
        L.listsize+=LISTINCREMENT; //更新线性表的空间容量
    }
    ElemType *q=&L.elem[i-1]; //指向第i个元素的位置
    for (ElemType *p=&L.elem[L.length-1]; p>=q; p--) *(p+1)=*p; //将第i个元素及其后面的元素后移一位
    *q=e; //插入新元素e
    L.length++; //线性表长度加1
    return OK; //插入成功
}
status ListDelete(SqList &L,int i,ElemType &e) //删除线性表的第i个元素
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能删除
    if (i<1 || i>L.length) return ERROR; //i不合法
    e=L.elem[i-1]; //获取第i个元素
    for (ElemType *q=&L.elem[i-1]; q<&L.elem[L.length-1]; q++) *q=*(q+1); //将第i+1个元素及其后面的元素前移一位
    L.length--; //线性表长度减1
    return OK; //删除成功
}
status ListTraverse(SqList L) //遍历线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能遍历
    if (L.length==0) return OK; //线性表为空，遍历成功
    for (int i=0;i<L.length;i++)
		if(i==L.length-1) printf("%d",L.elem[i]); //输出线性表的最后一个元素
		else  printf("%d ",L.elem[i]); //输出线性表的元素
    return OK; //遍历成功
}
status SaveList(SqList L,char FileName[])
{
    FILE *fp;
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能写文件
    if ((fp=fopen(FileName,"w"))==NULL) return ERROR; //打开文件失败
    for (int i=0;i<L.length;i++)
        fprintf(fp,"%d ",L.elem[i]); //写入线性表的元素
    fclose(fp); //关闭文件
    return OK; //写文件成功
}
status LoadList(SqList &L,char FileName[])
{
    FILE *fp;
    if ((fp=fopen(FileName,"r"))==NULL) return ERROR; //打开文件失败
    if(L.elem) return INFEASIBLE; //线性表已经存在，不能重复初始化
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType)); //申请空间
    if (!L.elem) return OVERFLOW; //申请失败
    L.listsize=LIST_INIT_SIZE; //设置线性表的空间容量初值
    L.length=0; //设置元素个数初始值
    while (fscanf(fp,"%d",&L.elem[L.length])==1) //读入线性表的元素
        L.length++; //线性表长度加1
    fclose(fp); //关闭文件
    return OK; //读文件成功
}
status AddList(LISTS &Lists,char ListName[]) //添加线性表
{
    if (Lists.length>=10) return ERROR; //线性表个数超过限制
    strcpy(Lists.elem[Lists.length].name,ListName); //复制线性表名称
    if (Lists.elem[Lists.length].L.elem != NULL) {
        Lists.elem[Lists.length].L.elem = NULL; // 避免重复释放
    }
    InitList(Lists.elem[Lists.length].L); //初始化线性表
    Lists.length++; //线性表个数加1
    return OK; //添加成功
}
status RemoveList(LISTS &Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            for (int j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            return i + 1; // Return 1-based index
        }
    }
    return 0; // Not found
}