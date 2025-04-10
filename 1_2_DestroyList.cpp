#include "def.h"
#include "string.h"
#include "ctype.h"
status DestroyList(SqList &L) //销毁线性表
{
    if (L.elem==NULL) return INFEASIBLE; //线性表不存在，不能销毁
    free(L.elem); //释放线性表的存储空间
    L.elem=NULL; //将线性表置为空
    L.length=0; //设置元素个数初始值
    L.listsize=0; //设置线性表的空间容量初值
    return OK; //销毁成功
}


status lex(FILE *fp,char word[])   //仅查找字母型标识符
{
    char c,c1,i;
    while ((c=fgetc(fp))!=EOF && !feof(fp))
    {
        if (isspace(c)) continue;
        if (c=='/')
        {
            c==fgetc(fp);
            if (c==EOF) return ERROR;
            if (c=='/')
            {
                while ((c=fgetc(fp))!='\n') 
                       if (c==EOF) return ERROR;
                continue;
            }
            if (c=='*')
            {
                c=fgetc(fp);
                if (c==EOF) return ERROR;
                do
                {
                    c1=c;
                    c=fgetc(fp);
                    if (c==EOF) return ERROR;
                 } while (c1!='*' || c!='/');
                continue;
            }
        }
        if (!isalpha(c)) continue;
        i=0;
        do {
            	word[i++]=c;
            } while (isalpha(c=fgetc(fp)));
        if (isspace(c)|| !(c>='0' && c<='9') || c==EOF)
        {
            word[i]='\0';
            return OK;
        }
    }
    return ERROR;
}
status match(char fileName[],char keyword[])
{
    FILE *fp;
    char word[50];
    fp=fopen(fileName,"r");
    if (!fp) {printf("文件打开失败"); return FALSE;}
    while (lex(fp,word)==OK){
        if (strcmp(keyword,word))
             continue;
        fclose(fp);
        return TRUE;
    }
    fclose(fp);
    return FALSE;
}

int main()
{
SqList L;
int f,i,j,e;
scanf("%d",&f);
if (f==0)
	{
	    L.elem=NULL;
        j=DestroyList(L);
        if (j==INFEASIBLE) printf("INFEASIBLE");
        else printf("不能对不存在的线性表进行销毁操作！");
	}
else
     { 
        L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
        L.length=0;
        L.listsize= 10;
       
        j=DestroyList(L);
        if (j==OK) 
            if (match("src/step02/stu.h","free")==FALSE || L.elem)
                printf("未正确释放数据元素空间");
            else printf("OK");
        else printf("ERROR");
     }
return 1;
}
