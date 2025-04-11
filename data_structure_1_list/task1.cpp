/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
//status DestroyList(SqList& L);
//status ClearList(SqList&L);
//status ListEmpty(SqList L);
//intListLength(SqList L);
//status GetElem(SqListL,inti,ElemType& e);
//status LocateElem(SqListL,ElemType e); //简化过
//status PriorElem(SqListL,ElemTypecur,ElemType&pre_e);
//status NextElem(SqListL,ElemTypecur,ElemType&next_e);
//status ListInsert(SqList&L,inti,ElemType e);
status ListDelete(SqList&L,int i,ElemType& e);
status ListTrabverse(SqList L);  //简化过
/*--------------------------------------------*/
int main(void){
SqList L;  int op=1;
while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem\n");
	printf("    	  2. DestroyList8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 //printf("\n----IntiList功能待实现！\n");
		 if(InitList(L)==OK) printf("线性表创建成功！\n");
		     else printf("线性表创建失败！\n");
		 getchar();getchar();
		 break;
	   case 2:
		 printf("\n----DestroyList功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 3:
		 printf("\n----ClearList功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 4:
		 printf("\n----ListEmpty功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 5:
		 printf("\n----ListLength功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 6:
		 printf("\n----GetElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 7:
		 printf("\n----LocateElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 8:
		 printf("\n----PriorElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 9:
		 printf("\n----NextElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 10:
		 printf("\n----ListInsert功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 11:
		 printf("\n----ListDelete功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 12:
		 //printf("\n----ListTrabverse功能待实现！\n");     
		 if(!ListTrabverse(L)) printf("线性表是空表！\n");
		getchar();getchar();
		 break;
	case 0:
         break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(SqList& L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
if(!L.elem) exit(OVERFLOW);
	L.length=0;
L.listsize=LIST_INIT_SIZE;
	return OK;
}
status ListTrabverse(SqList L){
int i;
printf("\n-----------all elements -----------------------\n");
for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
printf("\n------------------ end ------------------------\n");
return L.length;
}
 
